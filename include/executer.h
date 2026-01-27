/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:43 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/27 19:30:57 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

/**
 * @struct s_env
 * @brief Linked list structure to store environment variables.
 * 
 * @var s_env::key   The variable name (e.g., "PATH").
 * @var s_env::value The variable value (e.g., "/bin:/usr/bin").
 * @var s_env::next  Pointer to the next node.
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ************************************************************************** */
/*                              ENVIRONMENT VARS                              */
/* ************************************************************************** */

/**
 * @brief Adds a new environment node to the end of the linked list.
 * 
 * @param head Pointer to the address of the list head.
 * @param new Pointer to the new node to be added.
 */
void	add_env(t_env **head, t_env *new);

/**
 * @brief Creates a new environment node from a string (KEY=VALUE).
 * Parses the string to separate the key and the value.
 * 
 * @param str The string containing "KEY=VALUE".
 * @return t_env* Pointer to the newly created node, or NULL on 
 * allocation failure.
 */
t_env	*get_env_node(char *str);

/**
 * @brief Initializes the environment linked list from the main's char** envp.
 * 
 * @param envp The null-terminated array of environment strings.
 * @return t_env* Pointer to the head of the generated list.
 */
t_env	*init_env(char **envp);

/**
 * @brief Calculates the number of nodes in the environment list.
 * 
 * @param env The environment list.
 * @return int The number of variables (size).
 */
int		env_size(t_env *env);

/**
 * @brief Converts the environment linked list back to a char** array.
 * Essential for passing the environment to execve().
 * 
 * @param env The environment list.
 * @return char** A null-terminated array of "KEY=VALUE" strings.
 */
char	**env_to_array(t_env *env);

/* ************************************************************************** */
/*                              PATH HANDLING                                 */
/* ************************************************************************** */

/**
 * @brief Iterates through split paths to find an executable binary.
 * Checks for F_OK and X_OK permissions.
 * 
 * @param cmd The command name (e.g., "ls").
 * @param paths The array of split path directories.
 * @return char* The full absolute path to the binary, or NULL if not found.
 */
char	*find_valid_path(char *cmd, char **paths);

/**
 * @brief Main logic to retrieve the full path of a command.
 * Retrieves PATH variable, splits it, and calls find_valid_path.
 * 
 * @param cmd The command name.
 * @param env The environment list (to find PATH).
 * @return char* The full valid path, the cmd itself (if absolute), or NULL.
 */
char	*get_path(char *cmd, t_env *env);

/* ************************************************************************** */
/*                                EXECUTOR                                    */
/* ************************************************************************** */

/**
 * @brief excutes a single command (no pipes).
 * Handles both builtins (in parent) and external commands (forking).
 * 
 * @param cmd Pointer to the command structure.
 * @param env Pointer to the environment list pointer.
 */
void	execute_simple_cmd(t_command *cmd, t_env **env);

/**
 * @brief The child process logic for external commands.
 * Handles path resolution and calls execve().
 * 
 * @param cmd Pointer to the command structure.
 * @param env Pointer to the environment list pointer.
 */
void	execute_child(t_command *cmd, t_env **env, t_command *cmds_head);

/* ************************************************************************** */
/*                                HEREDOCS                                    */
/* ************************************************************************** */

/**
 * @brief Processes a single heredoc node.
 * Reads input until delimiter is found and writes to the IO fd.
 * 
 * @param redir The redirection node containing the delimiter.
 * @param io_fd Pointer to the FD where input should be written.
 * @return int 0 on success, status code on failure/interrupt.
 */
int		handle_heredoc(t_redir *redir,t_command *cmd,t_env **env, t_command *cmds_head);

/**
 * @brief Pre-scans the command list to process all heredocs.
 * Bash processes all heredocs before starting any execution.
 * 
 * @param cmd The head of the command list.
 * @return int 0 on success, or error code if interrupted.
 */
int		handle_heredocs_before_pipeline(t_command *cmd, t_env **env, t_command *cmds_head);

/**
 * @brief Signal handler specifically for interruptions during heredoc input.
 * 
 * @param sig The signal number received (SIGINT).
 */
void	handle_sigint_heredoc(int sig);

/**
 * @brief Checks if the current heredoc is the last input redirection.
 * Only the last heredoc/input actually feeds the command stdin.
 * 
 * @param redir The current redirection node.
 * @return int 1 if it is the last input source, 0 otherwise.
 */
int		is_last_heredoc(t_redir *redir);

/**
 * @brief Helper to translate redirection types to open() flags.
 * 
 * @param type The redirection type ID.
 * @return int The corresponding flags (e.g., O_TRUNC, O_APPEND).
 */
int		get_flags(int type);

/* ************************************************************************** */
/*                                PIPELINES                                   */
/* ************************************************************************** */

/**
 * @brief Manages the execution of a pipeline (multiple commands connected by |).
 * Creates pipes, forks children, and manages duplication of FDs.
 * 
 * @param cmd The head of the command list.
 * @param env Pointer to the environment list pointer.
 */
void	execute_pipeline(t_command *cmd, t_env **env);

/* ************************************************************************** */
/*                              REDIRECTIONS                                  */
/* ************************************************************************** */

/**
 * @brief Handles cases where a command node has redirections but no arguments.
 * Example: "> file.txt" (creates file, does not execute command).
 * 
 * @param cmd The command node.
 */
void	handle_redirs_only(t_command *cmd);

/**
 * @brief Iterates through the redirection list and applies them.
 * Opens files and performs dup2() for Stdin/Stdout.
 * 
 * @param cmd The command node containing redirections.
 * @return int 0 on success, 1 on failure (e.g., file permission denied).
 */
int		check_redirs(t_command *cmd);

#endif