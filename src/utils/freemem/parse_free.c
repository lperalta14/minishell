/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:05 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 09:46:39 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	if (!redirs)
		return ;
	while (redirs)
	{
		tmp = redirs;
		redirs = tmp->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_commands(t_command *cmds)
{
	t_command	*tmp;
	t_command	*head;

	if (!cmds)
		return ;
	head = cmds;
	if (cmds->head)
		head = cmds->head;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->fd_in > 2)
			close(tmp->fd_in);
		if (tmp->fd_out > 2)
			close(tmp->fd_out);
		if (tmp->path)
			free(tmp->path);
		ft_freematrix(tmp->args);
		free_redirs(tmp->redirs);
		free(tmp);
	}
}
