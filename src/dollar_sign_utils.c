#include "mini.h"

char *get_variable_name(char *line, int *i)
{
    int start_num;

    start_num = (*i);
    while (line[(*i)] != '\0' && (ft_isalpha(line[(*i)]) || ft_isdigit(line[(*i)]) || line[(*i)] == '_'))
        (*i)++;
    if ((*i) > start_num)
    {
        return (ft_substr(line, start_num, (*i) - start_num));
    }
    return (NULL);
}

char *find_value_by_key(char *key, t_env *lst)
{
    while (lst)
	{
		if(ft_strcmp(key, lst->key) == 0)
		    return(lst->value);
		lst = lst->next;
	}
    return (NULL);
}
//$HOME help "hello $aa"$MM text$
 
char *replace_env_var(char *line, t_general *g_data)
{
    int i;
    int start_index;
    char *final_line;
    char *temp;

    start_index = 0;
    i = 0;
    final_line = NULL;
    while (line[i] != '\0')
    {
        i = pass_single_quotes(line, i);
        if (line[i] == '$')
        {
            if (i != start_index)
            {
                temp = ft_substr(line, start_index, i - (start_index));
                // printf("Start = %s\n", temp);

                // TODO remove double quotes from temp above  $HOME help "he''llo $aa ' ds''gsdg"$MM text$
                //                                                  help "he''llo 
                //                                                                  ' ds''gsdg"
                //                                                                             text

                final_line = ft_strjoin(final_line, temp);
            }
            i++;
            temp = get_variable_name(line, &i);
            start_index = i;
            // printf("Var =  %s\n", temp);

            if (temp != NULL)
            {
                temp = find_value_by_key(temp, g_data->head_env);
                // printf("find_value_by_key = %s\n", temp);
                final_line = ft_strjoin(final_line, temp);
            }
            else
                final_line = ft_strjoin(final_line, "$"); // TODO handle the free of join
        }
        // printf("Final = %s  \n ", final_line);
        if (line[i] && line[i] != '$')
            i++;
    }
    return (final_line);
}