unsigned char	swap_bits(unsigned char octet)
{
    return (octet >> 4 | octet << 4);
}

//#include <stdio.h>
/*int main(void)
{
    unsigned char result = swap_bits(0x41);  // 0x41 = 01000001 en binario
    printf("Resultado: %02x\n", result);     // imprime en hexadecimal
    return 0;
}*/