#include "../../include/minishell.h"

int	is_valid_env_name(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == '=')
			return (1);
		if (i == 0 && ft_isdigit(c))
			return (0);
		if (!ft_isalnum(c) && c != '_')
			return (0);
		i++;
	}
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	int		status;
	t_env	*tmp;

	if (args[1] == NULL)
	{
		ft_env(*env); //para nota tiene que ser alfabetico.
		return (0);
	}
	i = 1;
	while (args[i])
	{
		tmp = get_env_node(args[i]);
		if (!is_valid_env_name(args[i]))
		{
			ft_putstr_fd("minishell: export: `args[i]`:
				not a valid identifier", 1);
			status = 1;
			i++;
		}


	}
}
