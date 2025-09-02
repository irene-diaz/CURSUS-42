unsigned char	reverse_bits(unsigned char octet)
{
	int				i;
	unsigned char	result;

	i = 8;
	result = 0;
	while (i--)
	{
		result = result << 1 | octet & 1;
		octet >>= 1;
	}
	return (result);
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
	unsigned char bit = 8;

	print_bits(bit); // imprime 00001000
	write(1, "\n", 1);

	bit = reverse_bits(bit);

	print_bits(bit); // imprime 00010000
	write(1, "\n", 1);

	return (0);
}*/