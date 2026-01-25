/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:16:13 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 21:38:03 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **head, t_redir *n_node)
{
	t_redir	*current;

	if (!n_node)
		return ;
	if (!*head)
	{
		*head = n_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = n_node;
}

int	assign_redirections(t_token **token, t_redir_type *type)
{
	if ((*token)->type == TK_R_IN)
		*type = REDIR_IN;
	else if ((*token)->type == TK_R_OUT)
		*type = REDIR_OUT;
	else if ((*token)->type == TK_APPEND)
		*type = REDIR_APPEND;
	else if ((*token)->type == TK_HEREDOC)
		*type = REDIR_HEREDOC;
	else
		return (0);
	return (1);
}

int	parse_redirections(t_token **tokens, t_command *cmd)
{
	t_redir			*new_redir;
	t_redir_type	type;

	while (*tokens && (*tokens)->type != TK_PIPE && (*tokens)->type != TK_END)
	{
		if (!assign_redirections(tokens, &type))
		{
			*tokens = (*tokens)->next;
			continue ;
		}
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->type != TK_WORD)
			return (-1);
		new_redir = create_redir(type, (*tokens)->value);
		if (!new_redir)
			return (-1);
		add_redir(&cmd->redirs, new_redir);
		*tokens = (*tokens)->next;
	}
	return (0);
}
