
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include "libft.h"
#include "ft_printf.h"


# define PROMPT_PIPE_EXAMPLE "|\"ls |-la|\" | cat sgdsgsdg sdgsdgsdg |$dsgsd\"gs|dg\" '|f |f  |g| |'  | ls"
# define PROMPT_TOKENS_EXAMPLE "<a<b<c>d>\" t    \">>y<<u>i<i \"cat \"ls <\"t \"> u file"
# define UNEXPECTED "|&;()"
# define METACHARACTERS "|&;()<>\n\t "
# define HEREDOC 1  // <<

typedef struct s_red t_red;
typedef struct s_pipe t_pipe;
typedef struct s_parsing t_parsing;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env 	*next;
}					t_env;

typedef struct s_general
{
	t_env   	*head_env;
	char 		*line;
	char		**env;
	t_pipe		*pipes;
	t_parsing	*parse_data;
}					t_general;

typedef struct s_parsing
{
	char	**pipes; // containing array of lines in between pipes |  | the quote pipes doesn't count as pipe
	int 	pipe_count;
}					t_parsing;

typedef struct s_pipe //malloc with noumer of pipes +1 , and give initial valuees 
{
	int		fd_in;  // 0
	int		fd_out; // 1
	char	**argv; // for execve //NULL
	t_red	*head_red; //NULL
}					t_pipe;

typedef struct s_red 
{
	int				*flag; // if << flags = Heredoc       for others(>> > < ) man open defined flags numbers 
	char			*pathname; // the string that doesn't contain metacharacters starting from <<
	struct s_red 	*next; //NULL for the firs time 
}					t_red;


// parsing
char	*ft_strdup_modif(const char *s1, int startIndex, int len);
char	*ft_trim(char *s1);
int		check_first_symbol(char *str);
int 	check_last_symbol(char *str);
int 	check_opening_closing_quote_pair(char* str);
int 	has_errors(char *str);
void 	split_by_pipes(t_general *g_data, t_parsing *data);
void	init_structs(t_general *g_data);
void	paresing(t_general *g_data);

//utils
int	free_array(void	**ptr);