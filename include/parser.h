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
/**
 * @brief Parser principal: convierte tokens en comandos
 * 
 * @param tokens Lista de tokens del lexer
 * @return t_command* Lista de comandos (separados por pipes)
 */
t_command	*parse(t_token *tokens);

/* ============================================ */
/*          FUNCIONES AUXILIARES                */
/* ============================================ */

/**
 * @brief Crea un comando desde tokens
 * 
 * @param tokens Puntero a lista de tokens (se modifica)
 * @return t_command* Comando creado o NULL si error
 */
t_command	*create_command(t_token **tokens);

/**
 * @brief Extrae argumentos de tokens hasta PIPE o END
 * 
 * @param tokens Puntero a lista de tokens (se modifica)
 * @return char** Array de strings terminado en NULL
 */
char		**extract_args(t_token **tokens);

/* ============================================ */
/*          FUNCIONES DE LIMPIEZA               */
/* ============================================ */

/**
 * @brief Libera array de strings terminado en NULL
 * 
 * @param args Array de strings a liberar
 */
void		free_args(char **args);

/**
 * @brief Libera lista enlazada de redirecciones
 * 
 * @param redirs Lista de redirecciones a liberar
 */
void		free_redirs(t_redir *redirs);

/**
 * @brief Libera lista enlazada de comandos completa
 * 
 * @param cmds Lista de comandos a liberar
 */
void		free_commands(t_command *cmds);

/* ============================================ */
/*          FUNCIONES DE DEBUG                  */
/* ============================================ */

/**
 * @brief Imprime lista de comandos (debugging)
 * 
 * @param cmds Lista de comandos a imprimir
 */
void		print_commands(t_command *cmds);

/**
 * @brief Imprime lista de redirecciones (debugging)
 * 
 * @param redirs Lista de redirecciones a imprimir
 */
void		print_redirs(t_redir *redirs);

#endif