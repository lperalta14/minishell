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
/**
 * @brief calculate the size of a list of env
 * 
 * @param env 
 * @return int 
 */
int		env_size(t_env *env);

/**
 * @brief convert a list of env to an array
 * 
 * @param env 
 * @return char** 
 */
char	**env_to_array(t_env *env);

/********************************************************/
/*					RUTAS DE ENTORNO					*/
/********************************************************/

/**
 * @brief find a valid path
 * 
 * @param cmd 
 * @param paths 
 * @return char* 
 */
char	*find_valid_path(char *cmd, char **paths);

/**
 * @brief Get the path object
 * 
 * @param cmd 
 * @param env 
 * @return char* 
 */
char	*get_path(char *cmd, t_env *env);

/********************************************************/
/*						EXECUTER						*/
/********************************************************/

/**
 * @brief EJECUTAR UN SOLO COMANDO
 * 
 * @param cmd 
 * @param env 
 */
void	execute_simple_cmd(t_command *cmd, t_env **env);

/**
 * @brief Revisar si hay redirecciones
 * @param cmd 
 */
int		check_redirs(t_command *cmd);

/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 */
void	execute_child(t_command *cmd, t_env **env);

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

#endif