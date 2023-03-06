/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:15:58 by lohanyan          #+#    #+#             */
/*   Updated: 2023/03/06 21:41:18 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include "mini.h"
// int main(int argc, char **argv, char **env)
// {
// 	char **tox;
// 	char *cmd;
// 	t_general data;
// 	int	i;


// 	i = 0;
// 	(void)argc;
// 	(void)argv;
// 	while(env[i])
// 		i++;
// 	data.env = malloc(sizeof(char *)*(i + 1));
// 	i = 0;
// while(env && env[i])
// {
// 	data.env[i] = ft_strdup(env[i]);
// 	i++;
// }
// data.env[i] = NULL;
// 	get_export(&data);
// 	//ft_sort_export(&data, &i);
	
// 	while(1)
// 	{
// 		cmd = readline("Minishell$ ");
// 		tox = ft_split(cmd, ' ');
// 		if(ft_strncmp(cmd, "echo", 4) == 0)
// 		{
// 			ft_echo(&cmd[5]);
// 		}
// 		else if(ft_strncmp(cmd, "pwd", 3) == 0)
// 		{
// 			ft_pwd(&cmd[3]);
// 		}
// 		else if(ft_strncmp(cmd, "cd", 2) == 0)
// 		{
// 			ft_cd(tox[1]);
// 		}
// 		else if(ft_strncmp(cmd, "env", 3) == 0)
// 		{
// 			ft_env(&data);
// 		}
// 		else if(ft_strncmp(cmd, "export", 6) == 0)
// 		{
// 			ft_export(&data, cmd);
// 		}
// 		else if(ft_strncmp(cmd, "unset", 5) == 0)
// 		{
// 			ft_unset(&data, &cmd[6]);
// 		}
// 		else if(ft_strncmp(cmd, "exit", 4) == 0)
// 		{
// 			ft_exit(&cmd[5]);
// 		}
// 		add_history(cmd);
// 		free(cmd);
// 		cmd = 0;
// 	/*	id = fork();
// 		if(id == 0)
// 		{
// 			execve(tox[0], tox, env);
// 			exit(0);
// 		}
// 		waiit(NULL);*/
// 	}
// }
