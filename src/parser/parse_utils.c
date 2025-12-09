#include "../../include/minishell.h"

int	validate_syntax( t_token **tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp)
		return (1);
	if (tmp->type == TK_PIPE)
		syntax_error("|");
	while (tmp)
	{
		if (tmp->type == TK_PIPE)
		{
			if (tmp->next == NULL || tmp->next == EOF)
				syntax_error("|");
			if (tmp->next == TK_PIPE)
				syntax_error ("|");
		}
		if (tmp-)
	}

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