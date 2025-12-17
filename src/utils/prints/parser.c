#include "../../../include/minishell.h"


void	print_commands(t_command *cmds)
{
	int	count;
	int	i;

	count = 0;
	while (cmds != NULL)
	{
		printf("--- Command %d ---\n", count);
		if (cmds->args)
		{
			printf("Args: ");
			i = 0;
			while (cmds->args[i])
			{
				printf("[%s] ", cmds->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("Args: (ninguno)\n");
		if (cmds->redirs)
			print_redirs(cmds->redirs);
		else
			printf("Redirections: (ninguna)\n");
		if (cmds->next)
			printf("        |\n        v (PIPE)\n\n");
		cmds = cmds->next;
		count++;
	}
	printf("\n");
}

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

// --- Command 0 ---
// Args: [ls] [-la]
// Redirections: (ninguna)

//         |
//         v (PIPE)

// --- Command 1 ---
// Args: [grep] [test]
// Redirections:
//   > output.txt