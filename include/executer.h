#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_env
{
	char			*path;   // Ej: "PATH"
	char			*value; // Ej: "/bin:/usr/bin"
	struct s_env	*next;
}	t_env;

#endif