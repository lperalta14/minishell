/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:11:32 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 20:58:18 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Dispatcher
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env);

// Builtins individuales
int		ft_echo(char **args);
int		ft_cd(t_command *cmd, t_env **env);
//int		ft_pwd(void);
int		ft_pwd(t_command *cmd, t_env **env);
int		ft_export(t_command *cmd, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_env(t_env *env, char **args);
int		ft_exit(char **args, t_env **env);

//utils
t_env	*find_env(t_env *env, char *key);
void	sort_env_tab(t_env **tab, int size);
t_env	**get_sorted_tab(t_env *env, int count);
int		print_sorted_env(t_env *env);
char	*get_env_path(t_env *env, char *var, size_t len);
void	update_pwds(t_env **env, char *cur_dir, char *arg_path);
void	update_env_var(t_env **env, char *key, char *value);

#endif