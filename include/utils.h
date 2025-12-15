#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_env		t_env;
typedef struct s_redir		t_redir;

/*******************************************************/
/*							PRINTS						*/
/********************************************************/

void	free_tokens(t_token *tokens);

/*void	free_commands(t_command *cmds);*/

/**
 * @brief 
 * 
 * @param text 
 */
void	print_banner(char *text);

/**
 * @brief 
 * 
 * @param tokens 
 */
void	print_tokens(t_token *tokens);

/********************************************************/
/*					GESTION DE MEMORIA					*/
/********************************************************/

/**
 * @brief liberar lista de env
 * 
 * @param head 
 */
void	free_env_list(t_env *head);

/**
 * @brief libera tokens
 * 
 * @param tokens
 */
void	free_tokens(t_token *tokens);

/**
 * @brief libera comandos
 * 
 * @param cmds 
 */
void	free_commands(t_command *cmds);

/**
 * @brief libera redirecciones
 * 
 * @param redirs 
 */
void	free_redirs(t_redir *redirs);


#endif