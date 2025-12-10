#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_command	t_command;

/********************************************************/
/*							PRINTS						*/
/********************************************************/

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

#endif