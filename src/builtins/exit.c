/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:21 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/26 00:15:21 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i]) // si solo "+" o "-"
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	clean_and_exit(int status, t_env **env)
{
	free_env_list(*env);
	//rl_clear_history();
	clear_history();
	exit(status);
}

int	ft_exit(char **args, t_env **env)
{
	//ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		clean_and_exit(g_exit_status, env);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_and_exit(255, env);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	clean_and_exit(ft_atoi(args[1]), env);
	return (0);
}
