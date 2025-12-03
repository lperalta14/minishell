#include "../../../include/minishell.h"

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
	int	i;

	if (!redirs)
		return ;
	i = 0;
	while (!redirs)
	tmp = redirs;
	redirs = redir
}
