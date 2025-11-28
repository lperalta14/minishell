#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"
# include "lexer.h"

typedef struct s_token t_token; 

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

#endif