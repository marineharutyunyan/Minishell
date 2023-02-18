#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <dirent.h>
#include "libft.h"
#include "ft_printf.h"

# define PROMPT_PIPE_EXAMPLE "|\"ls |-la|\" | cat sgdsgsdg sdgsdgsdg |$dsgsd\"gs|dg\" '|f |f  |g| |'  | ls"
# define PROMPT_TOKENS_EXAMPLE "<a<b<c>d>\" t    \">>y<<u>i<i \"cat \"ls <\"t \"> u file"
# define UNEXPECTED "|&;()"
# define SPACE "\n\t "
# define REDIRECTIONS "<>"
# define METACHARACTERS "|&;()<>\n\t "

# define HEREDOC 1  // << // opening file and puting the 

typedef struct s_red t_red;
typedef struct s_pipe t_pipe;
typedef struct s_parsing t_parsing;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env 	*next;
}					t_env;

typedef struct s_parsing
{
	char	**pipes; // containing array of lines in between pipes |  | the quote pipes doesn't count as pipe
	int 	pipe_count;
}					t_parsing;

typedef struct s_general
{
	t_env   	*head_env;
	//char		**env; //TODO Why do I need this ? 
	char 		*line;
	t_pipe		*pipes;
	t_parsing	parse_data;
}					t_general;

typedef struct s_pipe //malloc with noumer of pipes +1 , and give initial valuees 
{
	int		fd_in;  // 0          // read only goes here  
	int		fd_out; // 1              // rest reutts of open exept heredoc gors here 
	int 	words_count; // count of words contained in argv below
	char	**argv; // for execve //NULL
	t_red	*head_red; //NULL
}					t_pipe;

typedef struct s_red 
{
	int		flag; // TODO should this be just int ? if << flags = Heredoc       for others(>> > < ) man open defined flags numbers 
	char	*pathname; // the string that doesn't contain metacharacters starting from <<
	struct	s_red *next; //NULL for the firs time 
}					t_red;

// parsing
char	*ft_strdup_modif(const char *s1, int startIndex, int len);
char	*char_to_string(char s1);
char	*ft_trim(char *s1);
int		check_first_symbol(char *str);
int 	check_last_symbol(char *str);
int 	check_opening_closing_quote_pair(char* str);
int 	check_redir_sytax(char *str);
int 	has_errors(char *str);
void 	split_by_pipes(t_general *g_data, t_parsing *data);
void	init_structs(t_general *g_data);
void	paresing(t_general *g_data);
int		pass_quotes(char *str, int i);
void	lst_redir_add_back(t_red **lst, t_red *new);
t_red	*lst_redir_new(void *content, int flag_num);
int		pass_spces(char *line, int i);
int		pass_quotes(char *str, int i);
int		pass_word(char *line, int i);
char	*get_word(char *line, int *i);
int		pass_redir(char *line, int i);
char	*get_text(char *str, int *i);
char	*get_inbetween_double_quotes_text(char *str, int *i);
char	*get_inbetween_single_quotes_text(char *str, int *i);
char	*process_line (char *line, t_general *g_data);
char	*replace_env_var(char *line, t_general *g_data);


//envparsing

t_env	*lst_env_new(void *value, void *key);
void	lst_env_add_back(t_env **lst, t_env *new);
void    set_env(t_general *g_data, char **env);


//utils
int	free_array(void	**ptr);

//temp_utils
void	ft_redir_iter(t_red *lst);
void	ft_env_iter(t_env *lst);

