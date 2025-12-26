#include "../../include/minishell.h"

int	is_numeric(char *num)
{
	int	i;

	if (!num || !*num)
		return (0);
	i = 0;
	if (ft_issign(num[i]))
		i++ ;
	while (num[i] && ft_isdigit(num[i]))
		i++ ;
	if ((int)ft_strlen(num) == i)
		return (1);
	return (0);
}

int	get_exit_code(char *str)
{
	long	num;

	num = ft_atoi(str) % 256;
	if (num < 0)
		num += 256;
	return ((int)num);
}

int	ft_exit(char **args)
{
	int argc;
	int exit_code;
	
	ft_putstr_fd("exit\n", 1);
	argc = 0;
	while (args[argc])
		argc++;
	if (argc == 1)
		exit(g_exit_status);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = get_exit_code(args[1]);
	exit(exit_code);
}
