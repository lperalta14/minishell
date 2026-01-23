/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:10 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 20:57:45 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	else if (!ft_strncmp(cmd, "env", 4))
		return (3);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (4);
	else if (!ft_strncmp(cmd, "export", 7))
		return (5);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (6);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (7);
	return (0);
}

int	execute_builtin(t_command *cmd, t_env **env)
{
	int	built;

	built = is_builtin(cmd->args[0]);
	if (!built || !env)
		return (0);
	if (built == 1)
		return (ft_echo(cmd->args));
	else if (built == 2)
		return (ft_cd(cmd, env));
	else if (built == 3)
		return (ft_env(*env, cmd->args));
	else if (built == 4)
		return (ft_exit(cmd->args, env));
	else if (built == 5)
		return (ft_export(cmd, env));
	else if (built == 6)
		return (ft_pwd(cmd, env));
	else if (built == 7)
		return (ft_unset(cmd->args, env));
	return (0);
}
