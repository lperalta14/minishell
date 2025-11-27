#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"


typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_END,
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_DOUBLE,
	QUOTE_SINGLE
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer_state
{
	char *input;
	int pos;
	int len;
}	t_lexer_state;

/********************************************************/
/*						UTILS_TOKENS.C					*/
/********************************************************/

/**
 * @brief Salta espacios y tabulaciones en el input
 * 
 * @param state Estado del lexer con posición actual
 */
void	skip_spaces(t_lexer_state *state);

/**
 * @brief 
 * 
 * @param c 
 * @return int 
 */
int	is_operator(char c);

/**
 * @brief 
 * 
 * @param type 
 * @param value 
 * @return t_token* 
 */
t_token	*createtoken(t_token_type type, char *value);

/**
 * @brief 
 * 
 * @param head 
 * @param new 
 */
void	add_token(t_token **head, t_token *new);

/********************************************************/
/*						TOKEN.C							*/
/********************************************************/

/**
 * @brief Construct a new extract word object
 * 
 * @param state
 * @param tokens Puntero a la lista de tokens
 */
void	extract_word(t_lexer_state *state, t_token **tokens);

void	tokenize();

/**
 * @brief 
 * 
 * @param state 
 * @param tokens 
 */
void check_operator(t_lexer_state *state, t_token **tokens);

/********************************************************/
/*						QUOTES.C						*/
/********************************************************/
/**
 * @brief 
 * 
 * @param st 
 * @param tokens 
 * @return int 
 */
int	try_extract_quoted(t_lexer_state *st, t_token **tokens, t_token *token);

#endif