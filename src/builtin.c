/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:21:42 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/12 21:18:29 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int is_builtin(char *argv_0)
{
    if (ft_strncmp(argv_0, "echo", 4) == 0 
        || ft_strncmp(argv_0, "pwd", 3) == 0
        || ft_strncmp(argv_0, "cd", 2) == 0
        || ft_strncmp(argv_0, "env", 3) == 0
        || ft_strncmp(argv_0, "export", 6) == 0
        || ft_strncmp(argv_0, "unset", 5) == 0
        || ft_strncmp(argv_0, "exit", 4) == 0)
        return (1);
    return (0);
}

int builtin(t_general *g_data, char **argv, int i)
{
    if (ft_strncmp(*argv, "echo", 4) == 0)
        return (ft_echo(argv + 1, g_data, i));
    else if (ft_strncmp(*argv, "pwd", 3) == 0)
        ft_pwd(g_data->pipes[i].fd_out);
    else if (ft_strncmp(*argv, "cd", 2) == 0)
        return (ft_cd(argv + 1));
    else if (ft_strncmp(*argv, "env", 3) == 0)
        return (ft_env(g_data));
    else if (ft_strncmp(*argv, "export", 6) == 0)
        return (ft_export(g_data, (argv)));
    else if (ft_strncmp(*argv, "unset", 5) == 0)
        return (ft_unset(g_data, (argv)));
    else if (ft_strncmp(*argv, "exit", 4) == 0)
        return (ft_exit(argv));
    return (0);
}

void ft_malloc_for_env(t_general *g_data, char **env)
{
    int i;

    i = 0;

    while(env[i])
    {
        i++;
    }
    g_data->env = (char **)malloc((i + 1)*sizeof(char *));
    i = 0;
    while(env[i])
    {
        g_data->env[i] = ft_strdup(env[i]);
        i++;
    } 
    g_data->env[i] = NULL;
}

// int	main(int argc, char **argv, char **env)
// {
// 	int			i;
// 	char		*cmd;
// 	t_general	g_data;
// 	char		*str;

// 	ft_malloc_for_env(&g_data, env);
// 	g_data.head_env = NULL;
//     g_data.exp = NULL;
// 	set_env_t_list(&g_data, env);
//     get_export(&g_data);
// 	while (1)
// 	{
// 		g_data.line = readline("Minishell$ ");
// 		if (*(g_data.line) == '\0')
// 			continue ;
// 		add_history(g_data.line);
//         builtin(&g_data, ft_split(g_data.line, ' '), 1);
// 	}
// 	return (0);
// }