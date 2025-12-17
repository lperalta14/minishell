#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/my_lib/includes/libft.h"
# include "utils.h"
# include "lexer.h"
# include "parser.h"
# include "executer.h"
# include "expander.h"
# include "builtins.h"

#define RED "\033[38;5;196m"
#define ORANGE "\033[38;5;208m"
#define YELLOW "\033[38;5;226m"
#define GREEN "\033[38;5;46m"
#define BLUE "\033[38;5;21m"
#define PURPLE "\033[38;5;129m"
#define NC "\033[0m"

#endif