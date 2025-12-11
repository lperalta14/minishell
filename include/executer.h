#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;   // Ej: "PATH"
	char			*value; // Ej: "/bin:/usr/bin"
	struct s_env	*next;
}	t_env;

/********************************************************/
/*				VARIABLES DE ENTORNO					*/
/********************************************************/

/**
 * @brief añadir variables de entorno a la lista
 * 
 * @param head 
 * @param new 
 */
void	add_env(t_env **head, t_env *new);

/**
 * @brief Get the env node object
 * 
 * @param str 
 * @return t_env* 
 */
t_env	*get_env_node(char *str);

/**
 * @brief encontrar variables de entorno
 * 
 * @param envp 
 * @return t_env* 
 */
t_env	*init_env(char **envp);

/********************************************************/
/*					RUTAS DE ENTORNO					*/
/********************************************************/
#endif