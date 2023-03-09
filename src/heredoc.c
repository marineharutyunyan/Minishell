#include "mini.h"

int	heredoc(t_red *head_red)
{
	pid_t	pid;
	char	*line;
	char	*full_line;
	int		status;

	full_line = ft_strdup("");
	if (pipe(head_red->heredoc_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		handle_signals(!INTERACTIVE_MODE);
		while (1)
		{
			set_term_attr(1);
			line = readline("> ");
			set_term_attr(0);
			if (line == NULL)
			{
				if (full_line[0] != '\0')
					full_line = ft_strjoin(full_line, "\n");
				break ;
			}
			if ((full_line[0] != '\0' && full_line[0] != '\n') || line[0] == '\0')// TODO make readable
				full_line = ft_strjoin(full_line, "\n");
			if (ft_strcmp(line, head_red->pathname) == 0)
				break ;
			else
				full_line = ft_strjoin(full_line, line);
		}
		ft_printf(head_red->heredoc_fd[1], "%s", full_line);
		// close(head_red->heredoc_fd[0]);
		close(head_red->heredoc_fd[1]);
		exit(0);
	}
	close(head_red->heredoc_fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	// handle_signals(INTERACTIVE_MODE);
	// handle_signals(INTERACTIVE_MODE);
	// printf("%d\n", WTERMSIG(status));
	if (WIFSIGNALED(status) && write(1, "\n", 1))
		return (WTERMSIG(status));
	return (WEXITSTATUS(status));
	// c[read(head_red->heredoc_fd[0], c, 5)] = 0;
	// printf("c = %s\n", c);
}
