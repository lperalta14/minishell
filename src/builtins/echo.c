#include "../../include/minishell.h"

int	ft_echo(char **args)
{
	int i;
	int newline;
	
	i = 1;
	newline = 1;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}