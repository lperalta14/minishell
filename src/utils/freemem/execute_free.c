/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:42:25 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 10:42:26 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	clean_child_exit(int status, t_env **env, char **mat, t_command *cmds)
{
	if (mat)
		ft_freematrix(mat);
	if (cmds)
		free_commands(cmds);
	free_env_list(*env);
	rl_clear_history();
	exit(status);
}
