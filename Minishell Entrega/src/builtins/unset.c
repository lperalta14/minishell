/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:59 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:14:00 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (args[i][0] != '_')
			delete_env_var(env, args[i]);
		i++;
	}
	return (0);
}
