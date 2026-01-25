/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:04 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 20:37:05 by casimarasn       ###   ########.fr       */
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
    REDIR_IN,       /* Standard input redirection '<' */
    REDIR_OUT,      /* Standard output redirection '>' (truncate) */
    REDIR_APPEND,   /* Standard output redirection '>>' (append) */
    REDIR_HEREDOC   /* Heredoc input redirection '<<' */
}	t_redir_type;

/**
 * @struct s_redir
 * @brief Linked list node representing a single redirection.
 * 
 * @var s_redir::type  Type of redirection (IN, OUT, APPEND, HEREDOC).
 * @var s_redir::file  File name or delimiter (for heredoc).
 * @var s_redir::next  Pointer to the next redirection in the list.
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
 * A command block is everything between pipes.
 * 
 * @var s_command::args    Null-terminated array of arguments (argv).
 * @var s_command::redirs  Linked list of redirections associated with this cmd.
 * @var s_command::fd_in   File descriptor for input (unused in final version).
 * @var s_command::fd_out  File descriptor for output (unused in final version).
 * @var s_command::next    Pointer to the next command (pipe) in pipeline.
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
 * @brief Main parsing entry point. Converts a flat list of tokens into
 * an executable command structure (AST-like).
 * 
 * @param tokens Pointer to the head of the token list.
 * @return t_command* The head of the command pipeline, or NULL on error.
 */
t_command	*parse(t_token *tokens);

/* ************************************************************************** */
/*                              HELPER FUNCTIONS                              */
/* ************************************************************************** */

/**
 * @brief Initializes and populates a single command structure.
 * Iterates through tokens until a pipe or end is reached.
 * 
 * @param tokens Double pointer to current token (advances to the next pipe).
 * @return t_command* The created command structure.
 */
t_command	*create_command(t_token **tokens);

/**
 * @brief Extracts arguments from the token stream.
 * Allocates a char** array for execve. Skips redirections and pipes.
 * 
 * @param tokens Double pointer to current token (advances).
 * @return char** Null-terminated array of arguments.
 */
char		**extract_args(t_token **tokens);

/**
 * @brief Performs syntax validation on the token stream.
 * Checks for illegal sequences (e.g., pipes at start/end, double pipes).
 * 
 * @param tokens Double pointer to the token list head.
 * @return int 0 if syntax is valid, 1 (with error print) otherwise.
 */
int			validate_syntax(t_token **tokens);

/* ************************************************************************** */
/*                          REDIRECTION HANDLING                              */
/* ************************************************************************** */

/**
 * @brief Allocates and initializes a new redirection node.
 * 
 * @param type The type of redirection.
 * @param file The target filename or heredoc delimiter.
 * @return t_redir* Pointer to the new node.
 */
t_redir		*create_redir(t_redir_type type, char *file);

/**
 * @brief Identifies if a token represents a redirection operator.
 * 
 * @param token Double pointer to current token.
 * @param type Pointer to store the resulting redirection type.
 * @return int 1 if it is a redirection operator, 0 otherwise.
 */
int			assign_redirections(t_token **token, t_redir_type *type);

/**
 * @brief Processes redirection tokens associated with a command.
 * Extracts redirection operators and filenames, adding them to cmd->redirs.
 * 
 * @param tokens Double pointer to current token stream.
 * @param cmd The command structure to update.
 * @return int 0 on success, -1 on failure.
 */
int			parse_redirections(t_token **tokens, t_command *cmd);

/**
 * @brief Appends a redirection node to the end of the list.
 * 
 * @param head Pointer to the list head pointer.
 * @param new The new node to add.
 */
void		add_redir(t_redir **head, t_redir *new_node);

/* ************************************************************************** */
/*                              MEMORY CLEANUP                                */
/* ************************************************************************** */

/**
 * @brief Frees the memory of a redirection list.
 * 
 * @param redirs The head of the redirection list.
 */
void		free_redirs(t_redir *redirs);

/**
 * @brief Frees the entire command pipeline structure.
 * Recursively frees args, redirs, and next commands.
 * 
 * @param cmds The head of the command list.
 */
void		free_commands(t_command *cmds);

/**
 * @brief Prints a syntax error message to STDERR.
 * Format: "minishell: syntax error near unexpected token `token`"
 * 
 * @param token_str The string value of the unexpected token.
 * @return int Always returns 1 (error status), or 258 for Bash compliance.
 */
int			syntax_error(char *token_str);

/* ************************************************************************** */
/*                              DEBUGGING                                     */
/* ************************************************************************** */

/**
 * @brief Debug helper: Prints the parsing result to STDOUT.
 * Shows args and pipe structure.
 * 
 * @param cmds The command list.
 */
void		print_commands(t_command *cmds);

/**
 * @brief Debug helper: Prints redirection details.
 * 
 * @param redirs The redirection list.
 */
void		print_redirs(t_redir *redirs);

#endif