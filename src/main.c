/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msedeno- <msedeno-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:14:11 by msedeno-          #+#    #+#             */
/*   Updated: 2026/01/28 10:21:21 by msedeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

static void	minishell(char *input, t_env **env)
{
	t_token		*tokens;
	t_command	*cmds;

	tokens = NULL;
	tokens = init_token(input, tokens, *env);
	// print_tokens(tokens);
	cmds = parse(tokens);
	if (tokens)
	{
		free_tokens(tokens);
		tokens = NULL;
	}
	if (cmds)
	{
		// print_commands(cmds);
		if (cmds->next)
			execute_pipeline(cmds, env);
		else
			execute_simple_cmd(cmds, env);
		free_commands(cmds);
	}
}

/**
 * @brief 
  * GNL returns the line with a trailing '\n', unlike readline.
  * We must strip the '\n' to ensure consistest parsing behavior.
 * @param env_list 
 */
static void	main_loop(t_env **env_list)
{
	char	*input;
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minihell> ");
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line)
			{
				input = ft_strtrim(line, "\n");
				free(line);
			}
			else
				input = NULL;
		}
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		minishell(input, env_list);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	setup_signals_interactive();
	if (isatty(STDIN_FILENO))
		print_banner("banners/acrobata.txt");
	main_loop(&env_list);
	if (isatty(STDIN_FILENO))
		print_banner("banners/bye.txt");
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
