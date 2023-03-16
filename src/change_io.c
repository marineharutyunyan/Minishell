/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:21:43 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/16 23:21:58 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "mini.h"

void	change_io(int **fd, int i, int pipe_count, t_pipe pipe)
{
	if (pipe_count > 1)
	{
		if (i == 0)
		{
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			else
				dup2(fd[i][1], 1);
		}
		else if (i == pipe_count - 1)
		{
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			else
				dup2(fd[i - 1][0], 0);
		}
		else
		{
			if (pipe.fd_in != 0)
				dup2(pipe.fd_in, 0);
			else
				dup2(fd[i - 1][0], 0);
			if (pipe.fd_out != 1)
				dup2(pipe.fd_out, 1);
			else
				dup2(fd[i][1], 1);
		}
	}
	else
	{
		dup2(pipe.fd_in, 0);
		dup2(pipe.fd_out, 1);
	}
}
