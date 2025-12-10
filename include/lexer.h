#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_R_IN,
	TK_R_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_LPAREN,
	TK_RPAREN,
	TK_END,
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
	//int				elimquot;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer_state
{
	char			*input;
	int				pos;
	int				len;
	int				elimquote;
	t_quote_type	quote;
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
 * @param c 
 * @return int 
 */
int	 is_word(char c);

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

char	*join_token_value(char *old, char *add);
t_token *last_token(t_token *tokens);
t_token	*init_token(char *line, t_token *tokens);

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

t_token	*tokenize(t_token *tokens, t_lexer_state *st);

/**
 * @brief 
 * 
 * @param state 
 * @param tokens 
 */
void check_operator(t_lexer_state *state, t_token **tokens);

void count_quote(t_lexer_state *st, char quote, int end);

void	clean_quote(char *str, t_lexer_state *st, int end, char quote);

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
t_token	*try_extract_quoted(t_lexer_state *st);

/**
 * @brief Checks whether the character at a given position is a valid quote.
 * 
 * This function verifies if the character at index `pos` in the string `str`
 * is a valid single or double quote. A double quote preceded by a backslash
 * (`\`) is considered escaped and therefore NOT valid as a quote delimiter.
 * Single quotes are always treated as valid since they cannot be escaped
 * in standard shell syntax.
 * 
 * @param str The input string to evaluate.
 * @param pos The position of the character to check within the string.
 * @return 1 if the character is a valid quote delimiter, 0 otherwise.
 */
int	is_valid_quote(char *str, int pos);

char *clean_scape(char *dst, char *src, int len);

#endif