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

int g_signal_notifire;

void	free_parsing(t_parsing *pars_data)
{
	int	i;

	i = 0;
	while (pars_data->pipes[i])
	{
		free_array((void **)&pars_data->pipes[i++]);
	}
	free(pars_data->pipes);
}

void	free_general(t_general *g_data)
{
	free_array((void **)&g_data->line);
	//TODO free pipes
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

/*TODO ERROR cases
Minishell$ sdiufsuidd
Minishell: sdiufsuidd: No such file or directory
should be 
bash: sdiufsuidd: command not found
$PWD
/Users/maharuty/Downloads/Minishell: Permission denied
should be 
bash: /Users/maharuty/Downloads/Minishell: is a directory
*/

int	exit_status_setter(t_env **head_env, int status)
{
	char *str_status;

	str_status = ft_itoa(status);
	lst_env_add(head_env, lst_env_new("?", str_status));
	free_array((void **)&str_status);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_general	g_data;
	char		*str;
	int a;

	set_env(&g_data, env);
	g_data.head_env = NULL;
	set_env_t_list(&g_data, env);
	get_export(&g_data);
	while (1)
	{
		g_signal_notifire = 0;
		handle_signals(INTERACTIVE_MODE);
		set_term_attr(1);
		g_data.line = readline("Minishell$ ");
		set_term_attr(0);
		if (g_signal_notifire == 1 && exit_status_setter(&g_data.head_env, 1))
			continue ;
		if (g_data.line == NULL)
			exit(0);
		if (*(g_data.line) == '\0')
			continue ;
		add_history(g_data.line);
		if (has_errors(g_data.line) && exit_status_setter(&g_data.head_env, 258)) 
			continue ;
		split_by_pipes(&g_data, &g_data.parse_data);
		init_structs(&g_data);
		if (parsing(&g_data) != 0 && exit_status_setter(&g_data.head_env, 1)) //free
			continue ;
		if (g_data.pipes[0].argv)
			exit_status_setter(&g_data.head_env, execute(&g_data));
		free_parsing(&g_data.parse_data);
		free_general(&g_data); // TODO free red struct and close(heredoc_fd[0])
	}
	return (0);
}
