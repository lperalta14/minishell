/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:42 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 10:13:02 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Solo nos importa el status del último comando de la pipe
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

static void	child_process(t_command *cmd, t_pipe_state *pipe_st, t_env **env,
	t_command *head)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe_st->prev_read != -1)
	{
		dup2(pipe_st->prev_read, STDIN_FILENO);
		close(pipe_st->prev_read);
	}
	if (cmd->next)
	{
		close(pipe_st->fd[0]);
		dup2(pipe_st->fd[1], STDOUT_FILENO);
		close(pipe_st->fd[1]);
	}
	execute_child(cmd, env, head);
	exit(g_exit_status);
}

void	run_pipe_loop(t_command *cmd, t_env **env, pid_t *pid, t_command *head)
{
	t_pipe_state	state;

	state.prev_read = -1;
	while (cmd)
	{
		if (cmd->next && pipe(state.fd) == -1)
			return (perror("minishell: pipe"));
		*pid = fork();
		if (*pid == -1)
			return (perror("minishell: fork"));
		if (*pid == 0)
			child_process(cmd, &state, env, head);
		if (state.prev_read != -1)
			close(state.prev_read);
		if (cmd->next)
		{
			close(state.fd[1]);
			state.prev_read = state.fd[0];
		}
		cmd = cmd->next;
	}
}

static int	prepare_heredocs(t_command *cmd, t_env **env, t_command *head)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (handle_heredocs_before_pipeline(tmp, env, head) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/**
 * 2. Guardar teclado antes de tocar nada
 * 3. Restaurar teclado INMEDIATAMENTE para que el padre quede limpio
 *
 */
void	execute_pipeline(t_command *cmd, t_env **env)
{
	pid_t		pid;
	int			stdin_bk;
	t_command	*head;

	head = cmd;
	stdin_bk = dup(STDIN_FILENO);
	if (prepare_heredocs(cmd, env, head))
	{
		dup2(stdin_bk, STDIN_FILENO);
		close(stdin_bk);
		return ;
	}
	dup2(stdin_bk, STDIN_FILENO);
	close(stdin_bk);
	setup_signals_execution();
	run_pipe_loop(cmd, env, &pid, head);
	wait_children(pid);
	setup_signals_interactive();
}
