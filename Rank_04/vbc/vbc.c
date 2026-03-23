#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

char *s;

void unexpected(char c)
{
	if (c)
		printf("Unexpected token'%c'\n", c);
	else
		printf("Unexpected end of input");
}

int ft_sum();

int ft_factor()
{
	int n = 0;

	if (isdigit(*s))
		return (*s++ - '0');
	while (*s == '(')
	{
		s++;
		n = ft_sum();
		s++;
	}
	return (n);
}

int ft_product()
{
	int p = ft_factor();
	while (*s == '*')
	{
		s++;
		p *= ft_factor();
	}
	return (p);
}
int ft_sum()
{
	int sum = ft_product();
	while (*s == '+')
	{
		s++;
		sum += ft_product();
	}
	return (sum);
}

int check_list(char *str)
{
	int cp = 0;
	int i = 0;
	int last = 0;

	while (str[i])
	{
		if (str[i] == '(')
			cp++;
		if (str[i] == ')')
			cp--;
		if (isdigit(str[i]) && isdigit(str[i + 1]))
			return (unexpected(str[i + 1]), 1);
		last = str[i++];
	}
	if (cp > 0)
		return (unexpected('('), 1);
	if (cp < 0)
		return (unexpected(')'), 1);
	if (last == '*' || last == '+')
		return (unexpected(0), 1);
	return (0);
}

int main(int argc, char *argv[])
{
	int result;
	if (argc != 2 || check_list(argv[1]))
		return 1;
	s = argv[1];
	result = ft_sum();
	printf("%d\n", result);
	return 0;
}