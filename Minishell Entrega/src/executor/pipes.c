/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:42 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:15:27 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	wait_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 1);
			}
		}
	}
}

static void	child_process(t_command *cmd, int prev_read, int *fd, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execute_child(cmd, env);
	exit(g_exit_status);
}

static void	run_pipe_loop(t_command *cmd, t_env **env, pid_t *pid)
{
	int	prev_read;
	int	fd[2];

	prev_read = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("minishell: pipe"));
		*pid = fork();
		if (*pid == -1)
			return (perror("minishell: fork"));
		if (*pid == 0)
			child_process(cmd, prev_read, fd, env);
		if (prev_read != -1)
			close(prev_read);
		if (cmd->next)
		{
			close(fd[1]);
			prev_read = fd[0];
		}
		cmd = cmd->next;
	}
}

static int	prepare_heredocs(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (handle_heredocs_before_pipeline(tmp) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_pipeline(t_command *cmd, t_env **env)
{
	pid_t	pid;
	int		stdin_bk;

	stdin_bk = dup(STDIN_FILENO);
	if (prepare_heredocs(cmd))
	{
		dup2(stdin_bk, STDIN_FILENO);
		close(stdin_bk);
		return ;
	}
	dup2(stdin_bk, STDIN_FILENO);
	close(stdin_bk);
	setup_signals_execution();
	run_pipe_loop(cmd, env, &pid);
	wait_children(pid);
	setup_signals_interactive();
}
