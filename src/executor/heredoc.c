#include "../../include/minishell.h"

static void heredoc_sigint(int sig)
{
    (void)sig;
    printf("\n");
    exit(130);
}

static void heredoc_child(t_redir *redir, int *pipefd)
{
    char *line;

    signal(SIGINT, heredoc_sigint);
    close(pipefd[0]);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, redir->file) == 0)
        {
            free(line);
            break ;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    exit(0);
}

int handle_heredoc(t_redir *redir, int is_last)
{
    int     pipefd[2];
    pid_t   pid;
    int     status;

    if (pipe(pipefd) == -1)
        return (perror("minishell"), 1);
    pid = fork();
    if (pid == -1)
        return (perror("minishell"), 1);
    if (pid == 0)
        heredoc_child(redir, pipefd);
    close(pipefd[1]);
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
    {
        close(pipefd[0]);
        g_exit_status = 130;
        return (1);
    }
    if (is_last)
        dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    return (0);
}
