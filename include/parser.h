#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

// Target: Convertir lista plana tokens en estructura de comandos ejecutable.

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

/* ============================================ */
/*          FUNCIONES PRINCIPALES               */
/* ============================================ */

// Aquí van los prototipos de parse()

/* ============================================ */
/*          FUNCIONES AUXILIARES                */
/* ============================================ */

// Aquí van create_command, extract_args, etc.

/* ============================================ */
/*          FUNCIONES DE LIMPIEZA               */
/* ============================================ */

// Aquí van free_commands, free_redirs, etc.
/**
 * @brief Libera array de strings terminado en NULL
 * 
 * @param args Array de strings a liberar
 */
void	free_args(char **args);

/* ============================================ */
/*          FUNCIONES DE DEBUG                  */
/* ============================================ */

// Aquí van print_commands, print_redirs

#endif