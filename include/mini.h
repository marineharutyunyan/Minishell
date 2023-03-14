#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <dirent.h>
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <string.h>
#include <termios.h>
# define PROMPT_PIPE_EXAMPLE "|\"ls |-la|\" | cat sgdsgsdg sdgsdgsdg |$dsgsd\"gs|dg\" '|f |f  |g| |'  | ls"
# define PROMPT_TOKENS_EXAMPLE "<a<b<c>d>\" t    \">>y<<u>i<i \"cat \"ls <\"t \"> u file"
# define UNEXPECTED "|&;"
# define FT_SPACE "\n\t "
# define REDIRECTIONS "<>"
# define METACHARACTERS "|&;()<>\n\t "

# define INTERACTIVE_MODE 1

# define HEREDOC 1  // << // opening file and puting the 


// void rl_replace_line (const char *, int);

extern int g_signal_notifire;

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
	// int 	pipe_count;
}					t_parsing;

typedef struct s_general
{
	int 		pipe_count;
	t_env   	*head_env;
	char		**env; // this is the same env coming from int main 3th arg 
	char 		**exp;
	char 		*line;
	int 		exit_status;
	t_pipe		*pipes;
	t_parsing	parse_data;
}					t_general;

typedef struct s_pipe //malloc with noumer of pipes +1 , and give initial valuees 
{
	char	*cmd_name;  // argv[0] like  ls
	pid_t	pid;
	int		fd_in;  // 0          // read only goes here  
	int		fd_out; // 1          // rest reutts of open exept heredoc gors here 
	int 	words_count; // count of words contained in argv below
	char	**argv; // for execve //NULL
	t_red	*head_red; //NULL
}					t_pipe;

#define EXPAND_VAR 1
#define NO_EXPAND_VAR 2

typedef struct s_red
{
	int		expand_mode_heredoc; // for heredoc only TODO (cmd = cat << END) expand for example END(delimiter)
	//,  otherwise END'' END"" ""END  END"" "END" 'END'  pointer to file_a
 	int		flag; //  if << flags = Heredoc       for others(>> > < ) man open defined flags numbers 
	int		heredoc_fd[2];
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
int		parsing(t_general *g_data);
int		pass_quotes(char *str, int i);
void	lst_redir_add_back(t_red **lst, t_red *new);
t_red	*lst_redir_new(void *content, int flag_num);
int		pass_spces(char *line, int i);
int		pass_quotes(char *str, int i);
int		pass_word(char *line, int i);
char	*get_word(char *line, int *i);
int		pass_redir(char *line, int i);
char	*get_text(char *str, int *i);
char	*remove_qutoes(char *s, int *expand_mode_heredoc);
char	*get_inbetween_double_quotes_text(char *str, int *i);
char	*get_inbetween_single_quotes_text(char *str, int *i);
char	*process_dollar_sign_and_quotes (char *line, t_general *g_data);
int 	replace_dollar_varables(t_general *g_data, int i);
char	*replace_env_var(char *line, t_general *g_data);

//env_parsing
t_env	*lst_env_new(void *value, void *key);
void	lst_env_add(t_env **lst, t_env *new);
void	lst_env_delet_by_key(t_env *lst, char	*key);
void    set_env_t_list(t_general *g_data, char **env);
char	*get_value_by_key(char *key, t_env *lst);

// rediractions
int	 handle_rediractions(t_general *g_data);
int	ft_redir_iter(t_pipe *pipe);
int	heredoc(t_red *head_red, t_general *g_data);
//utils
int	free_array(void	**ptr);
int	free_double_array(void	***ptr);

//temp_utils
void	ft_redir_temp_iter(t_red *lst);
void	ft_env_iter(t_env *lst);

//
int		execute(t_general *g_data);
void 	handle_signals(int mode);
void	set_term_attr(int on_off);





//
int is_builtin(char *argv_0);
int builtin(t_general *g_data, char **argv, int i);
int	ft_echo(char **ptr, t_general *g_data, int i);
int ft_pwd();
int ft_cd(char **ptr);
int ft_env(t_general *data);
int	ft_export(t_general *data, char **ptr);
int	ft_exit(char **ptr);
int	ft_unset(t_general *data, char **ptr);


size_t	ft_strlen(const char *s);
char **ft_split(char const *s, char c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	get_export(t_general *data);
int ft_check_str(char *str, t_general *data);
// char *ft_strchr(char *s, int c);
char *ft_substr(char  const *s, unsigned int start, size_t len);
int ft_strcmp(char *s1, char *s2);
char *ft_epstrdup(char *s1);
void	ft_errors(char *str);
void	get_env(t_general *data, char *str);
int		ft_check_str1(char *str, t_general *data);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strjoin_modifed(char  *s1, char  *s2);
void	ft_unset_for_env(t_general *data, char *ptr);
char	*ft_sign(char *s1, int *i, int *j, int *flag);
unsigned long long int ft_atoi_modifed(const char *str);
void	ft_exp_func(char **ptr, t_general *data, int j, int i);
int	ft_cut_for_exp(t_general *data, char *tmp, char *str, int sign);
void	ft_new_malloc(char *str, char **tmp, int i, int flag);
int	ft_cut_for_env(t_general *data, char *tmp, char *str, int sign);
void	ft_check_env(int k, t_general *data, char **tmp);
void	ft_free_exp(char ***tmp, int j);
void	ft_sort_export(t_general *data, int i);
void	ft_builtins(t_general data, char *cmd, char **tox);
int		ft_errors_for_export(char *str);
int		ft_check_exit(char **ptr, int i, int j);
void	ft_check_sign(char **ptr, int i);
void	ft_check_sign1(char **ptr, int i);
void	ft_print_error_for_exit(void);
void	ft_print_error_for_two_arguments(char **ptr, int i);
void	ft_new_malloc1(char *str, char **tmp, int i, int flag);
char	*ft_strjoin_for_env(char *s1, char *s2);
