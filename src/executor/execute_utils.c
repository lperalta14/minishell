/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:14 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:13:15 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_flags(int type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	return (O_WRONLY | O_APPEND | O_CREAT);
}

int	is_last_heredoc(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir->next;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	handle_heredocs_before_pipeline(t_command *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(tmp, is_last_heredoc(tmp)))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
