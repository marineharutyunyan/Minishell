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

int main(int argc, char **argv, char **env)
{
	int		i; 
	char	*cmd;
	t_parsing pars_data;
	cmd = readline("Minishell$ ");
	if (!has_errors(cmd))
		ft_printf(1, "Line is valid\n");
	split_by_pipes(&pars_data, cmd);

	// print ---------------------
	while (i < pars_data.pipe_count + 1)
	{
		printf("[i] =%s\n", pars_data.pipes[i]);
		i++;
	}
	return (0);
}
