#include "../../include/minishell.h"

void	sort_env_tab(t_env **tab, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(tab[j]->key, tab[j + 1]->key) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_env	**get_sorted_tab(t_env *env, int count)
{
	t_env	**tab;
	int		i;

	tab = malloc(sizeof(t_env *) * count);
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i++] = env;
		env = env->next;
	}
	sort_env_tab(tab, count);
	return (tab);
}

int	print_sorted_env(t_env *env)
{
	t_env	**tab;
	int		count;
	int		i;

	count = env_size(env);
	tab = get_sorted_tab(env, count);
	if (!tab)
		return (1);
	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(tab[i]->key, "_") != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tab[i]->key, 1);
			if (tab[i]->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tab[i]->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putendl_fd("", 1);
		}
	}
	return (free(tab), 0);
}
