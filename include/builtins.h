#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Dispatcher
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env);

// Builtins individuales
int		ft_echo(char **args);
int		ft_cd(char **args, t_env **env);
int		ft_pwd(void);
int		ft_export(t_command *cmd, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_env(t_env *env);
int		ft_exit(char **args);

//utils
t_env	*find_env(t_env *env, char *key);
void	sort_env_tab(t_env **tab, int size);
t_env	**get_sorted_tab(t_env *env, int count);
int		print_sorted_env(t_env *env);

#endif