#include <stdlib.h>

//devuelve el numero de digitos del int pasado
int count_digits(int n)
{
    int len=1;
    //mientras n se pueda dividir entre 10, dividelo y ve aumentando el contador
    while(n/10)
    {
        n= n/10;
        len++;
    }
    return (len);
}

char	*ft_itoa(int nbr)
{
    char *str;
    int len;
    long nb= nbr; // Usamos long para evitar overflow(Esto es muy importante: si n = -2147483648 (el menor valor de un int), no puedes hacer -n porque no cabe en un int. Usar long evita eso.)
    int is_negative = 0; //para saber si el numero es negativo o no
    
    //la longitud es el numero de digitos de nb
    len=count_digits(nb);

    //si el numero es menor que 0, contamos un digito mas por el menos que llevara delante el numero en cuestion
    if(nb<0)
    {
        nb=-nb;
        is_negative=1; //marcamos que el numero es negativo
        len++; // Por el signo '-'
    }
    //reservamos el espacio de memoria necesario(incluido el '\0')
    str=malloc(len+1);
    if(!str)
        return NULL;
    //añadimos el final de linea al string
    str[len]='\0';

    //recorremos el len al reves, del final al principio
    while (len--)
	{
        //Guardamos el dígito con % 10 y lo convertimos en carácter (+'0')->(guardamos el ultimo digito)
		str[len] = nb % 10 + '0';
        //vamos dividiendo el numero
		nb = nb / 10;
	}
    //si el numero es negativo, añadimos el -
    if(is_negative)
        str[0]='-';
	return (str);
}