#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../src/my_lib/includes/libft.h"

#define RED "\033[38;5;196m"
#define ORANGE "\033[38;5;208m"
#define YELLOW "\033[38;5;226m"
#define GREEN "\033[38;5;46m"
#define BLUE "\033[38;5;21m"
#define PURPLE "\033[38;5;129m"
#define NC "\033[0m"

void	open_banner(void);
void	print_banner(char *text);

#endif