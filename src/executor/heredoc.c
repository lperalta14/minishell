/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:48 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/26 00:15:53 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static void	heredoc_child(t_redir *redir, int *pipefd)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	//rl_clear_history();
	clear_history();
	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: ", 2);
			ft_putendl_fd("here-document delimited by EOF", 2);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

// Nueva función auxiliar: Gestiona la espera del padre y actualiza el FD
static int	wait_heredoc_child(pid_t pid, int pipe_read, int *io_fd)
{
	int	status;

	setup_signals_execution();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
	{
		close(pipe_read);
		g_exit_status = 130;
		return (1);
	}
	if (*io_fd > 2)
		close(*io_fd);
	*io_fd = pipe_read;
	return (0);
}

int	handle_heredoc(t_redir *redir, int *io_fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("minishell: pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (perror("minishell: fork"), 1);
	}
	if (pid == 0)
		heredoc_child(redir, pipefd);
	close(pipefd[1]);
	return (wait_heredoc_child(pid, pipefd[0], io_fd));
}
