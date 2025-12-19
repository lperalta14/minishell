#include "../include/minishell.h"

volatile sig_atomic_t g_exit_status = 0;

static void	minishell(char *input, t_env *env)
{
	t_token		*tokens;
	t_command	*cmds;
	//int			g_exit_status;

	tokens = NULL;
	tokens = init_token(input, tokens, env);
	print_tokens(tokens);
	cmds = parse(tokens);
	if (cmds)
	{
		print_commands(cmds);
		execute_simple_cmd(cmds, env);
		free_commands(cmds);
	}
	if (tokens)
		free_tokens(tokens);
}

static void	main_loop(t_env *env_list)
{
	char	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minihell> ");
		else
			input = readline("");
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
	//char	*input;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	setup_signals_interactive();
	if (isatty(STDIN_FILENO))
		print_banner("banners/acrobata.txt");
	main_loop(env_list);
	/*while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minihell> ");
		else
			input = readline("");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		minishell(input, env_list);
		free(input);
	}*/
	if (isatty(STDIN_FILENO))
		print_banner("banners/bye.txt");
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
