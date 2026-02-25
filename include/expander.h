/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimarasn <casimarasn@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:48 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/25 20:20:23 by casimarasn       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

// Forward declaration of the quote enum to avoid circular dependency
typedef enum e_quote_type	t_quote_type;

/* ************************************************************************** */
/*                              EXPANDER LOGIC                                */
/* ************************************************************************** */

/**
 * @brief Retrieves the string value of an environment variable.
 * Wraps find_env() logic returning just the value char*.
 * 
 * @param env The environment list.
 * @param key The variable name to search.
 * @return char* The variable value, or an empty string ("") if not found.
 */
char	*get_env_value(t_env *env, char *key);

/**
 * @brief Scans a string to check for the presence of the '$' expansion symbol.
 * 
 * @param str The string to check.
 * @return int 1 (true) if a valid '$' is found, 0 (false) otherwise.
 */
int		has_dollar(char *str);

/**
 * @brief Calculates the length of a variable's value for memory allocation.
 * Advances the iterator 'i' past the variable name.
 * 
 * @param str The source string starting at the '$'.
 * @param i Pointer to the current index iterator.
 * @param env The environment list.
 * @return int The length of the expanded value string.
 */
int		get_var_value_len(char *str, int *i, t_env *env);

/**
 * @brief Main function to replace variables ($VAR) with their values 
 * in a string.
 * Modifies the string in-place (reallocating if necessary).
 * 
 * @param str Address of the string pointer (char**) to modify.
 * @param quote Context: QUOTE_DOUBLE (expands) or QUOTE_NONE (expands).
 * @param env The environment list.
 */
void	expand_variables(char **str, t_quote_type quote, t_env *env);

/**
 * @brief Handles special shell variables like "$?".
 * 
 * @param c The character after '$' (e.g., '?').
 * @param i Pointer to the iterator to advance.
 * @return char* The string representation of the special value 
 * (e.g., exit code).
 */
char	*extract_special_var(char c, int *i);

/**
 * @brief Pre-calculates the total length of the string after all expansions.
 * Essential to malloc the correct size for the new string.
 * 
 * @param str The original string with '$'.
 * @param env The environment list.
 * @return int The total length required for the result.
 */
int		calculate_expanded_len(char *str, t_env *env);

/**
 * @brief Parses and extracts the variable name string after a '$'.
 * Advances the index 'i' to the end of the name.
 * 
 * @param str The source string.
 * @param i Pointer to the current index iterator.
 * @return char* The variable name substring (malloc'd).
 */
char	*extract_var_name(char *str, int *i);

/**
 * @brief Expands the content from source to destination buffer.
 * Performs the actual copying of characters and variable values.
 * 
 * @param dst The pre-allocated destination buffer.
 * @param src The original source string.
 * @param env The environment list.
 */
void	copy_expanded_content(char *dst, char *src, t_env *env);

/**
 * @brief Helper for expansion copying.
 * Finds the variable value in env and copies it into 'dst'.
 * 
 * @param dst The destination buffer at the current write position.
 * @param src The source string at the variable position.
 * @param i Pointer to the source index iterator (updates it).
 * @param env The environment list.
 * @return int The number of characters written to 'dst'.
 */
int		copy_var_value(char *dst, char *src, int *i, t_env *env);

#endif