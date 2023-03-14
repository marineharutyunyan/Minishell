/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:53:24 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/13 21:53:24 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_signal_notifire;

void	free_parsing(t_parsing *pars_data)
{
	free_double_array((void ***)&pars_data->pipes);
}

void	free_red(t_red *head_red)
{
	while (head_red)
	{
		if (head_red->flag == HEREDOC)
			close(head_red->heredoc_fd[0]);
		free_array((void **)&head_red->pathname);
		head_red = head_red->next;
	}
}

void	free_pipes(t_pipe *pipes, int pipe_count)
{
	int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (i < pipe_count)
	{
		free_array((void **)&pipes[i].cmd_name);
		free_red(pipes[i].head_red);
		free_double_array((void***)&pipes[i].argv);
		i++;
	}
}

void	free_general(t_general *g_data)
{
	free_parsing(&g_data->parse_data);
	free_array((void **)&g_data->line);
	free_pipes(g_data->pipes, g_data->pipe_count);
	free_array((void **)&g_data->pipes);
	g_data->pipes = NULL;
}


void	init_structs(t_general *g_data)
{
	g_data->pipes = malloc(sizeof(t_pipe)
			* (g_data->pipe_count));
}

void	set_env(t_general *g_data, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	g_data->env = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		g_data->env[i] = ft_strdup(env[i]);
	g_data->env[i] = NULL;
}

void	general_init(t_general *g_data)
{
	g_data->head_env = NULL;
	g_data->pipe_count = 0;
	g_data->env = NULL;
	g_data->exp = NULL;
	g_data->line = NULL;
	g_data->exit_status = 0;
	g_data->pipes = NULL;
	g_data->parse_data.pipes = NULL;
}

int	exit_status_setter(t_env **head_env, int status)
{
	char	*str_status;

	str_status = ft_itoa(status);
	lst_env_add(head_env, lst_env_new("?", str_status));
	free_array((void **)&str_status);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_general	g_data;

	general_init(&g_data);
	set_env(&g_data, env);
	set_env_t_list(&g_data, env);
	get_export(&g_data); //TODO free and leaks unchecked
	while (1)
	{
		g_signal_notifire = 0;
		handle_signals(INTERACTIVE_MODE);
		set_term_attr(1);
		g_data.line = readline("Minishell$ ");
		set_term_attr(0);
		if (g_signal_notifire == 1 && exit_status_setter(&g_data.head_env, 1))
		{
			free_general(&g_data);
			continue ;
		}	
		if (g_data.line == NULL)
			exit(0);
		if (*(g_data.line) == '\0')
		{
			free_general(&g_data);
			continue ;
		}
		add_history(g_data.line);
		if (has_errors(g_data.line) && exit_status_setter(&g_data.head_env, 258)) 
		{
			free_general(&g_data);
			continue ;
		}
		split_by_pipes(&g_data, &g_data.parse_data);
		init_structs(&g_data);
		if (parsing(&g_data) != 0 && exit_status_setter(&g_data.head_env, 1))
		{
			free_general(&g_data);
			continue ;
		}
		if (g_data.pipes[0].argv && g_data.pipes[0].argv[0])
			exit_status_setter(&g_data.head_env, execute(&g_data));
		free_general(&g_data);
	}
	return (0);
}
