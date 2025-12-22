#include "../../include/minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(env->value, 1);

		}
		env = env->next;
	}
	return (0);
}
