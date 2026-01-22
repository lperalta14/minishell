/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:48 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/22 20:14:49 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef enum e_quote_type	t_quote_type;

char	*get_env_value(t_env *env, char *key);
int		has_dollar(char *str);
int		get_var_value_len(char *str, int *i, t_env *env);
void	expand_variables(char **str, t_quote_type quote, t_env *env);
char	*extract_special_var(char c, int *i);
int		calculate_expanded_len(char *str, t_env *env);
char	*extract_var_name(char *str, int *i);
void	copy_expanded_content(char *dst, char *src, t_env *env);
int		copy_var_value(char *dst, char *src, int *i, t_env *env);
#endif