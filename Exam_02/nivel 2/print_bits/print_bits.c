
#include <unistd.h>

/*Esta función recibe un número entre 0 y 255 (unsigned char).
Su misión: imprimir los 8 bits de ese número (en binario).*/
void print_bits(unsigned char octet)
{
    int i = 8; // Empezamos con 8 bits (de izquierda a derecha)
    unsigned char bit = 0; //// Variable para guardar temporalmente el bit actual

    while (i--) // Mientras i disminuye de 7 a 0
    {
        /*octet >> i → desplazamos los bits del número i veces a la derecha.

        & 1 → extraemos el bit más a la derecha (0 o 1).

        + 48 → convertimos el número 0 o 1 a su carácter ASCII:

        48 es '0'

        49 es '1'

        */
        bit = (octet >> i & 1) + 48; //es lo mismo que poner + '0'
        write (1, &bit, 1); // Write the ASCII representation of the bit to the standard output (stdout)
    }
}


/* if you want to test your code : */
int main()
{
	unsigned char octet = 3;
	print_bits(octet);
}
