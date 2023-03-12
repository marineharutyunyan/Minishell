#include "mini.h"

static int	**create_pipes(int pipe_count)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int) * (pipe_count - 1));
	if (fd == NULL)
		exit (1);
	while (i < pipe_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
			exit (1);
		if (pipe(fd[i]) == -1)
			return (NULL);
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
	if (pipe->words_count > 0)
		pipe->cmd_name = ft_strdup(pipe->argv[0]);
	paths = ft_split(get_value_by_key("PATH", g_data->head_env), ':');
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
	if (access(pipe->cmd_name, F_OK) != -1)
		return (free_double_array((void ***)&paths));
	return (free_double_array((void ***)&paths));
}

//  cat main.c | cat | cat
int	execute(t_general *g_data)
{
	int		status;
	int		i;
	int		**fd;

	i = 0;
	fd = create_pipes(g_data->pipe_count);
	if (fd == NULL)
		return (127);
	if (g_data->pipe_count == 1)
		if (is_builtin(g_data->pipes[0].argv[0]))
			return (builtin(g_data, g_data->pipes[0].argv, 0));
	while (i < g_data->pipe_count)
	{
		g_data->pipes[i].pid = fork(); // TODO check ret_value and handle exit status;
		if (g_data->pipes[i].pid == 0)
		{
			handle_signals(!INTERACTIVE_MODE);
			change_io(fd, i, g_data->pipe_count, g_data->pipes[i]);
			close_all_fd(fd, g_data->pipe_count);
			if (is_builtin(g_data->pipes[i].argv[0]))
				exit (builtin(g_data, g_data->pipes[i].argv, i));
			set_execv_path(g_data, &g_data->pipes[i]);
			execve(g_data->pipes[i].cmd_name, g_data->pipes[i].argv, g_data->env);
			ft_printf(2, "Minishell: %s: %s\n", g_data->pipes[i].cmd_name, strerror(errno));
			exit(127);
		}
		i++;
	}
	close_all_fd(fd, g_data->pipe_count);
	i = 0;
	while (i < g_data->pipe_count)
	{
		waitpid(g_data->pipes[i].pid, &status, 0);
		i++;
	}
	if (WIFSIGNALED(status)/* && write(1, "\n", 1)*/)
		return (WTERMSIG(status) + 127);
	// printf("waitpid2\n");
	return (WIFEXITED(status));
}
