/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:21 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/27 19:50:04 by msedeno-         ###   ########.fr       */
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

static void	clean_and_exit(int status, t_env **env, t_command *cmds_head)
{
	free_env_list(*env);
	if (cmds_head)
		free_commands(cmds_head);
	rl_clear_history();
	exit(status);
}

int	ft_exit(t_command *cmd/*char **args*/, t_env **env, t_command *cmds_head)
{
	//ft_putendl_fd("exit", 2);
	if (!cmds_head)
		cmds_head = cmd;
	if (!cmd->args || !cmd->args[1])
		clean_and_exit(g_exit_status, env, cmds_head);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_and_exit(255, env, cmd);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	clean_and_exit(ft_atoi(cmd->args[1]), env, cmd);
	return (0);
}
