/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:43 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:18:01 by msedeno-         ###   ########.fr       */
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
