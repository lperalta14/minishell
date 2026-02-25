/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:34 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 16:45:42 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	ft_printf("\n---- TOKENS ----\n");
	while (tmp)
	{
		ft_printf("TYPE: %d | QUOTE: %d | VALUE: \"%s\"\n",
			tmp->type, tmp->quote, tmp->value);
		tmp = tmp->next;
	}
	ft_printf("----------------\n\n");
}
