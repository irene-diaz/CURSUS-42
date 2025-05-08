#include "ft_printf.h"

int	ft_format_d(va_list *args)
{
	int	d;

	d = va_arg(*args, int);
	return (ft_putnbr(d));
}

int	ft_format_c(va_list *args)
{
	int	c;

	c = va_arg(*args, int);
	return (ft_putchar(c));
}

int	ft_format_s(va_list *args)
{
	char	*s;

	s = va_arg(*args, char *);
	return (ft_putstr(s));
}

int	ft_default(char c)
{
	return (ft_putchar(c));
}

/*int	ft_printf(const char *format, ...)
{
	int		i;
	int		j;
	va_list	args;
	int		number;
	va_list	args;
	int		i;
	char	*s;
	va_list	args;
	int		i;
	char	*s;
	char	*s;
	char	*s;
	char	*s;
	char	*s;
	int		i;
	int		c;
	size_t	i;

	// size_t	len;
	va_start(args, format);
	i = 0;
	// j = 0;
	while (i < format)
	{
		number = va_arg(args, int);
		i++;
	}
	// len = ft_strlen(argument_list);
	ft_putstr_fd(args, 1);
	// write(1, &p, 1);
	va_end(args);
	return (0);
}*/
/*printf return the number of characters that you pass*/
/*size_t	ft_strlen(const char *str)
{
	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}*/
/*printf return the number of characters that you pass*/
/*size_t	ft_strlen(const char *str)
{
	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}*/