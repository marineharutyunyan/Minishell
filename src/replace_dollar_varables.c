/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_varables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:40:41 by maharuty          #+#    #+#             */
/*   Updated: 2023/03/16 22:49:48 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	arr_double_len(char	**arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char ** slice_arr(char **argv, char **arr, int index)
{
	char	**result;
	int		i;
	int		j;
	int		index_for_free;

	index_for_free = index;
	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (arr_double_len(argv) + arr_double_len(arr) + 1));
	while (i < index)
	{
		result[i] =  argv[i];
		i++;
	}
	while (arr[j])
		result[index++] =  arr[j++];
	i++;
	while (argv[i])
		result[index++] =  argv[i++];
	result[index] = NULL;
	free(argv[index_for_free]);
	free(arr);
	free(argv);
	return (result);
}

int replace_dollar_varables(t_general *g_data, int i)
{
	int 	j;
	t_red 	*temp;

	j = 0;
	if (g_data->pipes[i].argv)
	{
		while (g_data->pipes[i].argv[j])
		{
			g_data->pipes[i].argv[j] = process_dollar_sign_and_quotes(g_data->pipes[i].argv[j], g_data);
			/*if (g_signal_notifire == SPLITE)
			{
				g_data->pipes[i].argv = slice_arr(g_data->pipes[i].argv, ft_split(g_data->pipes[i].argv[j], ' '), j);
				g_signal_notifire = NO_SPLITE;
			}*/
			if (g_data->pipes[i].argv[j] == NULL)
				g_data->pipes[i].argv[j] = ft_strdup("");
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