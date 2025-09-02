#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	if (argc == 4)
	{
		int n1 = atoi(argv[1]);
		int n2 = atoi(argv[3]);
		int result = 0;

		if (argv[2][0] == '*')
		{
			result = n1 * n2;
		}
		else if (argv[2][0] == '/')
		{
			result = n1 / n2;
		}
		else if (argv[2][0] == '%')
		{
			result = n1 % n2;
		}
		else if (argv[2][0] == '+')
		{
			result = n1 + n2;
		}
		else if (argv[2][0] == '-')
		{
			result = n1 - n2;
		}
		printf("%d \n", result);
	}
	else
	{
		write(1, "\n", 1);
	}
}