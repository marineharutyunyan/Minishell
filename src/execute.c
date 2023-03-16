/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:08 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/16 23:23:26 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "mini.h"

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

int	is_dir(char *cmd)
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
			|| !ft_strchr(pipe->cmd_name, '/')))
	{
		if (get_value_by_key("PATH", g_data->head_env))
			set_execv_path(g_data, pipe);
	}
	return (1);
}

int	execute(t_general *g_data)
{
	int	status;
	int	exit_status;
	int	i;
	int	**fd;

	i = 0;
	fd = create_pipes(g_data->pipe_count);
	if (fd == NULL)
		return (127);
	if (g_data->pipe_count == 1 && g_data->pipes[0].argv)
		if (is_builtin(g_data->pipes[0].argv[0]) && free_double_array((void ***)&fd))
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
	free_double_array((void ***)&fd);
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
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf(2, "Quit: 3");
		return ((!write(1, "\n", 1)) | WTERMSIG(status) + 128);
	}
	return (exit_status);
}
