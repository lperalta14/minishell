#include "../../include/minishell.h"

static int	is_valid_env_name(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == '=')
		{
			if (i == 0)
				return (0);
			return (1);
		}
		if (i == 0 && ft_isdigit(c))
			return (0);
		if (!ft_isalnum(c) && c != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}


int	ft_export(t_command *cmd, t_env **env)
{
	int		i;
	int		status;
	t_env	*tmp;
	t_env	*current;

	status = 0;
	if (!cmd->args[1])
		return (print_sorted_env(env));
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_env_name(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
		{
			tmp = get_env_node(cmd->args[i]);
			if (!tmp)
				return (1);
			current = find_env(*env, tmp->key);
			if (current)
			{
				if (tmp->value)
				{
					free(current->value);
					current->value = tmp->value;
					tmp->value = NULL;
				}
				free_node(tmp);
			}
			else
				add_env(env, tmp);
		}
		i++;
	}
	return (status);
}
