#include "../include/minishell.h"

void	minishell(char *input)
{
	t_token		*tokens;
	t_command	*cmds;

	tokens = NULL;
	tokens = init_token(input, tokens);
	//tokens = tokenize(input);
	print_tokens(tokens);
	cmds = parse(tokens);
	if (cmds)
	{
		print_commands(cmds);
		free_commands(cmds);
	}
	free(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	//t_token	*tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	// TODO: Inicializar señales (signal/sigaction)
	// TODO: Guardar envp en una estructura global
	if (isatty(STDIN_FILENO))
		print_banner("banners/acrobata.txt");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				print_banner("banners/bye.txt");
			break ;
		}
		add_history(input);
		// TODO: Llamar al lexer/parser aquí en lugar de printf
		minishell(input);
		//print_tokens(tokens);
		free(input);
	}
	rl_clear_history();
	return (0);
}
