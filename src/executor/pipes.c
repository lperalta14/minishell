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
		// Solo nos importa el status del último comando de la pipe
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

static void	parent_process(t_command *cmd, int *prev_read, int *fd)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_read = fd[0];
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
	int			prev_read;
	int			fd[2];
	pid_t		pid;

	if (prepare_heredocs(cmd))
		return ;
	prev_read = -1;
	setup_signals_execution();
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("minishell: pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"));
		if (pid == 0)
			child_process(cmd, prev_read, fd, env);
		parent_process(cmd, &prev_read, fd);
		cmd = cmd->next;
	}
	wait_children(pid);
	setup_signals_interactive();
}
