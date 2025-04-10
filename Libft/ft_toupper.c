#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 0 && c <= 255)
	{
		if ((c >= 'a' && c <= 'z'))
		{
			c = c - ('a' - 'A');
		}
	}
	return (c);
}