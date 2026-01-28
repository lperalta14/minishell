/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:14 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 10:51:48 by msedeno-         ###   ########.fr       */
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

int	handle_heredocs_before_pipeline(t_command *cmd, t_env **env,
	t_command *cmds_head)
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
			if (handle_heredoc(tmp, cmd, env, cmds_head))
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
void	execute_child(t_command *cmd, t_env **env, t_command *cmds_head)
{
	char	**f_path;
	int		ret_status;

	if (check_redirs(cmd) != 0)
		clean_child_exit(1, env, NULL, cmds_head);
	if (!cmd->args || !cmd->args[0])
		clean_child_exit(0, env, NULL, cmds_head);
	if (is_builtin(cmd->args[0]))
	{
		ret_status = execute_builtin(cmd, env, cmds_head);
		clean_child_exit(ret_status, env, NULL, cmds_head);
	}
	cmd->path = get_path(cmd->args[0], *env);
	ret_status = validate_cmd_path(cmd->path, cmd->args[0]);
	if (ret_status != 0)
		clean_child_exit(ret_status, env, NULL, cmds_head);
	f_path = env_to_array(*env);
	if (!f_path)
		clean_child_exit(1, env, NULL, cmds_head);
	execve(cmd->path, cmd->args, f_path);
	print_error(cmd->args[0], strerror(errno));
	clean_child_exit(126, env, f_path, cmds_head);
}

