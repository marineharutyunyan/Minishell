/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:21:42 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/06 21:57:12 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int is_builtin(char **argv)
{
    if(ft_strncmp(*argv, "echo", 4) == 0 
        || ft_strncmp(*argv, "pwd", 3) == 0
        || ft_strncmp(*argv, "cd", 2) == 0
        || ft_strncmp(*argv, "env", 3) == 0
        || ft_strncmp(*argv, "export", 6) == 0
        || ft_strncmp(*argv, "unset", 5) == 0
        || ft_strncmp(*argv, "exit", 4) == 0)
        return (1);
    return (0);
}

int builtin(t_general *g_data, char **argv)
{
    if(ft_strncmp(*argv, "echo", 4) == 0)
        return(ft_echo(*argv)); // TODO return from funcions
    else if(ft_strncmp(*argv, "pwd", 3) == 0)
        ft_pwd(*argv);
    else if(ft_strncmp(*argv, "cd", 2) == 0)
        ft_cd(*argv);
    else if(ft_strncmp(*argv, "env", 3) == 0)
        ft_env(g_data);
    else if(ft_strncmp(*argv, "export", 6) == 0)
        ft_export(g_data, *argv);
    else if(ft_strncmp(*argv, "unset", 5) == 0)
        ft_unset(g_data, *argv);
    else if(ft_strncmp(*argv, "exit", 4) == 0)
        ft_exit(*argv);
    return (0);
}
