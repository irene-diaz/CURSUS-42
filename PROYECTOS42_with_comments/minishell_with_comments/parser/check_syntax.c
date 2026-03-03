#include "../includes/minishell.h"

//parentesis balanceadois--> check parentesis
//comillas cerradas --> is matching quoites
//operadores válidos -> check left y right
//despues de un operaador o al inicio
//redirecciones válidas
//quizás meter alguna cosilla en útils

int	syntax_error(const char *token, int *exitcode)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, "syntax error near unexpected token '", 36);
	if (token && token[0] == '\n')
		write(STDERR_FILENO, "newline", 7);
	else if (token)
		write(STDERR_FILENO, token, ft_strlen(token));
	else
		write(STDERR_FILENO, "(NULL)", 6);
	write(STDERR_FILENO, "'\n", 2);
	*exitcode = 2;
	return (0);
}

int	is_control_operator(const char *token)
{
	if (token[0] == '|' && token[1] == '|')
		return (2);
	else if (token[0] == '|')
		return (1);
	else if (token[0] == '&' && token[1] == '&')
		return (2);
	else if (token[0] == '(')
		return (1);
	else if (token[0] == ')')
		return (1);
	return (0);
}

int	is_meta_char(const char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '&')
		return (1);
	else if (c == '(')
		return (1);
	else if (c == ')')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	return (0);
}

int	is_redirect(const char *cmd)
{
	if (!ft_strncmp(cmd, "<<", 3))
		return (1);
	else if (!ft_strncmp(cmd, ">>", 3))
		return (1);
	else if (!ft_strncmp(cmd, "<", 2))
		return (1);
	else if (!ft_strncmp(cmd, ">", 2))
		return (1);
	return (0);
}

int	check_left_arg(char **cmd, int index, int *exitcode)
{
	int	j;

	j = index - 1;
	while (j >= 0 && (cmd[j][0] == ')' || cmd[j][0] == '('))
		j--;
	if (j < 0)
		return (syntax_error(cmd[index], exitcode), 0);
	if (is_control_operator(cmd[j]))
		return (syntax_error(cmd[j], exitcode), 0);
	return (1);
}

int	check_right_arg(char **cmd, int index, int *exitcode)
{
	int	j;

	j = index + 1;
	while (cmd[j] && (cmd[j][0] == '(' || cmd[j][0] == ')'))
		j++;
	if (cmd[j] == NULL)
		return (syntax_error(cmd[index], exitcode), 0);
	if (is_control_operator(cmd[j]))
		return (syntax_error(cmd[j], exitcode), 0);
	return (1);
}

int	check_redirect(char **cmd, int *exitcode)
{
	if (!is_redirect(*cmd))
		return (1);
	if (*(cmd + 1) == NULL || is_meta_char(cmd[1][0]))
	{
		syntax_error(cmd[1], exitcode);
		return (0);
	}
	return (1);
}

int	is_quotation(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

static int	check_quotes(const char *str)
{
	char	quote;

	while (*str)
	{
		while (*str && !is_quotation(*str))
			str++;
		if (*str == 0)
			return (1);
		quote = *str;
		str++;
		while (*str && *str != quote)
			str++;
		if (*str == 0)
			return (0);
		str++;
	}
	return (1);
}

static int	check_parentheses(char **cmd, int *exitcode)
{
	int	count;

	count = 1;
	while (*cmd)
	{
		if (**cmd == '(' && cmd[1] && cmd[1][0] == ')')
		{
			syntax_error("empty parentheses", exitcode);
			return (0);
		}
		if (**cmd == '(')
			count++;
		if (**cmd == ')')
			count--;
		cmd++;
	}
	if (count != 1)
	{
		syntax_error("missing parenthesis", exitcode);
		return (0);
	}
	return (1);
}

int	is_valid_syntax(char **cmd, int *exitcode)
{
	int	i;

	i = 0;
	if (!check_parentheses(cmd, exitcode))
		return (0);
	while (cmd[i])
	{
		if (!check_quotes(cmd[i]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (is_control_operator(cmd[i]) && cmd[i][0] != '(' && cmd[i][0] != ')')
		{
			if (!check_left_arg(cmd, i, exitcode))
				return (0);
			if (!check_right_arg(cmd, i, exitcode))
				return (0);
		}
		if (cmd[i][0] == '(' && i > 0 && !is_control_operator(cmd[i - 1]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (cmd[i][0] == ')' && cmd[i + 1] && !is_control_operator(cmd[i + 1]))
			return (syntax_error(cmd[i], exitcode), 0);
		if (!check_redirect(&cmd[i], exitcode))
			return (0);
		i++;
	}
	return (1);
}
