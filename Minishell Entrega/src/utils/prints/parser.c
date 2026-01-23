/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:19 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 17:09:48 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	print_commands(t_command *cmds)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	while (cmds != NULL)
// 	{
// 		printf("--- Command %d ---\n", count);
// 		if (cmds->args)
// 		{
// 			printf("Args: ");
// 			i = 0;
// 			while (cmds->args[i])
// 			{
// 				printf("[%s] ", cmds->args[i]);
// 				i++;
// 			}
// 			printf("\n");
// 		}
// 		else
// 			printf("Args: (ninguno)\n");
// 		if (cmds->redirs)
// 			print_redirs(cmds->redirs);
// 		else
// 			printf("Redirections: (ninguna)\n");
// 		if (cmds->next)
// 			printf("        |\n        v (PIPE)\n\n");
// 		cmds = cmds->next;
// 		count++;
// 	}
// 	printf("\n");
// }

void	print_redirs(t_redir *redirs)
{
	printf("Redirections:\n");
	while (redirs)
	{
		printf("  ");
		if (redirs->type == REDIR_IN)
			printf("< ");
		else if (redirs->type == REDIR_OUT)
			printf("> ");
		else if (redirs->type == REDIR_APPEND)
			printf(">> ");
		else if (redirs->type == REDIR_HEREDOC)
			printf("<< ");
		printf("%s\n", redirs->file);
		redirs = redirs->next;
	}
}
