/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:25 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 10:52:10 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_redir_file(t_redir *tmp)
{
	int	fd;

	if (tmp->type == REDIR_IN)
		fd = open(tmp->file, O_RDONLY);
	else
		fd = open(tmp->file, get_flags(tmp->type), 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->file);
	}
	return (fd);
}

// Procesa una única redirección (sea archivo o heredoc)
static int	process_one_redir(t_redir *tmp)
{
	int	fd;

	/*if (tmp->type == REDIR_HEREDOC)
	{
		if (cmd->fd_in != -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		return (0);
	}*/
	fd = open_redir_file(tmp);
	if (fd < 0)
		return (1);
	if (tmp->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	check_redirs(t_command *cmd)
{
	t_redir	*tmp;

	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(cmd->fd_in); // Importante cerrar el original tras dup2
		cmd->fd_in = -1; // Marcar como cerrado/usado
	}
	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type != REDIR_HEREDOC) // IGNORAR HEREDOCS AQUI
		{
			if (process_one_redir(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	handle_redirs_only(t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (cmd->redirs)
	{
		pid = fork();
		if (pid == 0)
		{
			if (check_redirs(cmd))
				exit(1);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}
