/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:43 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 19:08:17 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/********************************************************/
/*						ENV								*/
/********************************************************/

/**
 * @brief Adds a new environment variable node to the list.
 * 
 * @param head Pointer to the head of the list.
 * @param new New node to add.
 */
void	add_env(t_env **head, t_env *new);

/**
 * @brief Creates a new environment node from a string "KEY=VALUE".
 * 
 * @param str The string to parse.
 * @return Pointer to the new node.
 */
t_env	*get_env_node(char *str);

/**
 * @brief Initializes the environment linked list from envp array.
 * 
 * @param envp Array of environment strings.
 * @return Pointer to the head of the list.
 */
t_env	*init_env(char **envp);
/**
 * @brief Calculates the size of the environment list.
 * 
 * @param env Pointer to the list.
 * @return Number of nodes.
 */
int		env_size(t_env *env);

/**
 * @brief Converts the environment list to an array of strings.
 * 
 * @param env Pointer to the list.
 * @return Null-terminated array of strings.
 */
char	**env_to_array(t_env *env);

/********************************************************/
/*							PATH						*/
/********************************************************/

/**
 * @brief Finds a valid executable path for a command.
 * 
 * @param cmd Command name.
 * @param paths Array of path directories.
 * @return Full path to executable or NULL.
 */
char	*find_valid_path(char *cmd, char **paths);

/**
 * @brief Gets the full path for a command using env list.
 * 
 * @param cmd Command name.
 * @param env Environment list.
 * @return Full path to executable.
 */
char	*get_path(char *cmd, t_env *env);

/********************************************************/
/*						EXECUTER						*/
/********************************************************/

/**
 * @brief Executes a single command (no pipes).
 * 
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 */
void	execute_simple_cmd(t_command *cmd, t_env **env);

/**
 * @brief Executes a simple command in a child process.
 * 
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 */
void	execute_child(t_command *cmd, t_env **env);

/**
 * @brief Handles reading input for a heredoc redirection.
 * 
 * @param redir Redirection structure.
 * @param is_last Flag indicating if this is the last heredoc.
 * @return 0 on success.
 */
int		handle_heredoc(t_redir *redir, int is_last);

/**
 * @brief Processes all heredocs in the command tree before execution.
 * 
 * @param cmd Command structure.
 * @return 0 on success.
 */
int		handle_heredocs_before_pipeline(t_command *cmd);

/**
 * @brief Signal handler for SIGINT during heredoc input.
 * 
 * @param sig Signal number.
 */
void	handle_sigint_heredoc(int sig);

/**
 * @brief Checks if a redirection is the last heredoc in the list.
 * 
 * @param redir Redirection structure.
 * @return 1 if last, 0 otherwise.
 */
int		is_last_heredoc(t_redir *redir);

/**
 * @brief Gets open flags based on redirection type.
 * 
 * @param type Redirection type.
 * @return Flags for open().
 */
int		get_flags(int type);

/********************************************************/
/*						PIPES							*/
/********************************************************/

/**
 * @brief buscar si hay pipes
 * 
 * @param cmd 
 * @param env 
 */
void	execute_pipeline(t_command *cmd, t_env **env);

/** 
 * @brief executes a pipeline of commands.
 * 
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 */
void	execute_pipeline(t_command *cmd, t_env **env);

/********************************************************/
/*					REDIRECTIONS						*/
/********************************************************/
/**
 * @brief Handles redirections for commands with no arguments.
 * @param cmd Command structure.
 */
void	handle_redirs_only(t_command *cmd);

/**
 * @brief 
 * 
 * @param cmd 
 * @return int 
 */
int		check_redirs(t_command *cmd);

#endif