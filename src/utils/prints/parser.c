#include "../../../include/minishell.h"
#include "parse.h"


void	print_commands(t_command *cmds)
{
	int	count;
	int	i;

	count = 0;
	while (cmds != NULL)
	{
		printf("--- Command cmd[0] ---");
		if (cmd->args)
		{
			printf ("Args: ");
			i = 0;
			while (cmd->args[i])
			{
				printf("[", "%s", cmd->args[i], "]");
				i++;
			}
			printf("\n");
		}
		else
			printf("Args: ");
		if (cmd->redirs)
			print_redirs(cmd->redirs);
		else
			printf("Redirections: \n")
		if (cmds->next)
		{
			printf("        |");
			printf("        v (PIPE)");
			printf("\n");
		}
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