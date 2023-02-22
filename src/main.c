/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:15:58 by lohanyan          #+#    #+#             */
/*   Updated: 2023/01/25 14:59:11 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include "mini.h"

void	free_parsing(t_parsing *pars_data)
{
	int	i;

	i = 0;
	while (pars_data->pipes[i])
		free_array((void **)&pars_data->pipes[i++]);
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

int	main(int argc, char **argv, char **env)
{
	int			i;
	char		*cmd;
	t_general	g_data;
	char		*str;
	g_data.env = env;
	while (1)
	{
		cmd = readline("Minishell$ ");
		add_history(cmd);
		// if (!has_errors(cmd)) /* TODO enable erro check */
		// ft_printf(1, "Line is valid\n"); //TODO add rediraction check
		g_data.line = cmd;
		g_data.head_env = NULL;
		split_by_pipes(&g_data, &g_data.parse_data);
		init_structs(&g_data);
		paresing(&g_data);
		set_env(&g_data, env);
		//printf("str = %s\n", process_dollar_sign_and_quotes(g_data.line, &g_data));
		handle_rediractions(&g_data);
		execute(&g_data);
		free_parsing(&g_data.parse_data);
		free_general(&g_data);
	}
	return (0);
}
