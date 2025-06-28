unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char result = 0;
	int i = 8; // hay 8 bits en un byte

	while (i--)
	{
		// desplazamos result a la izquierda para hacerle espacio al nuevo bit
		result = (result << 1) | (octet & 1); // añadimos el bit menos significativo de octet
		octet >>= 1; // desplazamos octet a la derecha para pasar al siguiente bit
	}
	return (result);
}