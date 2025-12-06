#include "minishell.h"

void	create_redir(t_redir type, char *file)
{
	t_redir	*redir;

	redir = malloc (sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir head, t_redir new)
{
	t_redir	current;

	if (!new)
		return ;
	if (!head)
	{
		head = new;
		return ;
	}
	current = head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	parse_redirections(t_token **tokens, char *cmd)
{
	t_redir			*new_redir;
	t_redir_type	type;

	while (tokens && (*tokens)->type != TK_PIPE && (*token)->type != TK_END)
	{
		if ((*tokens)->type == TK_R_IN)
			type = REDIR_IN;
		else if ((*tokens)->type == TK_R_OUT)
			type = REDIR_OUT;
		else if ((*tokens)->type == TK_APPEND)
			type = REDIR_APPEND;
		else if ((*tokens)->type == TK_HEREDOC)
			type = REDIR_HEREDOC;
		else
		{
			*tokens = (*tokens)->next;
			continue ;
		}
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)-> type != TK_WORD)
			return (-1);
		new_redir = create_redir(type, tokens->value);
		if (!new_redir)
			return (-1);
		add_redir(cmd->redirs, new_redir);
		tokens = tokens->next;
	}
	return (1);
}

// INPUT: "cat < input.txt > output.txt"

//           ↓ tokenize()

// TOKENS: [WORD:"cat"] [REDIR_IN] [WORD:"input.txt"]
//	[REDIR_OUT] [WORD:"output.txt"] [END]

//           ↓ create_command()

//     ┌─────────────────────────────────────┐
//     │  Guardar posición inicial (start)   │
//     └─────────────────────────────────────┘
//               ↓
//     ┌─────────────────────────────────────┐
//     │  extract_args(tokens)               │
//     │  - Cuenta solo WORD (salta redirs)  │
//     │  - Copia solo argumentos            │
//     │  → args = ["cat", NULL]             │
//     └─────────────────────────────────────┘
//               ↓
//     ┌─────────────────────────────────────┐
//     │  Volver al inicio (tokens = start)  │
//     └─────────────────────────────────────┘
//               ↓
//     ┌─────────────────────────────────────┐
//     │  parse_redirections(tokens, cmd)    │
//     │  - Detecta REDIR_IN                 │
//     │  - Crea {REDIR_IN, "input.txt"}     │
//     │  - Detecta REDIR_OUT                │
//     │  - Crea {REDIR_OUT, "output.txt"}   │
//     │  → redirs = lista enlazada          │
//     └─────────────────────────────────────┘
//               ↓

// COMANDO FINAL:
// {
//   args: ["cat", NULL],
//   redirs: {REDIR_IN, "input.txt"} → {REDIR_OUT, "output.txt"} → NULL,
//   next: NULL
// }