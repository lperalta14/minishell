#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Dispatcher
int     is_builtin(char *cmd);
int     execute_builtin(t_command *cmd, t_env **env);

// Builtins individuales
int		ft_echo(char **args);
int		ft_cd(char **args, t_env **env);
int     ft_pwd(void);
int     ft_export(char **args, t_env **env);
int     ft_unset(char **args, t_env **env);
int     ft_env(t_env *env);
int		ft_exit(char **args);

#endif