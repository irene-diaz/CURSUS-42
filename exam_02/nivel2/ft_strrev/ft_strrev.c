int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
char	*ft_strrev(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		// utilizamos tmp para guardar el carater antes de intercambiar
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}
#include <unistd.h>

int	main(void)
{
	char str[] = "hola mundo";
	ft_strrev(str);
	int len = ft_strlen(str);
	write(1, str, len);
}