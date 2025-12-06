#include "../../../include/minishell.h"

static t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
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

void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	parse_redirections(t_token **tokens, t_command *cmd)
{
	t_redir			*new_redir;
	t_redir_type	type;

	while (*tokens && (*tokens)->type != TK_PIPE && (*tokens)->type != TK_END)
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
		if (!*tokens || (*tokens)->type != TK_WORD)
			return (-1);
		new_redir = create_redir(type, (*tokens)->value);
		if (!new_redir)
			return (-1);
		add_redir(&cmd->redirs, new_redir);
		*tokens = (*tokens)->next;
	}
	return (0);
}

// # Caso 1: Input simple
// cat < file.txt

// # Caso 2: Output simple
// ls > output.txt

// # Caso 3: Append
// echo "text" >> log.txt

// # Caso 4: Múltiples redirecciones
// cat < in.txt > out.txt

// # Caso 5: Con argumentos
// grep "word" < file.txt > result.txt

// # Caso 6: Error (sin archivo)
// cat <    # ← Debe dar error

// # Caso 7: Con pipes
// cat < in.txt | grep test > out.txt

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