/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:33 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:15:34 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_env_name(char *str)
{
	int		i;
	char	c;

	if (!str || !*str)
		return (0);
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
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static int	export_var(char *arg, t_env **env)
{
	t_env	*tmp;
	t_env	*current;

	tmp = get_env_node(arg);
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
	return (0);
}

int	ft_export(t_command *cmd, t_env **env)
{
	int		i;
	int		status;

	status = 0;
	if (!cmd->args[1])
		return (print_sorted_env(*env));
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_env_name(cmd->args[i]))
		{
			print_export_error(cmd->args[i]);
			status = 1;
		}
		else
		{
			if (export_var(cmd->args[i], env))
				return (1);
		}
		i++;
	}
	return (status);
}
