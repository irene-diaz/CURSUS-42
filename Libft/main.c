/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:44:41 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/10 16:34:59 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("COMPROBACIONES\n");

	printf("COMPROBACION CON FUNCION IS_ALPHA\n");
	printf("Comprobacion con mi propia funcion\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", ft_isalpha('1'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", ft_isalpha('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", ft_isalpha(' '));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", isalpha('1'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", isalpha('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", isalpha(' '));

	printf("\n");

	printf("COMPROBACION CON FUNCION IS_DIGIT\n");
	printf("Comprobacion con mi propia funcion\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", ft_isdigit('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", ft_isdigit('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", ft_isdigit(' '));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", isdigit('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", isdigit('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", isdigit(' '));

	printf("\n");

	printf("COMPROBACION CON FUNCION IS_ALNUM\n");
	printf("Comprobacion con mi propia funcion\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", ft_isalnum('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", ft_isalnum('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", ft_isalnum(' '));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", isalnum('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", isalnum('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", isalnum(' '));

	printf("\n");

	printf("COMPROBACION CON FUNCION IS_ASCII\n");
	printf("Comprobacion con mi propia funcion\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", ft_isascii('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", ft_isascii('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", ft_isascii(' '));
	// comprobacion con caracter no ASCII
	// printf("Salida: %d\n", ft_isascii('¿'));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", isascii('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", isascii('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", isascii(' '));
	// comprobacion con caracter no ASCII
	// printf("Salida: %d\n", isascii('¿'));
	/* printf("Salida:
		%d\n",isascii('ª')); (no funcina pq no entra dentro de un char)*/

	printf("\n");

	printf("COMPROBACION CON FUNCION IS_PRINT\n");
	printf("Comprobacion con mi propia funcion\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", ft_isprint('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", ft_isprint('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", ft_isprint(' '));
	// comprobacion con caracter no ASCII
	printf("Salida: %d\n", ft_isascii(0x80));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %d\n", isprint('8'));
	// comprobacion con caracter alfabetico
	printf("Salida: %d\n", isprint('z'));
	// comprobacion con caracter vacio
	printf("Salida: %d\n", isprint(' '));
	// comprobacion con caracter no imprimible
	printf("Salida: %d\n", isprint(0x80));
	/*1. Usar un literal de tipo wchar_t (caracteres anchos):
	Si estás trabajando con caracteres que no son ASCII y que están fuera del rango del tipo char (por ejemplo,
	caracteres Unicode),
		puedes utilizar un tipo de datos más grande como wchar_t,
		que está diseñado para
	almacenar caracteres de Unicode.
	Ademas habria que incluir estos include:
	#include <wchar.h>  // Para manejar caracteres anchos
	#include <wctype.h> // Para iswprint()*/

	printf("\n");

	printf("COMPROBACION CON FUNCION STRLEN\n");
	printf("Comprobacion con mi propia funcion\n");
	/*strlen() devuelve un valor de tipo size_t.
	%d se usa para enteros tipo int,
	pero size_t puede ser un unsigned long u otro tipo
	dependiendo del sistema.
	%zu es el especificador correcto y seguro para imprimir valores
		de tipo size_t.*/
	// comprobacion con caracter no alfabetico
	printf("Salida: %zu\n", ft_strlen("Holii"));
	// comprobacion con caracter alfabetico
	printf("Salida: %zu\n", ft_strlen(""));
	// comprobacion con caracter vacio
	printf("Salida: %zu\n", ft_strlen("1 2 2"));
	printf("Comprobacion con la funcion original\n");
	// comprobacion con caracter no alfabetico
	printf("Salida: %zu\n", strlen("Holii"));
	// comprobacion con caracter alfabetico
	printf("Salida: %zu\n", strlen(""));
	// comprobacion con caracter vacio
	printf("Salida: %zu\n", strlen("1 2 2"));

	printf("\n");

	printf("COMPROBACION CON FUNCION MEMSET \n");
	printf("Comprobacion con mi propia funcion\n");
	char str[] = "Hola mundo";
	printf("Salida:%s\n", str);
	ft_memset(str, 36, 3);
	printf("Salida:%s\n", str);
	printf("Comprobacion con la funcion original\n");
	char str2[] = "Hola mundo";
	printf("Salida:%s\n", str2);
	memset(str2, 36, 3);
	printf("Salida:%s\n", str2);

	printf("\n");

	// como memset pero rellena con \n
	printf("COMPROBACION CON FUNCION BZERO \n");
	printf("Comprobacion con mi propia funcion\n");
	char str3[] = "Hola mundo";
	printf("Salida:%s\n", str3);
	ft_bzero(str3, 3);
	printf("Salida:%s\n", str3);
	printf("Comprobacion con la funcion original\n");
	char str4[10] = "Hola mundo";
	printf("Salida:%s\n", str4);
	/* no muestra nada mas desde el caracter 6,
		pq a partir de ahi añadimos caracteres nulos*/
	bzero(&str4[6], 3);
	printf("Salida:%s\n", str4);

	printf("\n");

	printf("COMPROBACION CON FUNCION MEMCPY \n");
	printf("Comprobacion con mi propia funcion\n");
	char s1[] = "Hola mundo";
	char s2[] = "Adios gente";
	printf("Salida:%s\n", s1);
	ft_memcpy(s1, s2, 3);
	printf("Salida:%s\n", s1);
	printf("Comprobacion con la funcion original\n");
	char s3[] = "Hola mundo";
	printf("Salida:%s\n", s3);
	memcpy(s3, s2, 3);
	printf("Salida:%s\n", s3);

	printf("\n");

	printf("COMPROBACION CON FUNCION MEMMOVE \n");
	printf("Comprobacion con mi propia funcion\n");
	char dest[] = "Hola mundo";
	char src[] = "Adios gente";
	printf("Salida:%s\n", s1);
	ft_memmove(dest, src, 3);
	printf("Salida:%s\n", s1);
	printf("Comprobacion con la funcion original\n");
	char dest2[] = "Hola mundo";
	printf("Salida:%s\n", s3);
	memcpy(dest2, src, 3);
	printf("Salida:%s\n", s3);

	printf("\n");

	printf("COMPROBACION CON FUNCION STRLCPY \n");
	printf("Comprobacion con mi propia funcion(la funcion original no la tenemos incluida)\n");
	char source[] = "Hola, mundo";
	char dst[20];
	/* pone size como 4,
		pero aparentemente corta 3 caracteres por el final de string*/
	unsigned int size = 4;
	unsigned int len = ft_strlcpy(dst, source, size);
	printf("Copiado: %s\n", dst);
	printf("Longitud de src:%u\n", len);

	printf("\n");

	printf("COMPROBACION CON FUNCION STRLCAT \n");
	printf("Comprobacion con mi propia funcion(la funcion original no la tenemos incluida)\n");
	char src5[] = "hola";
	char dest5[10] = "adios";
	printf("%zu\n", ft_strlcat(dest5, src5, sizeof(dest5)));

	printf("\n");

	printf("COMPROBACION CON FUNCION TOUPPER \n");
	printf("Comprobacion con mi propia funcion\n");
	printf("%c\n", ft_toupper('a'));
	printf("%c\n", ft_toupper('1'));
	printf("Comprobacion con la funcion original\n");
	printf("%c\n", toupper('a'));
	printf("%c\n", toupper('1'));

	printf("\n");

	printf("COMPROBACION CON FUNCION TOLOWER \n");
	printf("Comprobacion con mi propia funcion\n");
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower('1'));
	printf("Comprobacion con la funcion original\n");
	printf("%c\n", tolower('a'));
	printf("%c\n", tolower('1'));

	printf("\n");
	printf("COMPROBACION CON FUNCION STRCHR \n");
	const char *texto = "Hola mundo";
	char *ptr;
	const char *texto2 = "Hola mundo";
	char *ptr2;
	ptr = strchr(texto, 'm');
	printf("Comprobacion con mi propia funcion\n");
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	ptr2 = ft_strchr(texto2, 'm');
	printf("Comprobacion con la funcion original\n");
	if (ptr2 != NULL)
		printf("Encontrado: %s\n", ptr2); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");

	printf("\n");
	printf("COMPROBACION CON FUNCION STRCHR \n");
	ptr = strrchr(texto, 'm');
	printf("Comprobacion con mi propia funcion\n");
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	ptr2 = ft_strrchr(texto2, 'm');
	printf("Comprobacion con la funcion original\n");
	if (ptr2 != NULL)
		printf("Encontrado: %s\n", ptr2); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	return (0);
}