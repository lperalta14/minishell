/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:16:19 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:16:08 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TK_R_IN || type == TK_R_OUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

int	syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	validate_syntax( t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp)
		return (1);
	if (tmp->type == TK_PIPE)
		return (syntax_error("|"));
	while (tmp)
	{
		if (tmp->type == TK_PIPE)
		{
			if (!tmp->next || tmp->next->type == TK_PIPE)
				return (syntax_error("|"));
		}
		else if (is_redir_token (tmp->type))
		{
			if (!tmp->next)
				return (syntax_error("newline"));
			if (tmp->next->type != TK_WORD)
				return (syntax_error(tmp->next->value));
		}
		tmp = tmp->next;
	}
	return (1);
}
