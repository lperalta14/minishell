/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:11:32 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 20:15:00 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* ************************************************************************** */
/*                              DISPATCHER                                    */
/* ************************************************************************** */

/**
 * @brief Checks if a command name corresponds to an internal shell builtin.
 * 
 * @param cmd The command name string (e.g., "echo", "cd").
 * @return int The builtin ID (or 1) if found, 0 otherwise.
 */
int		is_builtin(char *cmd);

/**
 * @brief Routes the command execution to the specific builtin function.
 * 
 * @param cmd Pointer to the command structure containing arguments.
 * @param env Pointer to the environment list pointer (for modification).
 * @return int The exit status of the builtin function.
 */
int		execute_builtin(t_command *cmd, t_env **env);

/* ************************************************************************** */
/*                          BUILTIN COMMANDS                                  */
/* ************************************************************************** */

/**
 * @brief Replicates the 'echo' command. Prints arguments to STDOUT.
 * Handles the '-n' flag to suppress the trailing newline.
 * 
 * @param args Array of command arguments.
 * @return int Always returns 0.
 */
int		ft_echo(char **args);

/**
 * @brief Replicates the 'cd' command. Changes the current working directory.
 * Updates PWD and OLDPWD environment variables upon success.
 * 
 * @param cmd Pointer to the command structure.
 * @param env Pointer to the environment list pointer.
 * @return int 0 on success, 1 on failure.
 */
int		ft_cd(t_command *cmd, t_env **env);

/**
 * @brief Replicates the 'pwd' command. Prints the current working directory.
 * 
 * @param cmd Pointer to the command structure (unused usually).
 * @param env Pointer to the environment list pointer (unused usually).
 * @return int 0 on success.
 */
int		ft_pwd(t_command *cmd, t_env **env);

/**
 * @brief Replicates the 'export' command.
 * If args are present, adds/updates variables in KEY=VALUE format.
 * If no args are present, prints the environment sorted alphabetically.
 * 
 * @param cmd Pointer to the command structure.
 * @param env Pointer to the environment list pointer.
 * @return int 0 on success, 1 on error.
 */
int		ft_export(t_command *cmd, t_env **env);

/**
 * @brief Replicates the 'unset' command. Removes variables from the environment.
 * 
 * @param args Array of strings containing keys to remove.
 * @param env Pointer to the environment list pointer.
 * @return int Always returns 0.
 */
int		ft_unset(char **args, t_env **env);

/**
 * @brief Replicates the 'env' command. Prints all environment variables.
 * Only prints variables that have an assigned value.
 * 
 * @param env Pointer to the environment list.
 * @param args Array of arguments (used to check for illegal flags/args).
 * @return int 0 on success, 127 if arguments/flags are provided (standard).
 */
int		ft_env(t_env *env, char **args);

/**
 * @brief Replicates the 'exit' command. Terminates the shell.
 * Validates if the first argument is numeric to set the specific exit code.
 * Fails if there are too many arguments.
 * 
 * @param args Array of arguments.
 * @param env Pointer to the environment list pointer (for cleanup).
 * @return int Does not return on success; 1 on failure (e.g., too many args).
 */
int		ft_exit(char **args, t_env **env);

/* ************************************************************************** */
/*                                UTILS                                       */
/* ************************************************************************** */

/**
 * @brief Searches for a specific node in the environment list by key.
 * 
 * @param env The environment list.
 * @param key The key string to search for.
 * @return t_env* Pointer to the found node, or NULL if not found.
 */
t_env	*find_env(t_env *env, char *key);

/**
 * @brief Sorts an array of environment nodes alphabetically by key.
 * Used by export without arguments.
 * 
 * @param tab Array of pointers to t_env nodes.
 * @param size The number of elements in the array.
 */
void	sort_env_tab(t_env **tab, int size);

/**
 * @brief creates a temporary array of pointers to env nodes and sorts it.
 * 
 * @param env The source environment list.
 * @param count The number of nodes in the list.
 * @return t_env** A null-terminated array of pointers, sorted.
 */
t_env	**get_sorted_tab(t_env *env, int count);

/**
 * @brief Handles the logic for displaying 'export' with no arguments.
 * Creates a sorted copy of env and prints it with "declare -x" format.
 * 
 * @param env The environment list.
 * @return int Always returns 0.
 */
int		print_sorted_env(t_env *env);

/**
 * @brief Retrieves the value of a specific env variable (safe wrapper).
 * 
 * @param env The environment list.
 * @param var The key to search for (e.g., "HOME").
 * @param len The length of the key to compare.
 * @return char* The value string, or NULL if not found.
 */
char	*get_env_path(t_env *env, char *var, size_t len);

/**
 * @brief DEPRECATED/STATIC: Helper for cd variable updates.
 * (Usually static inside cd.c now, but kept if you use it elsewhere).
 */
void	update_pwds(t_env **env, char *cur_dir, char *arg_path);

/**
 * @brief Creates or updates an environment variable node.
 * If 'key' exists, updates 'value'. If not, adds a new node.
 * 
 * @param env Pointer to the environment list pointer.
 * @param key The variable name.
 * @param value The variable value.
 */
void	update_env_var(t_env **env, char *key, char *value);

#endif