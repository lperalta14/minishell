/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:54 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/27 19:40:26 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* 
** Forward declarations to avoid circular dependency issues 
** since utils.h is often included before module headers.
*/
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_env		t_env;
typedef struct s_redir		t_redir;

/* ************************************************************************** */
/*                              PRINTS & DEBUG                                */
/* ************************************************************************** */

/**
 * @brief Displays the startup ASCII art banner.
 * Reads the file specified by path and prints valid lines.
 * 
 * @param path Relative path to the banner file (e.g., "banners/acrobata.txt").
 */
void	print_banner(char *path);

/**
 * @brief Debug helper: Prints the content of the token list.
 * Format: TYPE: [ID] | VALUE: [STR]
 * 
 * @param tokens The head of the token list.
 */
void	print_tokens(t_token *tokens);

/**
 * @brief Standardized error printing function.
 * Prints to STDERR: "minishell: [cmd]: [msg]".
 * 
 * @param cmd The command name generating the error.
 * @param msg The error message description.
 */
void	print_error(char *cmd, char *msg);

/* ************************************************************************** */
/*                          MEMORY MANAGEMENT                                 */
/* ************************************************************************** */

/**
 * @brief Frees the entire linked list of tokens.
 * 
 * @param tokens The head of the token list.
 */
void	free_tokens(t_token *tokens);

/**
 * @brief Frees the entire command pipeline structure.
 * Recursively frees arguments arrays and nested redirection lists.
 * 
 * @param cmds The head of the command list.
 */
void	free_commands(t_command *cmds);

/**
 * @brief Frees the entire environment variable list.
 * 
 * @param head The head of the environment list.
 */
void	free_env_list(t_env *head);

/**
 * @brief Frees a single environment node.
 * Frees the key, the value, and the node pointer itself.
 * 
 * @param node The node to free.
 */
void	free_node(t_env *node);

/**
 * @brief Frees the list of redirections associated with a command.
 * 
 * @param redirs The head of the redirection list.
 */
void	free_redirs(t_redir *redirs);

/**
 * @brief 
 * 
 */
void	clean_child_exit(int status, t_env **env, char *path, char **mat, t_command *cmds);

#endif