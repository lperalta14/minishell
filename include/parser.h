/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:04 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 21:46:05 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/**
 * @enum e_redir_type
 * @brief Categorizes the type of I/O redirection.
 */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/**
 * @struct s_redir
 * @brief Linked list node representing a single redirection.
 */
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/**
 * @struct s_command
 * @brief Linked list node representing a parsed command block.
 */
typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}	t_command;

/* ************************************************************************** */
/*                              CORE FUNCTIONS                                */
/* ************************************************************************** */

/**
 * @brief Main parsing entry point.
 * @param tokens Pointer to the head of the token list.
 * @return t_command* The head of the command pipeline.
 */
t_command	*parse(t_token *tokens);

/* ************************************************************************** */
/*                              HELPER FUNCTIONS                              */
/* ************************************************************************** */

/**
 * @brief Initializes and populates a single command structure.
 * @param tokens Double pointer to current token.
 * @return t_command* The created command structure.
 */
t_command	*create_command(t_token **tokens);

/**
 * @brief Extracts arguments from the token stream.
 * @param tokens Double pointer to current token.
 * @return char** Null-terminated array of arguments.
 */
char		**extract_args(t_token **tokens);

/**
 * @brief Performs syntax validation on the token stream.
 * @param tokens Double pointer to the token list head.
 * @return int 0 if syntax is valid, 1 otherwise.
 */
int			validate_syntax(t_token **tokens);

/* ************************************************************************** */
/*                          REDIRECTION HANDLING                              */
/* ************************************************************************** */

/**
 * @brief Allocates and initializes a new redirection node.
 * @param type The type of redirection.
 * @param file The target filename or heredoc delimiter.
 * @return t_redir* Pointer to the new node.
 */
t_redir		*create_redir(t_redir_type type, char *file);

/**
 * @brief Identifies if a token represents a redirection operator.
 * @param token Double pointer to current token.
 * @param type Pointer to store the resulting redirection type.
 * @return int 1 if it is a redirection operator, 0 otherwise.
 */
int			assign_redirections(t_token **token, t_redir_type *type);

/**
 * @brief Processes redirection tokens associated with a command.
 * @param tokens Double pointer to current token stream.
 * @param cmd The command structure to update.
 * @return int 0 on success, -1 on failure.
 */
int			parse_redirections(t_token **tokens, t_command *cmd);

/**
 * @brief Appends a redirection node to the end of the list.
 * @param head Pointer to the list head pointer.
 * @param node The new node to add.
 */
void		add_redir(t_redir **head, t_redir *n_node);

/* ************************************************************************** */
/*                              MEMORY CLEANUP                                */
/* ************************************************************************** */

/**
 * @brief Frees the memory of a redirection list.
 * @param redirs The head of the redirection list.
 */
void		free_redirs(t_redir *redirs);

/**
 * @brief Frees the entire command pipeline structure.
 * @param cmds The head of the command list.
 */
void		free_commands(t_command *cmds);

/**
 * @brief Prints a syntax error message to STDERR.
 * @param token_str The string value of the unexpected token.
 * @return int Always returns 1.
 */
int			syntax_error(char *token_str);

/* ************************************************************************** */
/*                              DEBUGGING                                     */
/* ************************************************************************** */

/**
 * @brief Debug helper: Prints the parsing result to STDOUT.
 * @param cmds The command list.
 */
void		print_commands(t_command *cmds);

/**
 * @brief Debug helper: Prints redirection details.
 * @param redirs The redirection list.
 */
void		print_redirs(t_redir *redirs);

#endif