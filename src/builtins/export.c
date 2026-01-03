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

int	ft_export(char **args, char **env)
{

}