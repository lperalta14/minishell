/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:53 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 20:23:32 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/**
 * @enum e_token_type
 * @brief Identifies the grammatical category of a token.
 */
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

/**
 * @enum e_quote_type
 * @brief Context to track if a token was originally quoted.
 * Important for variable expansion rules.
 */
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_DOUBLE,
	QUOTE_SINGLE,
}	t_quote_type;

/**
 * @struct s_token
 * @brief Represents a lexical unit (token) in the linked list.
 * 
 * @var s_token::type  Category of the token (Word, Pipe, etc.).
 * @var s_token::value The actual string content of the token.
 * @var s_token::quote The quote context of the token.
 * @var s_token::next  Pointer to the next token in the list.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote;
	struct s_token	*next;
}					t_token;

/**
 * @struct s_lexer_state
 * @brief Holds the current state of the lexer machine.
 * 
 * @var s_lexer_state::input The full input string line.
 * @var s_lexer_state::pos   Current cursor position index.
 * @var s_lexer_state::len   Total length of input.
 * @var s_lexer_state::quote Current quote state being processed.
 * @var s_lexer_state::env   Pointer to env list (needed for expansion).
 */
typedef struct s_lexer_state
{
	char			*input;
	int				pos;
	int				len;
	t_quote_type	quote;
	t_env			*env;
}	t_lexer_state;

/* ************************************************************************** */
/*                              TOKEN UTILS                                   */
/* ************************************************************************** */

/**
 * @brief Advances the lexer cursor past spaces and tabs.
 * 
 * @param state The current lexer state.
 */
void	skip_spaces(t_lexer_state *state);

/**
 * @brief Checks if a character is a shell operator.
 * 
 * @param c The character to check.
 * @return int 1 if char is | < >, 0 otherwise.
 */
int		is_operator(char c);

/**
 * @brief Checks if a character belongs to a standard word.
 * 
 * @param c The character to check.
 * @return int 1 if char is not an operator or space.
 */
int		is_word(char c);

/**
 * @brief Allocates and initializes a new token node.
 * 
 * @param type The type of token (TK_WORD, etc.).
 * @param value The string content (will be duplicated).
 * @return t_token* Pointer to new node or NULL on failure.
 */
t_token	*createtoken(t_token_type type, char *value);

/**
 * @brief Appends a token to the end of the token list.
 * 
 * @param head Pointer to the head of the token list.
 * @param new The new token node to add.
 */
void	add_token(t_token **head, t_token *new);

/**
 * @brief Concatenates two strings to form a merged token value.
 * Used when joining parts like: word"quoted"word.
 * 
 * @param old The existing string.
 * @param add The string to append.
 * @return char* The new combined string.
 */
char	*join_token_value(char *old, char *add);

/**
 * @brief High-level logic to merge adjacent tokens if they are connected.
 * Handles cases like: echo "he"llo (becomes one argument).
 * 
 * @param st The lexer state.
 * @param tokens Pointer to the token list.
 * @return int status code.
 */
int		join_quote(t_lexer_state *st, t_token **tokens);

/**
 * @brief Returns the last node in the token list.
 * 
 * @param tokens The token list head.
 * @return t_token* Pointer to the last node.
 */
t_token	*last_token(t_token *tokens);

/**
 * @brief Main entry point for the Tokenizer.
 * Initializes the state struct and starts the tokenization loop.
 * 
 * @param line The raw input string from readline.
 * @param tokens The list head (usually NULL initially).
 * @param env The environment list (for expansion).
 * @return t_token* The head of the generated token list.
 */
t_token	*init_token(char *line, t_token *tokens, t_env *env);

/* ************************************************************************** */
/*                              TOKEN LOGIC                                   */
/* ************************************************************************** */

/**
 * @brief Extracts a standard unquoted word from the input.
 * Handles variable expansion if '$' exists.
 * 
 * @param state The lexer state.
 * @return t_token* The created word token.
 */
t_token	*extract_word(t_lexer_state *state);

/**
 * @brief The main lexer loop.
 * Iterates through input characters and dispatches to specific extractors.
 * 
 * @param tokens The current token list.
 * @param st The lexer state.
 * @return t_token* The updated token list.
 */
t_token	*tokenize(t_token *tokens, t_lexer_state *st);

/**
 * @brief Detects and handles operator tokens (| < << > >>).
 * Creates the appropriate token and advances the cursor.
 * 
 * @param state The lexer state.
 * @param tokens Address of the token list head.
 */
void	check_operator(t_lexer_state *state, t_token **tokens);

/**
 * @brief Helper to remove quote characters from a string.
 * NOTE: Often done during extraction, but this is a specific helper.
 * 
 * @param str The string to clean.
 * @param st The lexer state.
 * @param end The index where the quote ends.
 * @param quote The character of the quote (' or ").
 */
void	clean_quote(char *str, t_lexer_state *st, int end, char quote);

/* ************************************************************************** */
/*                              QUOTES HANDLING                               */
/* ************************************************************************** */

/**
 * @brief Attempts to extract a quoted string (single or double).
 * Checks if current char is a quote, finds the closing pair, 
 * extracts content, and expands variables if double quoted.
 * 
 * @param st The lexer state.
 * @return t_token* The created token or NULL if no valid quote found.
 */
t_token	*try_extract_quoted(t_lexer_state *st);

/**
 * @brief Checks whether the character at a given position is a valid quote.
 * A double quote preceded by a backslash is NOT valid (escaped).
 * 
 * @param str The input string.
 * @param pos The index to check.
 * @return int 1 if valid start of quote, 0 otherwise.
 */
int		is_valid_quote(char *str, int pos);

/**
 * @brief Removes escape characters (backslashes) inside double quotes.
 * 
 * @param dst Destination buffer.
 * @param src Source string.
 * @param len Length to process.
 * @return char* The cleaned string.
 */
char	*clean_scape(char *dst, char *src, int len);

#endif