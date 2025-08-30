unsigned char	swap_bits(unsigned char octet)
{
	return (octet >> 4 | octet << 4);
}

/*#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bits;

	i = 8;
	bits = 0;
	while (i--)
	{
		bits = (octet >> i & 1) + '0';
		write(1, &bits, 1);
	}
}

int	main(void)
{
	print_bits(33);
	unsigned char b = swap_bits(65);
	write(1, "\n", 1);
	print_bits(b);
}*/