#include "mini.h"

int	**create_pipes(int pipe_count)
{
	int	i;
	int	**fd; //TODO doesn't work with *fd[2]

	i = 0;
	fd = malloc(sizeof(int) * (pipe_count - 1));
	while (i < pipe_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
	return (fd);
}

void	close_all_fd(int	**fd, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	change_io(int **fd, int i, int pipe_count, t_pipe pipe)
{
	if (pipe_count > 1)
	{
		if (i == 0)
		{
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			else
				dup2(fd[i][1], 1);
		}
		else if (i == pipe_count - 1)
		{
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			else
				dup2(fd[i - 1][0], 0);
		}
		else
		{
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			else
				dup2(fd[i - 1][0], 0);
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			else
				dup2(fd[i][1], 1);
		}
	}
	else
	{
		dup2(pipe.fd_in, 0);
		dup2(pipe.fd_out, 1);
	}
}

void	print_pipes(int pipe_count, int **fd)
{
	int	i;

	printf("\n");
	i = 0;
	while (i < pipe_count - 1)
	{
		printf("fd[%d][0] = %d\n", i, fd[i][0]);
		printf("fd[%d][1] = %d\n", i, fd[i][1]);
		i++;
	}
}

int	set_execv_path(t_general *g_data, t_pipe *pipe)
{
	char	**paths;
	int		i;
	char	*fullpath;

	i = 0;
	paths = NULL;
	if (access(pipe->cmd_name, F_OK) != -1)
	{
		//TODO should I  also check if the command is execuatable with X_OK
		printf("path exist\n");
		return (free_double_array((void ***)&paths));
	}
	else
	{
		paths = ft_split(get_value_by_key("PATH", g_data->head_env), ':');
	}
	while (paths[i])
	{
		fullpath = ft_strjoin(paths[i], ft_strdup("/")); // TODO free on second argument insite join  
		fullpath = ft_strjoin(fullpath, pipe->cmd_name);// TODO free on  first argument insite join 
		if (access(fullpath, F_OK) != -1)
		{
			pipe->cmd_name = fullpath;
			paths = NULL;
			return (free_double_array((void ***)&paths));
		}
		i++;
	}
	return (free_double_array((void ***)&paths));
}

//  cat main.c | cat | cat
int	execute(t_general *g_data)
{
	int		status;
	int		i;
	int		**fd; //TODO doesn't work with *fd[2]

	i = 0;
	fd = create_pipes(g_data->pipe_count);
	while (i < g_data->pipe_count)
	{
		g_data->pipes[i].pid = fork(); // TODO check ret_value and handle exit status;
		if (g_data->pipes[i].pid == 0)
		{
			change_io(fd, i, g_data->pipe_count, g_data->pipes[i]);
			close_all_fd(fd, g_data->pipe_count);
			set_execv_path(g_data, &g_data->pipes[i]);
			execve(g_data->pipes[i].cmd_name, g_data->pipes[i].argv, g_data->env);
			ft_printf(2, "Minishell: %s: %s\n", g_data->pipes[i].cmd_name, strerror(errno));
			exit(127);
		}
		i++;
	}

	i = 0;
	while (i < g_data->pipe_count)
	{
		waitpid(g_data->pipes[i].pid, &status, 0);
		i++;
	}
	close_all_fd(fd, g_data->pipe_count);
    // printf("status = %d\n", status);
	// if (WIFEXITED(status))  // TODO exit_status
  	//printf("%d\n", WEXITSTATUS(status)); //need to store the cheild exit status for
	return (0);
}
