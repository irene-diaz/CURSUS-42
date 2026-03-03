#include "../includes/minishell.h"

static char	*build_prompt(t_arena *arena)
{
	char	*prompt;
	char	*user;
	char	path[1024];
	char	hostname[1024];

	user = getenv("USER");
	if (!user)
		user = "user";
	gethostname(hostname, 1024);
	getcwd(path, 1024);
	prompt = ft_strjoin_arena(arena, GREEN, user);
	prompt = ft_strjoin_arena(arena, prompt, "@");
	prompt = ft_strjoin_arena(arena, prompt, hostname);
	prompt = ft_strjoin_arena(arena, prompt, ":" RESET BLUE);
	prompt = ft_strjoin_arena(arena, prompt, path);
	prompt = ft_strjoin_arena(arena, prompt, RESET "$ ");
	return (prompt);
}

char	*reader(t_arena *arena, char **envp)
{
	char	*tmp;
	char	*str;
	char	*prompt;
	int		len;

	envp++;
	prompt = build_prompt(arena);
	tmp = readline(prompt);
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp);
	str = arena_alloc(arena, len + 1);
	ft_strncpy(str, tmp, len);
	str[len] = '\0';
	free(tmp);
	if (str && *str)
		add_history(str);
	return (str);
}
