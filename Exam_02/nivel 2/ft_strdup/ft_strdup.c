#include <stdlib.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (*str)
	{
		str++;
		i++;
	}
    return i;
}
char    *ft_strdup(char *src)
{
    size_t i;
    size_t len;
    char *dup;

    i=0;
    //sacamos la longitud total de la cadena
    len= ft_strlen(src);
    //reservamos el respectivo espacio de memoria, incluido el final de linea
    dup= (char *)malloc(len+1);

    //proteccion de errores del malloc
    if(!dup)
        return NULL;

    //recorremos el string 
    while(src[i])
    {
        //igualamos un string al otro
        dup[i] = src[i];
        i++;
    }
    //añadimos el final de linea
    dup[i] = '\0';
    
    //retornamos el nuevo puntero
    return dup;
}