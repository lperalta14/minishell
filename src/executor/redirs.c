#include "../../include/minishell.h"

static int	handle_redirs(t_redir *tmp)
{
	int	fd;
	int	flags;

	if (tmp->type == REDIR_HEREDOC)
		return (0);
	flags = get_flags(tmp->type);
	if (tmp->type == REDIR_IN)
		fd = open(tmp->file, flags);
	else
		fd = open(tmp->file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->file);
		return (1);
	}
	if (tmp->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_other_redirs(t_command *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type != REDIR_HEREDOC)
		{
			if (handle_redirs(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_redirs(t_command *cmd)
{
	if (handle_other_redirs(cmd))
		return (1);
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
