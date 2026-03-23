/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:59:34 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/16 16:53:09 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "arena.h"
# include "libft.h"
# include "libft_arena.h"
# include <dirent.h>
# include <fcntl.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

# define GREEN "\001\033[0;32m\002"
# define BLUE "\001\033[0;34m\002"
# define RESET "\001\033[0m\002"
# define YELLOW "\001\033[0;33m\002"

# define TOKEN_PIPE "|"
# define TOKEN_OR "||"
# define TOKEN_AND "&&"
# define TOKEN_HEREDOC "<<"
# define TOKEN_APPEND ">>"
# define TOKEN_REDIR_IN "<"
# define TOKEN_REDIR_OUT ">"
# define TOKEN_OPEN_PAREN "("
# define TOKEN_CLOSE_PAREN ")"

//# define TOKEN_SEMICOLON ";"

# define EXIT_SUCCESS 0
# define EXIT_GENERAL_ERROR 1
# define EXIT_MISUSE 2
# define EXIT_CANNOT_EXEC 126
# define EXIT_NOT_FOUND 127
# define EXIT_INVALID_ARG 128
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131
# define EXIT_SIGKILL 137
# define EXIT_SIGTERM 143

extern int			g_signal;

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
	int				leftover[2];
	int				heredoc;
	int				heredoc_quoted;
	int				infile;
	int				outfile;
	int				*exitcode;
	int				redir_error;
	struct s_cmd	*subshell;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}					t_cmd;

/*********************************************************************/
/*main*/
/*********************************************************************/

int					is_single_builtin(t_cmd *cmd);
void				exec_single_builtin(t_cmd *cmd, int *exit_status);
void				run_interactive_loop(char ***mini_env, int *exit_status,
						int lft[2]);
int					run_script_mode(char *line, char ***mini_env,
						int *exit_status);

/*********************************************************************/
/* reader/read.c
	Read from stdin and add the comand to the history */
/*********************************************************************/
char				*reader(t_arena *arena, char **envp, int leftover[2]);
void				update_quote_flags(const char *line, int *double_q,
						int *single_q);
void				append_line(t_arena *arena, char **full_line, char *tmp);

/*******************************************************/
/* tokenizer/tokenizer.c
	tokenizes the line of stdin */
/*******************************************************/

char				**tokenizer(t_arena *arena, const char *str);
int					get_keylen(const char *str);
char				*get_env_value(t_cmd *cmd, char *key);
int					is_token(const char *token);
int					token_len(const char *str);
char				*get_token_string(const char *str);

/*********************************************************/
/* parser/parse.c
		parse the output of the tokenizer */
/*********************************************************/
int					is_valid_syntax(char **cmd, int *exitcode);
t_cmd				*parser(t_arena *arena, char **tokens, char ***env_ptr,
						int *exitcode);
int					is_control_operator(const char *token);
int					is_meta_char(const char c);
int					is_quotation(char c);
int					check_quotes(const char *str);
int					check_parentheses(char **cmd, int *exitcode);
int					check_left_arg(char **cmd, int index, int *exitcode);
int					check_right_arg(char **cmd, int index, int *exitcode);
int					check_redirect(char **cmd, int *exitcode);
int					syntax_error(const char *token, int *exitcode);
//--------------------------------------------------
int					parse_heredoc(t_cmd *cmd, int leftover[2]);
void				write_heredoc_interactive(t_cmd *cmd, char *eof,
						int pipefd[2], int leftover[2]);
void				write_heredoc_pasted(char **tokens, char *eof,
						int pipefd[2], int *j);
int					has_pasted_content(char **tokens, int j, char *eof);
int					handle_heredoc_pasted(t_cmd *cmd, char *eof, int pipefd[2],
						int j);
int					wait_heredoc(t_cmd *cmd, pid_t pid, int pipefd[2]);
int					is_delimiter(char *line, char *eof);
void				remove_heredoc_tokens(char **cmd, int i);
int					is_redirect(const char *cmd);
void				remove_quotes(char *str);
t_cmd				*init_cmd(t_arena *arena, char ***env_ptr, int *exitcode);

//----------------------------------------------------
t_operator			get_operator(char *str);
char				**get_next_operator(char **cmd);
char				**after_closing_parenth(char **cmd);
char				**get_next_cmd(t_cmd *group, char **cmd);
char				**copy_cmd_with_redirections(t_arena *arena, char **tokens,
						t_cmd *cmd);
char				**copy_tab_until_operator(t_arena *arena, char **tab);
//---------------------------------------------------
int					is_redirection(char *token);
void				handle_redirection(t_cmd *cmd, char **tokens, int *i);

/*********************************************************/
/* execution */
/*********************************************************/

int					execute_cmd_list(t_cmd *cmd);
char				*resolve_path(t_arena *arena, char *cmd, char **envp);
int					should_skip(t_operator incoming_op, int exitcode);
t_cmd				*next_group(t_cmd *cmd, t_operator *out_op);
void				child_exec_cmd(t_cmd *cmd);
/*builtins*/
int					exec_builtin(t_cmd *cmd);
void				exec_cd(t_cmd *cmd);
void				exec_exit(t_cmd *cmd);
void				exec_pwd(t_cmd *cmd);
void				exec_echo(t_cmd *cmd);
int					handle_invalid_identifier(t_cmd *cmd, char *identifier);
char				**copy_env(char **envp);
char				*get_env_var(t_cmd *cmd, char *key);
void				free_env(char **env);
void				exec_export(t_cmd *cmd);
void				exec_unset(t_cmd *cmd);
/*señales*/
void				set_signals_interactive(void);
void				set_signals_child(void);
/*redirections*/
void				apply_redirections(t_cmd *cmd);
void				open_redirections(t_cmd *cmd);

/*wrapper*/
int					execute_chain(t_cmd *cmd);

/*********************************************************/
/*expander*/
/*********************************************************/
void				expander(t_cmd *cmd);
char				*expand_heredoc_line(t_cmd *cmd, char *line);
int					get_keylen(const char *str);
char				*get_env_value(t_cmd *cmd, char *key);
char				*expand_var(t_cmd *cmd, char *var, int dolar_pos);
void				get_next_dolar(t_cmd *cmd, int word_index);
void				remove_char(char *str);
void				remove_word(char **cmd);
void				remove_redirect(char **cmd);
int					has_wildcard(const char *arg);
int					wildcard_match(const char *pattern, const char *name);
int					count_words(char **cmd);
void				insert_word(t_cmd *cmd, char *new_word, int index);
void				expand_wildcards(t_cmd *cmd, int word_index);
void				expand_heredoc(t_cmd *cmd);
void				heredocs_expander_main(t_cmd *cmd);

#endif
