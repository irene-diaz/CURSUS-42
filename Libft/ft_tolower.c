#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 0 && c <= 255)
	{
		if ((c >= 'A' && c <= 'Z'))
		{
			c = c + ('a' - 'A');
		}
	}
	return (c);
}