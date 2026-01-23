/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:04 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 18:17:05 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

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
/*				MAIN 	FUNCTIONS				*/
/* ============================================ */
/**
 * @brief Principal parser: converts tokens into commands.
 * 
 * @param tokens List of tokens from the lexer.
 * @return t_command* List of commands (separated by pipes).
 */
t_command	*parse(t_token *tokens);

/* ============================================ */
/*						AUX						*/
/* ============================================ */

/**
 * @brief Creates a command from tokens.
 * 
 * @param tokens Pointer to token list (modified during parsing).
 * @return t_command* Created command or NULL on error.
 */
t_command	*create_command(t_token **tokens);

/**
 * @brief Extracts arguments from tokens until a PIPE or END is found.
 * 
 * @param tokens Pointer to token list (modified during parsing).
 * @return char** NULL-terminated array of strings.
 */
char		**extract_args(t_token **tokens);

/**
 * @brief Validates syntax by checking token sequence.
 * 
 * @param tokens Pointer to token list.
 * @return int 1 if syntax is valid, 0 otherwise.
 */
int			validate_syntax( t_token **tokens);

/* ============================================ */
/*				REDIRECTIONS					*/
/* ============================================ */
/**
 * @brief Create a redirection object.
 * 
 * @param type Redirection type.
 * @param file Filename or delimiter.
 * @return t_redir* Pointer to created redirection.
 */
t_redir		*create_redir(t_redir_type type, char *file);

/**
 * @brief Determines redirection type based on token type.
 * 
 * @param token Token double pointer.
 * @param type Pointer to store the result redirection type.
 * @return int 1 if it is a redirection, 0 otherwise.
 */
int			assign_redirections(t_token **token, t_redir_type *type);

/**
 * @brief Parses redirections from tokens and adds them to command.
 * 
 * @param tokens Pointer to token list.
 * @param cmd Command to add redirections to.
 * @return int 0 on success, -1 on error.
 */
int			parse_redirections(t_token **tokens, t_command *cmd);

/**
 * @brief Adds a redirection node to the list.
 * 
 * @param head Pointer to the head of the list.
 * @param new New redirection node.
 */
void		add_redir(t_redir **head, t_redir *new);

/* ============================================ */
/*					CLEANERS					*/
/* ============================================ */

/**
 * @brief Frees a linked list of redirections.
 * 
 * @param redirs List of redirections to free.
 */
void		free_redirs(t_redir *redirs);

/**
 * @brief Frees a complete linked list of commands.
 * 
 * @param cmds List of commands to free.
 */
void		free_commands(t_command *cmds);

/**
 * @brief Prints a syntax error message.
 * 
 * @param token_str The unexpected token string.
 * @return int Always returns 0 (for error code propagation).
 */
int			syntax_error(char *token_str);

/* ============================================ */
/*					DEBUG						*/
/* ============================================ */

/**
 * @brief Prints list of commands (for debugging).
 * 
 * @param cmds List of commands to print.
 */
void		print_commands(t_command *cmds);

/**
 * @brief Prints list of redirections (for debugging).
 * 
 * @param redirs List of redirections to print.
 */
void		print_redirs(t_redir *redirs);

#endif