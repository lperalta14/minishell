#include "../../include/minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	if (!redirs)
		return ;
	while (redirs)
	{
		tmp = redirs;
		redirs = tmp->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_commands(t_command *cmds)
{
	t_command	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_args(tmp->args);
		free_redirs(tmp->redirs);
		free(tmp);
	}
}

int	syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}
