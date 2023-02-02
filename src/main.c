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

void	free_pipes(t_parsing *pars_data)
{
	int	i;

	i = 0;
	while (pars_data->pipes[i])
		free_array((void **)&pars_data->pipes[i++]);
	free(pars_data->pipes);
}

void init_structs(t_general *g_data)
{
	t_parsing	*pars_data;
	t_pipe		*pipes;

	g_data->parse_data = pars_data;
	g_data->pipes = malloc(sizeof(t_pipe) * (g_data->parse_data->pipe_count + 1));
}

int main(int argc, char **argv, char **env)
{
	int			i;
	char		*cmd;
	t_parsing	pars_data;
	t_general 	g_data;
	while (1)
	{
		cmd = readline("Minishell$ ");
		add_history(cmd);
		if (!has_errors(cmd))
			ft_printf(1, "Line is valid\n");
		g_data.line = ft_strdup(cmd); //  ----------- is this correct ? 
		split_by_pipes(&g_data, &pars_data);
		init_structs(&g_data);
		paresing(&g_data);



		// print bloks splited by pipe ---------------------
		i = 0;
		while (pars_data.pipes[i])
		{
			printf("[i] =%s\n", pars_data.pipes[i]);
			i++;
		}
		free_pipes(&pars_data);
	}
	return (0);
}

// int main()
// {
// 	char *ptr;
// 	ptr = malloc(10);
// 	ptr[9] = 0;
// 	printf("\n\n\n\n");
// 	printf("%p\n", &ptr);
// 	printf("%p\n", ptr);

// 	// printf("ptr = x%p\n", ptr);
// 	free_array((void **)&ptr);
// 	// printf("ptr = %p\n", ptr);
// }