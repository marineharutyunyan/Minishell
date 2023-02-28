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

void	change_ia(int **fd, int i, int pipe_count)
{
	if (i == 0)
		dup2(fd[i][1], 1);
	else if (i == pipe_count - 1)
		dup2(fd[i - 1][0], 0);
	else
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
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

int set_execv_path(t_general *g_data, t_pipe *pipe)
{
	char **paths;
	int i;
	char *fullpath;
	i = 0;
	if (access(pipe->cmd_name, F_OK) != -1)
	{
		//TODO should I  also check if the command is execuatable with X_OK
		printf("path exist\n");
		return (0);
	}
	else 
	{
		paths = ft_split(get_value_by_key(ft_strdup("PATH"), g_data->head_env), ':');
	}
	while(paths[i])
	{
		fullpath = ft_strjoin(paths[i], ft_strdup("/"));
		fullpath = ft_strjoin(fullpath, pipe->cmd_name);
		if (access(fullpath, F_OK) != -1)
		{
			pipe->cmd_name = fullpath;
			return (0);
		}
		i++;
	}
	return (-1);
}

//  cat main.c | cat | cat
int	execute(t_general *g_data)
{
	pid_t	id;
	int		status;
	int		i;
	int		**fd; //TODO doesn't work with *fd[2]

	i = 0;
	fd = create_pipes(g_data->pipe_count);
	while (i < g_data->pipe_count)
	{
		id = fork(); // TODO check ret_value;
		if (id == 0)
		{
			change_ia(fd, i, g_data->pipe_count);
			close_all_fd(fd, g_data->pipe_count);
			set_execv_path(g_data, &g_data->pipes[i]);
			execve(g_data->pipes[i].cmd_name, g_data->pipes[i].argv, g_data->env);
			exit(5);
		}
		i++;
	}		
	close_all_fd(fd, g_data->pipe_count);
	waitpid(id, &status, 0);
//  printf("status = %d\n", status);
//  printf("id of parent %d\n", id);
//	if (WIFEXITED(status))  // TODO exit_status
//  	printf("%d\n", WEXITSTATUS(status)); //need to store the cheild exit status for
	return (0);
}
