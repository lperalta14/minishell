/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:14 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:13:15 by msedeno-         ###   ########.fr       */
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

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(tmp, is_last_heredoc(tmp)))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// ...existing code...
// Función auxiliar para cumplir Norminette en execute_child
static void	validate_cmd_path(char *path, char *cmd_name)
{
	struct stat	st;

	if (!path)
	{
		print_error(cmd_name, "command not found");
		exit(127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(path, "Is a directory");
		exit(126);
	}
}

// Ahora execute_child es corta y protege contra comandos vacíos
void	execute_child(t_command *cmd, t_env **env)
{
	char	*path;
	char	**f_path;

	if (check_redirs(cmd) != 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, env));
	path = get_path(cmd->args[0], *env);
	validate_cmd_path(path, cmd->args[0]);
	f_path = env_to_array(*env);
	if (!f_path)
		exit(1);
	execve(path, cmd->args, f_path);
	print_error(cmd->args[0], strerror(errno));
	exit(126);
}