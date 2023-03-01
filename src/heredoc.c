#include "mini.h"

void heredoc(t_red *head_red)
{
    pid_t pid;
    char *line;
    char *full_line;
    int		status;
    char c[100];

    full_line = ft_strdup("");
    pipe(head_red->heredoc_fd);
    pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            line = readline("> ");
            if ((full_line[0] != '\0' && full_line[0] != '\n') || line[0] == '\0')// TODO make readable
                full_line = ft_strjoin(full_line, "\n");
            if (ft_strcmp(line, head_red->pathname) == 0)
                break;
            else
                full_line = ft_strjoin(full_line, line);
        }
        ft_printf(head_red->heredoc_fd[1], "%s", full_line);
        // close(head_red->heredoc_fd[0]);
		close(head_red->heredoc_fd[1]);
        // printf("full line = %s\n", full_line);
    }
    close(head_red->heredoc_fd[1]);
    waitpid(-1, &status, 0);
	// c[read(head_red->heredoc_fd[0], c, 5)] = 0;
	// printf("c = %s\n", c);
}
