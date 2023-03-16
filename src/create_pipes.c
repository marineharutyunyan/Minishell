/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:22:56 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/17 00:16:53 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "mini.h"

int	**create_pipes(int pipe_count)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (pipe_count));
	if (fd == NULL)
		exit (1);
	while (i < pipe_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
			exit (1);
		if (pipe(fd[i]) == -1)
		{
			perror("Minishell: pipe:");
			while (i != -1)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				free(fd[i]);
				i--;
			}
			free(fd);
			return (NULL);
		}
		i++;
	}
	fd[i] = NULL;
	return (fd);
}