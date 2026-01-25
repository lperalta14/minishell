/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:14 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 21:51:04 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_flags(int type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	return (O_WRONLY | O_APPEND | O_CREAT);
}

int	is_last_heredoc(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir->next;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	handle_heredocs_before_pipeline(t_command *cmd)
{
	t_redir	*tmp;

	if (cmd->fd_in != -1)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(tmp, &cmd->fd_in))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// ...existing code...
// Función auxiliar para cumplir Norminette en execute_child
static int	validate_cmd_path(char *path, char *cmd_name)
{
	struct stat	st;

	if (!path)
	{
		print_error(cmd_name, "command not found");
		return (127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(path, "Is a directory");
		return (126);
	}
	return (0);
}

// Ahora execute_child es corta y protege contra comandos vacíos
void	execute_child(t_command *cmd, t_env **env)
{
	char	*path;
	char	**f_path;
	int		ret_status;

	if (check_redirs(cmd) != 0)
		clean_child_exit(1, env, NULL, NULL);
	if (!cmd->args || !cmd->args[0])
		clean_child_exit(0, env, NULL, NULL);
	if (is_builtin(cmd->args[0]))
	{
		ret_status = execute_builtin(cmd, env);
		clean_child_exit(ret_status, env, NULL, NULL);
	}
	path = get_path(cmd->args[0], *env);
	ret_status = validate_cmd_path(path, cmd->args[0]);
	if (ret_status != 0)
		clean_child_exit(ret_status, env, path, NULL);
	f_path = env_to_array(*env);
	if (!f_path)
		clean_child_exit(1, env, NULL, NULL);
	execve(path, cmd->args, f_path);
	print_error(cmd->args[0], strerror(errno));
	clean_child_exit(126, env, path, f_path);
}

/*Cambios Clave:
1. clean_child_exit: Actúa como un embudo único de salida. 
No importa dónde falles, llamas a esta función pasando lo que tengas asignado
hasta el momento (path o f_path), o NULL si aún no los tenías. Siempre limpia
env y history.

2. validate_cmd_path: Ya no mata el proceso. Devuelve 127 o 126. Esto permite que
execute_child reciba el control de vuelta y llame a la limpieza antes de salir.

3. Orden de ejecución: Se asigna f_path (la matriz pesada) después de validar que
el comando existe y es ejecutable, ahorrando recursos si el comando no es
válido.*/
