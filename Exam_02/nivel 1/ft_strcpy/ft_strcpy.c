//#include <stdio.h>

char    *ft_strcpy(char *s1, char *s2)
{
    int i;
    i=0;
    //recorro el puntero en el que voy a guardar la info de s1 hasta el final de linea
    while(s2[i]!='\0')
    {
        //igualo sus valores
        s1[i]=s2[i];
        i++;
    }
    //le añado el final de linea 
    s1[i]= '\0';
    return s1;
}

/*int	main(void)
{
	char	src[] = "Hola mundo";
	char	dest[20];
	
	ft_strcpy(dest, src);
	printf("Cadena copiada: %s\n" , dest);

}*/