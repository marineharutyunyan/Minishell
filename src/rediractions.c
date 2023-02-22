#include "mini.h"

void handle_rediractions(t_general *g_data)
{
    int i = -1;
	while (g_data->pipe_count > ++i)
	    ft_redir_iter(&g_data->pipes[i]);
}

int	ft_redir_iter(t_pipe *pipe)
{
	while (pipe->head_red)
	{
		if (pipe->head_red->flag == O_TRUNC || pipe->head_red->flag == O_APPEND)
		{
			if (pipe->fd_out != 1)
				close(pipe->fd_out);
			pipe->fd_out = open(pipe->head_red->pathname, O_CREAT | pipe->head_red->flag | O_RDWR, 0777);
			if(pipe->fd_out == -1)
			{
				ft_printf(2, "Minishell: %s: %s\n", pipe->head_red->pathname, strerror(errno));
				return (1);
			}
		}
		else if (pipe->head_red->flag == O_RDONLY /*|| pipe->head_red->flag == HEREDOC*/)
		{
			if (pipe->fd_in != 0)
				close(pipe->fd_in);
			pipe->fd_in = open(pipe->head_red->pathname, pipe->head_red->flag);
			if(pipe->fd_in == -1)
			{
				ft_printf(2, "Minishell: %s: %s\n", pipe->head_red->pathname, strerror(errno));
				return (1);
			}
		}
		// printf("Pathname = %s\n", pipe->head_red->pathname);
		// printf("flage = %d\n", pipe->head_red->flag);
		pipe->head_red = pipe->head_red->next;
	}
	// printf("in = %d\n", pipe->fd_in);
	// printf("out = %d\n", pipe->fd_out);
	return (0);
}
