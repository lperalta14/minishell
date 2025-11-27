#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_

	(void)argc;
	(void)argv;
	// TODO: Inicializar señales (signal/sigaction)
	// TODO: Guardar envp en una estructura global
	if ( isatty(STDIN_FILENO))//test (isatty solo muest banner si interact)
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
		printf("%s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
