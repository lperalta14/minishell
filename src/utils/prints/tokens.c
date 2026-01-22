/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:34 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:17:35 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
t_token	*tmp = tokens;

printf("\n---- TOKENS ----\n");
while (tmp)
{
	printf("TYPE: %d | QUOTE: %d | VALUE: \"%s\"\n", tmp->type, tmp->quote, tmp->value);
	tmp = tmp->next;
}
printf("----------------\n\n");
}
