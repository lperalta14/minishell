/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:11:32 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 18:19:53 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/********************************************************/
/*						DISPATCHER						*/
/********************************************************/

/**
 * @brief Checks if a command is a builtin.
 * @param cmd Command name to check.
 * @return 1 if builtin, 0 otherwise.
 */
int		is_builtin(char *cmd);

/**
 * @brief Executes the corresponding builtin function.
 * @param cmd Command structure containing args.
 * @param env Double pointer to environment list.
 * @return Exit status of the builtin.
 */
int		execute_builtin(t_command *cmd, t_env **env);

/********************************************************/
/*						BUILTINGS						*/
/********************************************************/

/**
 * @brief Implementation of echo command. Prints args to stdout.
 * @param args Command arguments.
 * @return 0 on success.
 */
int		ft_echo(char **args);

/**
 * @brief Implementation of cd command. Changes current directory.
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 * @return 0 on success, 1 on error.
 */
int		ft_cd(t_command *cmd, t_env **env);

/**
 * @brief Implementation of pwd command. Prints current working directory.
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 * @return 0 on success.
 */
int		ft_pwd(t_command *cmd, t_env **env);

/**
 * @brief Implementation of export command. Adds/updates env vars.
 * @param cmd Command structure.
 * @param env Double pointer to environment list.
 * @return 0 on success.
 */
int		ft_export(t_command *cmd, t_env **env);

/**
 * @brief Implementation of unset command. Removes env vars.
 * @param args Command arguments (variable names).
 * @param env Double pointer to environment list.
 * @return 0 on success.
 */
int		ft_unset(char **args, t_env **env);

/**
 * @brief Implementation of env command. Prints environment variables.
 * @param env Environment list.
 * @param args Command arguments.
 * @return 0 on success.
 */
int		ft_env(t_env *env, char **args);

/**
 * @brief Implementation of exit command. Exits the shell.
 * @param args Command arguments (optional exit code).
 * @return Exit code.
 */
int		ft_exit(char **args);

/********************************************************/
/*						UTILS							*/
/********************************************************/

/**
 * @brief Finds an environment variable node by key.
 * @param env Environment list.
 * @param key Variable name to find.
 * @return Pointer to node or NULL if not found.
 */
t_env	*find_env(t_env *env, char *key);

/**
 * @brief Sorts an array of environment pointers.
 * @param tab Array of pointers to env nodes.
 * @param size Size of the array.
 */
void	sort_env_tab(t_env **tab, int size);

/**
 * @brief Creates a sorted array of environment pointers.
 * @param env Environment list.
 * @param count Number of nodes.
 * @return Array of pointers to env nodes.
 */
t_env	**get_sorted_tab(t_env *env, int count);

/**
 * @brief Prints export-style sorted environment variables.
 * @param env Environment list.
 * @return 0 on success.
 */
int		print_sorted_env(t_env *env);

/**
 * @brief Gets value of specific path variable or similar.
 * @param env Environment list.
 * @param var Variable name (e.g., "HEAD").
 * @param len Length of name.
 * @return Value string.
 */
char	*get_env_path(t_env *env, char *var, size_t len);

/**
 * @brief Updates PWD and OLDPWD after directory change.
 * @param env Double pointer to environment list.
 * @param cur_dir Previous directory.
 * @param arg_path Destination path argument.
 */
void	update_pwds(t_env **env, char *cur_dir, char *arg_path);

/**
 * @brief Updates or adds an environment variable.
 * @param env Double pointer to environment list.
 * @param key Variable name.
 * @param value Variable value.
 */
void	update_env_var(t_env **env, char *key, char *value);

#endif