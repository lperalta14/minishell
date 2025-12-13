#include "../../include/minishell.h"

<<<<<<< HEAD
/*int	validate_syntax( t_token **tokens)
=======
int	is_redir_token(t_token_type type)
{
	return (type == TK_R_IN || type == TK_R_OUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

int	syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	validate_syntax( t_token **tokens)
>>>>>>> origin/mariabranch
{
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp)
		return (1);
	if (tmp->type == TK_PIPE)
		return (syntax_error("|"));
	while (tmp)
	{
		if (tmp->type == TK_PIPE)
		{
			if (!tmp->next || tmp->next->type == TK_PIPE)
				return (syntax_error("|"));
		}
		else if (is_redir_token (tmp->type))
		{
			if (!tmp->next)
				return (syntax_error("newline"));
			if (tmp->next->type != TK_WORD)
				return (syntax_error(tmp->next->value));
		}
		tmp = tmp->next;
	}
<<<<<<< HEAD

}*/
=======
	return (1);
}
>>>>>>> origin/mariabranch

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