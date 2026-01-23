/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:53 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/23 18:12:25 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	QUOTE_SINGLE,
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
	char			*input;
	int				pos;
	int				len;
	t_quote_type	quote;
	t_env			*env;
}	t_lexer_state;

/********************************************************/
/*						UTILS_TOKENS.C					*/
/********************************************************/

/**
 * @brief Skips whitespaces and tabs in the input.
 * 
 * @param state Lexer state with current position.
 */
void	skip_spaces(t_lexer_state *state);

/**
 * @brief Checks if a character is a special operator.
 * 
 * @param c Character to check.
 * @return 1 if operator, 0 otherwise.
 */
int		is_operator(char c);

/**
 * @brief Checks if a character is part of a word.
 * 
 * @param c Character to check.
 * @return 1 if word char, 0 otherwise.
 */
int		is_word(char c);

/**
 * @brief Creates a new token with given type and value.
 * 
 * @param type Type of the token.
 * @param value String value of the token.
 * @return Pointer to new token node.
 */
t_token	*createtoken(t_token_type type, char *value);

/**
 * @brief Adds a token to the end of the token list.
 * 
 * @param head Pointer to the head of the list.
 * @param new New token to add.
 */
void	add_token(t_token **head, t_token *new);

/**
 * @brief Joins a new string to an existing token value.
 * @param old Old value string.
 * @param add String to append.
 * @return New allocated string.
 */
char	*join_token_value(char *old, char *add);

/**
 * @brief Handles joining quoted segments to adjacent tokens.
 * @param Extracts a word token from the input.
 * 
 * @param state Lexer state.
 * @return The extracted token.
 */
t_token	*extract_word(t_lexer_state *state);

/**
 * @brief Main tokenization loop.
 * 
 * @param tokens Current list of tokens.
 * @param st Lexer state.
 * @return Updated list of tokens.
 */
t_token	*tokenize(t_token *tokens, t_lexer_state *st);

/**
 * @brief Checks for and extracts operator tokens at current position.
 * 
 * @param state Lexer state.
 * @param tokens Double pointer to token list.
 */
void	check_operator(t_lexer_state *state, t_token **tokens);

/**
 * @brief Cleans quotes from a string segment.
 * 
 * @param str Destination buffer.
 * @param st Lexer state.
 * @param end End index in input.
 * @param quote Quote character found.
 * @return Head of token list.
 */
t_token	*init_token(char *line, t_token *tokens, t_env *env);

/********************************************************/
/*						TOKEN.C							*/
/********************************************************/

/**
 * @brief Construct a new extract word object
 * 
 * @param state
 * @param tokens Puntero a la lista de tokens
 */
t_token	*extract_word(t_lexer_state *state);

t_token	*tokenize(t_token *tokens, t_lexer_state *st);

/**
 * @brief Attempts to extract a quoted section as a token.
 * 
 * @param st Lexer state.
 * @return Extracted token or NULL.
 */
void	check_operator(t_lexer_state *state, t_token **tokens);

/**
 * @brief 
 * 
 * @param str 
 * @param st 
 * @param end 
 * @param quote 
 */
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
int		is_valid_quote(char *str, int pos);

/**
 * @brief Removes escape characters (backslashes) from string.
 * @param dst Destination buffer.
 * @param src Source string.
 * @param len Length to process.
 * @return Pointer to cleaned string.
 */
char	*clean_scape(char *dst, char *src, int len);

#endif