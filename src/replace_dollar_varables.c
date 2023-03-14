/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_varables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:40:41 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/14 09:53:37 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int replace_dollar_varables(t_general *g_data, int i)
{
	int 	j;
	char	*tmp_pathname;
	t_red 	*temp;

	j = 0;
	if (g_data->pipes[i].argv)
	{
		while (g_data->pipes[i].argv[j])
		{
			g_data->pipes[i].argv[j] = process_dollar_sign_and_quotes(g_data->pipes[i].argv[j], g_data);
			j++;
		}
	}
	temp = g_data->pipes[i].head_red;
	while (temp)
	{
		if (temp->flag != HEREDOC)
			temp->pathname = process_dollar_sign_and_quotes(temp->pathname, g_data);
		else
			temp->pathname = remove_qutoes(temp->pathname, &temp->expand_mode_heredoc);
		temp = temp->next;
	}
	return(0);
}