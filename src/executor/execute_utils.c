#include "../../include/minishell.h"

static int	get_flags(int type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	return (O_WRONLY | O_APPEND | O_CREAT);
}

static int	handle_redirs(t_redir *tmp)
{
	int	fd;
	int	flags;

	flags = get_flags(tmp->type);
	if (tmp->type == REDIR_IN)
		fd = open(tmp->file, flags);
	else
		fd = open(tmp->file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd ("minishell: ", 2);
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

int	check_redirs(t_command *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (handle_redirs(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
