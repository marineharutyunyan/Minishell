/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:15:02 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/16 20:21:37 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int child_heredoc(t_red *head_red, t_general *g_data)
{
	char	*line;
	char	*full_line;
	full_line = ft_strdup("");
	handle_signals(!INTERACTIVE_MODE);
	while (1)
	{
		set_term_attr(1);
		line = readline("> ");
		set_term_attr(0);
		if (line == NULL)
		{
			if (full_line[0] != '\0')
				full_line = ft_strjoin_free_first_arg(full_line, "\n");
			break ;
		}
		if ((full_line[0] != '\0' && full_line[0] != '\n') || line[0] == '\0')// TODO make readable
			full_line = ft_strjoin_free_first_arg(full_line, "\n");
		if (ft_strcmp(line, head_red->pathname) == 0)
			break ;
		else
			full_line = ft_strjoin_free_first_arg(full_line, line);
	}
	if (head_red->expand_mode_heredoc == EXPAND_VAR)
		full_line = replace_env_var(full_line, g_data);
	if (full_line)
		ft_printf(head_red->heredoc_fd[1], "%s", full_line);
	close(head_red->heredoc_fd[1]);
	exit(0);
}
int	heredoc(t_red *head_red, t_general *g_data)
{
	pid_t	pid;
	int		status;

	
	if (pipe(head_red->heredoc_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_heredoc(head_red, g_data);
	close(head_red->heredoc_fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && write(1, "\n", 1))
		return (WTERMSIG(status));	
	return (WEXITSTATUS(status));
}
