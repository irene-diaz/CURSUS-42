#include <unistd.h>

void	print_bits(unsigned char octet)
{
	unsigned char	bits;
	int				i;

	bits = 0;
	i = 8;
	while (i--)
	{
		bits = (octet >> i && 1) + '0';
		write(1, &bits, 1);
	}
}
/*int	main(void)
{
	unsigned char octet = 3;
	print_bits(octet);
}*/