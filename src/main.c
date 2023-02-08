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
}

void	init_structs(t_general *g_data)
{
	g_data->pipes = malloc(sizeof(t_pipe)
			* (g_data->parse_data.pipe_count + 1));
}

int	main(int argc, char **argv, char **env)
{
	int			i;
	char		*cmd;
	t_general	g_data;

	while (1)
	{
		cmd = readline("Minishell$ ");
		add_history(cmd);
		// if (!has_errors(cmd))
		// ft_printf(1, "Line is valid\n");
		g_data.line = cmd;
		split_by_pipes(&g_data, &g_data.parse_data);
		init_structs(&g_data);
		paresing(&g_data);
		free_parsing(&g_data.parse_data);
		free_general(&g_data);
	}
	return (0);
}
