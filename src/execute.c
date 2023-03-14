#include "mini.h"

char	*ft_strjoin_free_first_arg(char *s1, char const *s2) // TODO add flag to free or not to free
{
	int		s1_len;
	int		s2_len;
	char	*newstr;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (!s1)
			return (ft_strdup(s2));
		else/* if (!free_arr((char *)s1))*/
			return (ft_strdup(s1));
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!(newstr))
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + 1);
	ft_strlcat(newstr + (s1_len), s2, s2_len + 1);
	free(s1);
	return (newstr);
}

static int	**create_pipes(int pipe_count)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (pipe_count));
	if (fd == NULL)
		exit (1);
	while (i < pipe_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
			exit (1);
		if (pipe(fd[i]) == -1)
		{
			perror("Minishell: pipe:");
			while (i != -1)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				free(fd[i]);
				i--;
			}
			free(fd);
			return (NULL);
		}
		i++;
	}
	fd[i] = NULL;
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

int is_dir(char *cmd)
{
	if (opendir(cmd))
	{
		ft_printf(2, "minishell: %s: is a directory\n", cmd);
		exit (126);
	}
	return (0);
}

int	is_for_execve(char *cmd, t_general *g_data, t_pipe *pipe)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ft_printf(2, "minishell: .: filename argument required\n\
.: usage: . filename [arguments]\n");
		exit (2);
	}
	if (!is_dir(pipe->cmd_name)
		&& (!is_path_abs_or_relative(pipe->cmd_name)
			|| !ft_strchr(pipe->cmd_name,'/')))
	{
		if (get_value_by_key("PATH", g_data->head_env))
			set_execv_path(g_data, pipe);
	}
	return(1);
}

//  cat main.c | cat | cat
int	execute(t_general *g_data)
{
	int		status;
	int 	exit_status;
	int		i;
	int		**fd;

	i = 0;
	fd = create_pipes(g_data->pipe_count); // TODO protect multiple pipes
	if (fd == NULL)
		return (127);
	if (g_data->pipe_count == 1 && g_data->pipes[0].argv)
		if (is_builtin(g_data->pipes[0].argv[0]))
			return (builtin(g_data, g_data->pipes[0].argv, 0));
	while (i < g_data->pipe_count)
	{
		if (g_data->pipes[i].argv)
		{
			g_data->pipes[i].pid = fork();
			if (g_data->pipes[i].pid == -1)
				exit (1); // TODO review
			if (g_data->pipes[i].pid == 0)
			{
				handle_signals(!INTERACTIVE_MODE);
				change_io(fd, i, g_data->pipe_count, g_data->pipes[i]);
				close_all_fd(fd, g_data->pipe_count);
				if (is_builtin(g_data->pipes[i].argv[0]))
					exit (builtin(g_data, g_data->pipes[i].argv, i));
				if (g_data->pipes[i].words_count > 0)
					g_data->pipes[i].cmd_name = ft_strdup(g_data->pipes[i].argv[0]);
				if (is_for_execve(g_data->pipes[i].cmd_name, g_data, &g_data->pipes[i]))	
					execve(g_data->pipes[i].cmd_name, g_data->pipes[i].argv, g_data->env);
				ft_printf(2, "Minishell!!: %s: %s\n", g_data->pipes[i].cmd_name, strerror(errno));
				exit(127);
			}
		}
		i++;
	}
	close_all_fd(fd, g_data->pipe_count);
	free_double_array((void***)&fd);
	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < g_data->pipe_count)
	{
		waitpid(g_data->pipes[i].pid, &status, 0);
		if (i == g_data->pipe_count - 1)
			exit_status = WEXITSTATUS(status);
		i++;
	}
	if (WIFSIGNALED(status)) // TODO review
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf(2, "Quit: 3");
		return ((!write(1, "\n", 1)) | WTERMSIG(status) + 128);
	}
	return (exit_status);
}