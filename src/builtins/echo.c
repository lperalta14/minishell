#include "../../include/minishell.h"

int	ft_echo(char **args)
{
	int i;
	int newline;
	
	i = 1;
	newline = 1;
	
	// Detectar flags -n
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	
	// Imprimir argumentos
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	
	// Imprimir salto de línea si corresponde
	if (newline)
		ft_putchar_fd('\n', 1);
	
	return (0);
}