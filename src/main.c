#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc > 0 || argv[0] || envp)
	print_banner("banners/acrobata.txt");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			print_banner("banners/bye.txt");
			break;;
		}
		else
			add_history(input);
		printf("Input: %s\n", input);
		free(input);
	}
	return(0);
}