#include "../../../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
/*
void	free_commands(t_command *cmds)
{
	t_command	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		freematrix(tmp->args);
		free_redirs(tmp->redirs);
		free(tmp);
	}
}*/

// void	free_tokens(t_token *tokens)
// {
//     t_token	*tmp;

//     while (tokens)
//     {
//         tmp = tokens->next;
//         if (tokens->value)
//             free(tokens->value);
//         free(tokens);
//         tokens = tmp;
//     }
// // }esta funcion la dejo porque haciendo pruebas en 
// un momento me habia encointrado un supuesto leak:

// ==2586291== definitely lost: 32 bytes in 1 blocks
// ==2586291== indirectly lost: 102 bytes in 6 blocks
// pero no estoy segura de si ha sido una rallada y 
// pasandoselo a la ia me decia esto. lo dejo por aqui por si acaso