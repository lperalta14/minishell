/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:54 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 18:15:04 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_env		t_env;
typedef struct s_redir		t_redir;

/********************************************************/
/*						PRINTS							*/
/********************************************************/

/**
 * @brief Frees the token list.
 * @param tokens Pointer to the start of the token list.
 */
void	free_tokens(t_token *tokens);

/**
 * @brief Frees the command list.
 * 
 * @param cmds Pointer to the start of the command list.
 */
void	free_commands(t_command *cmds);

/**
 * @brief Prints a banner text.
 * 
 * @param text The text to print.
 */
void	print_banner(char *text);

/**
 * @brief Prints tokens for debugging purposes.
 * 
 * @param tokens Pointer to the token list.
 */
void	print_tokens(t_token *tokens);

/**
 * @brief Prints an error message to stderr with the command name.
 * 
 * @param cmd The command name (optional).
 * @param msg The error message.
 */
void	print_error(char *cmd, char *msg);

/********************************************************/
/*						MEMORY							*/
/********************************************************/

/**
 * @brief Frees the entire environment list.
 * 
 * @param head Pointer to the head of the list.
 */
void	free_env_list(t_env *head);

/**
 * @brief Frees a single environment node.
 * 
 * @param node Pointer to the node to free.
 */
void	free_node(t_env *node);

/**
 * @brief Frees the token list.
 * 
 * @param tokens Pointer to the start of the token list.
 */
void	free_tokens(t_token *tokens);

/**
 * @brief Frees the command list.
 * 
 * @param cmds Pointer to the start of the command list.
 */
void	free_commands(t_command *cmds);

/**
 * @brief Frees the redirection list.
 * 
 * @param redirs Pointer to the start of the redirection list.
 */
void	free_redirs(t_redir *redirs);

#endif