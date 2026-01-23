/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:34 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 16:40:29 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	printf("\n---- TOKENS ----\n");
	while (tmp)
	{
		printf("TYPE: %d | QUOTE: %d | VALUE: \"%s\"\n",
			tmp->type, tmp->quote, tmp->value);
		tmp = tmp->next;
	}
	printf("----------------\n\n");
}
