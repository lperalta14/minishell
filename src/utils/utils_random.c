/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:43 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:17:44 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_spaces(t_lexer_state *state)
{
	while (state->pos < state->len && (state->input[state->pos] == ' '
			|| state->input[state->pos] == '\t'))
		state->pos++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*int	is_word(char c)
{
	if (!is_operator(c) && !is_quote(c) && !isspace(c))
		return (1);
	return (0);
}*/