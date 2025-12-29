#include "../../include/minishell.h"

void	execute_pipeline(t_command *cmd, t_env **env)
{
	int			prev_pipe_read;
	t_command	*tmp;
	int			fd[2];
	pid_t		pid;

	prev_pipe_read = -1;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(fd) == -1)
			{
				perror("minishell: pipe");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			return ;
		}
		if (pid == 0)
		{
			if (prev_pipe_read != -1) // vengo de un pipe anterior?
			{
				dup2(prev_pipe_read, STDIN_FILENO);
				close(prev_pipe_read);
			}
			if (tmp->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute_child(tmp, env);
		}
		else
		{
			if (prev_pipe_read != -1)
				close(prev_pipe_read);
			if (tmp->next)
			{
				close(fd[1]);
				prev_pipe_read = fd[0];
			}
			tmp = tmp->next;
		}
	}
	while (wait(NULL) > 0)
		;
}
