#ifndef MINISHELL_H
# define MINISHELL_H

# include "arena.h"
# include "libft.h"
# include "libft_arena.h"
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

# define TOKEN_PIPE "|"
# define TOKEN_OR "||"
# define TOKEN_AND "&&"
# define TOKEN_HEREDOC "<<"
# define TOKEN_APPEND ">>"
# define TOKEN_REDIR_IN "<"
# define TOKEN_REDIR_OUT ">"
# define TOKEN_OPEN_PAREN "("
# define TOKEN_CLOSE_PAREN ")"

typedef enum s_operator
{
	NONE,
	PIPE,
	AND,
	OR,
	OPEN_SUBSHELL,
	CLOSE_SUBSHELL
}					t_operator;

typedef enum s_mode
{
	NON_INTERACTIVE,
	INTERACTIVE,
	HEREDOC
}					t_mode;

typedef struct s_cmd
{
	char			**cmd;
	char			***env_ptr;
	t_operator		operator;
	t_arena			*arena;
	int				pipefd[2];
	pid_t			pid;
	int				original_stdin;
	int				original_stdout;
	int				heredoc;
	int				infile;
	int				outfile;
	int				*exitcode;
	struct s_cmd	*subshell;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}					t_cmd;

/*********************************************************************/
/* reader/read.c
	Read from stdin and add the comand to the history */
/*********************************************************************/

char				*reader(t_arena *arena, char **envp);

/*******************************************************/
/* tokenizer/tokenizer.c
	tokenizes the line of stdin */
/*******************************************************/

char				**tokenizer(t_arena *arena, const char *str);

/*********************************************************/
/* parser/parse.c
		parse the output of the tokenizer */
/*********************************************************/
int					is_valid_syntax(char **cmd, int *exitcode);
t_cmd				*parser(t_arena *arena, char **tokens, char ***env_ptr,
						int *exitcode);

//----------------------------------------------------
t_operator			get_operator(char *str);
char				**get_next_operator(char **cmd);
char				**after_closing_parenth(char **cmd);
char				**get_next_cmd(t_cmd *group, char **cmd);
char				**copy_tab_until_operator(t_arena *arena, char **tab);

/*********************************************************/
/* execution */
/*********************************************************/

int					execute_cmd_list(t_cmd *cmd);
char				*resolve_path(t_arena *arena, char *cmd, char **envp);
/*builtins*/
int					exec_builtin(t_cmd *cmd);
void				exec_cd(t_cmd *cmd);
void				exec_exit(t_cmd *cmd);
void				exec_pwd(t_cmd *cmd);
void				exec_echo(t_cmd *cmd);
void				exec_export(t_cmd *cmd);
void				exec_unset(t_cmd *cmd);
/*señales*/
void				set_signals_interactive(void);
void				set_signals_child(void);
/*redirections*/
void				apply_redirections(t_cmd *cmd);
#endif
