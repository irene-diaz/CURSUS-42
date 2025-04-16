/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:44:41 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/16 16:28:20 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char str[] = "Hola mundo";
	char str2[] = "Hola mundo";
	char str3[] = "Hola mundo";
	char str4[10] = "Hola mundo";
	char s1[] = "Hola mundo";
	char s2[] = "Adios gente";
	char s3[] = "Hola mundo";
	char dest[] = "Hola mundo";
	char src[] = "Adios gente";
	char dest2[] = "Hola mundo";
	char source[] = "Hola, mundo";
	char dst[20];
	unsigned int size;
	unsigned int len;
	char src5[] = "hola";
	char dest5[10] = "adios";
	const char *texto = "Hola mundo";
	char *ptr;
	const char *texto2 = "Hola mundo";
	char *ptr2;
	unsigned int length;
	char str8[] = "abz";
	char str9[] = "aba";
	int n;
	int n2;
	char str10[] = "Hola mundo";
	char *ptr3;
	char *ptr4;
	char s4[] = "Hola\0mundo";
	char s5[] = "Hola\0zorro";
	char *big;
	char *little;
	char *resultado;
	int *nums;
	int *nums2;
	int *nums3;
	int *nums4;
	char *original;
	char *copia;
	char *copia2;

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
	printf("Salida:%s\n", str);
	ft_memset(str, 36, 3);
	printf("Salida:%s\n", str);
	printf("Comprobacion con la funcion original\n");
	printf("Salida:%s\n", str2);
	memset(str2, 36, 3);
	printf("Salida:%s\n", str2);
	printf("\n");
	// como memset pero rellena con \n

	printf("COMPROBACION CON FUNCION BZERO \n");
	printf("Comprobacion con mi propia funcion\n");
	printf("Salida:%s\n", str3);
	ft_bzero(str3, 3);
	printf("Salida:%s\n", str3);
	printf("Comprobacion con la funcion original\n");
	printf("Salida:%s\n", str4);
	/* no muestra nada mas desde el caracter 6,
		pq a partir de ahi añadimos caracteres nulos*/
	bzero(&str4[6], 3);
	printf("Salida:%s\n", str4);
	printf("\n");

	printf("COMPROBACION CON FUNCION MEMCPY \n");
	printf("Comprobacion con mi propia funcion\n");
	printf("Salida:%s\n", s1);
	ft_memcpy(s1, s2, 3);
	printf("Salida:%s\n", s1);
	printf("Comprobacion con la funcion original\n");
	printf("Salida:%s\n", s3);
	memcpy(s3, s2, 3);
	printf("Salida:%s\n", s3);
	printf("\n");

	printf("COMPROBACION CON FUNCION MEMMOVE \n");
	printf("Comprobacion con mi propia funcion\n");
	printf("Salida:%s\n", s1);
	ft_memmove(dest, src, 3);
	printf("Salida:%s\n", s1);
	printf("Comprobacion con la funcion original\n");
	printf("Salida:%s\n", s3);
	memcpy(dest2, src, 3);
	printf("Salida:%s\n", s3);
	printf("\n");

	printf("COMPROBACION CON FUNCION STRLCPY \n");
	printf("Comprobacion con mi propia funcion(la funcion original no la tenemos incluida)\n");
	/* pone size como 4,
		pero aparentemente corta 3 caracteres por el final de string*/
	size = 4;
	len = ft_strlcpy(dst, source, size);
	printf("Copiado: %s\n", dst);
	printf("Longitud de src:%u\n", len);
	printf("\n");

	printf("COMPROBACION CON FUNCION STRLCAT \n");
	printf("Comprobacion con mi propia funcion(la funcion original no la tenemos incluida)\n");
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

	printf("COMPROBACION CON FUNCION STRRCHR \n");
	ptr = strrchr(texto, 'm');
	printf("Comprobacion con la funcion original\n");
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	ptr2 = ft_strrchr(texto2, 'm');
	printf("Comprobacion con mi propia funcion\n");
	if (ptr2 != NULL)
		printf("Encontrado: %s\n", ptr2); // Imprime "mundo"
	else
		printf("No se encontró el carácter\n");
	printf("\n");

	printf("COMPROBACION CON FUNCION STRNCMP \n");
	length = 3;
	n = ft_strncmp(str8, str9, length);
	n2 = strncmp(str8, str9, length);
	printf("Comprobacion con la funcion original\n");
	printf("%i\n", n2);
	printf("Comprobacion con mi propia funcion\n");
	printf("%i\n", n);
	printf("\n");
	//test que petaba por no poner unsigned char(ya qu e sino pudes meter caracteres no ASCII)
	ft_strncmp("test\200", "test\0", 6);
	
	printf("COMPROBACION CON FUNCION MEMCHR \n");
	printf("Comprobacion con la funcion original\n");
	// Buscamos la letra 'm' en los primeros 10 bytes
	ptr3 = memchr(str10, 'm', 10);
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr3); // Debería imprimir: "mundo"
	else
		printf("No se encontró el carácter.\n");
	printf("Comprobacion con mi propia funcion\n");
	// Buscamos la letra 'm' en los primeros 10 bytes
	ptr4 = ft_memchr(str10, 'm', 10);
	if (ptr != NULL)
		printf("Encontrado: %s\n", ptr4); // Debería imprimir: "mundo"
	else
		printf("No se encontró el carácter.\n");
	printf("\n");
	printf("COMPROBACION CON FUNCION MEMCMP \n");
	printf("Comprobacion con la funcion original\n");
	printf("memcmp: %d\n", memcmp(s4, s5, 10));
	printf("Comprobacion con mi propia funcion\n");
	printf("ft_memcmp: %d\n", ft_memcmp(s4, s5, 10));
	printf("\n");
	printf("COMPROBACION CON FUNCION STRNSTR \n");
	big = "Hola mundo bonito!";
	little = "mun";
	printf("Comprobacion con mi propia funcion(la funcion original no la tenemos incluida)\n");
	resultado = ft_strnstr(big, little, 10);
	if (resultado)
		printf("Encontrado: %s\n", resultado); // Debería imprimir: "mundo!"
	else
		printf("No encontrado.\n");
	printf("\n");
	printf("COMPROBACION CON FUNCION ATOI \n");
	printf("Resultado ft_atoi: %d\n", ft_atoi("-7"));
	printf("Resultado atoi: %d\n", atoi("-7"));
	printf("Resultado ft_atoi: %d\n", ft_atoi("--7"));
	printf("Resultado atoi: %d\n", atoi("--7"));
	printf("Resultado ft_atoi: %d\n", ft_atoi("    7"));
	printf("Resultado atoi: %d\n", atoi("    7"));
	printf("Resultado ft_atoi: %d\n", ft_atoi("+7"));
	printf("Resultado atoi: %d\n", atoi("+7"));
	printf("\n");

	// FUNCIONES
	printf("COMPROBACION CON FUNCION CALLOC \n");
	printf("Comprobacion con mi propia funcion\n");
	nums = ft_calloc(5, sizeof(int));
	if (!nums)
	{
		printf("Error en calloc\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
		printf("%d ", nums[i]); // Debería imprimir: 0 0 0 0 0
	free(nums);
	printf("\n");
	nums2 = ft_calloc(0, sizeof(int));
	if (!nums2)
	{
		printf("Error en calloc\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
		printf("%d ", nums2[i]); // Debería imprimir: 0 0 0 0 0
	free(nums2);
	printf("\n");
	printf("Comprobacion con la funcion original\n");
	nums3 = ft_calloc(5, sizeof(int));
	if (!nums3)
	{
		printf("Error en calloc\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
		printf("%d ", nums3[i]); // Debería imprimir: 0 0 0 0 0
	free(nums3);
	printf("\n");
	nums4 = ft_calloc(0, sizeof(int));
	if (!nums4)
	{
		printf("Error en calloc\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
		printf("%d ", nums4[i]); // Debería imprimir: 0 0 0 0 0
	free(nums4);
	printf("\n");

	printf("\n");

	printf("COMPROBACION CON FUNCION STRDUP \n");
	original = "Hola mundo!";
	printf("Comprobacion con mi propia funcion\n");
	copia = ft_strdup(original);
	if (copia)
	{
		printf("Original: %s\n", original);
		printf("Duplicado: %s\n", copia);
		free(copia);
	}
	printf("Comprobacion con la funcion original\n");
	copia2 = ft_strdup(original);
	if (copia2)
	{
		printf("Original: %s\n", original);
		printf("Duplicado: %s\n", copia2);
		free(copia2);
	}

	printf("\n");

	// FUNCIONES ADICIONALES
	printf("%s\n", ft_substr("Hola me llamo Irene", 2, 5));
	printf("%s\n", ft_strjoin("Hola", "Adios"));
	printf("%s\n", ft_strtrim("supercalifragi", "sui"));
	return (0);

	/*FUNCION CALLOC
	#include "libft.h"
	#include <stdlib.h>
	void	*ft_calloc(size_t nmemb, size_t size)
	{
	//si el tamaño o el nº de elementos es 0, devuelve un puntero unico
	if (nmemb == 0 || size == 0)
	{
		nbytes = 1;
		ptr = malloc(1);
	}
	//sino crea un malloc de los bytes necesarios,
		si supera el limite devuelve NULL
	else
	{
		nbytes = nmemb * size;
		if (nbytes / nmemb != size)
			return (NULL);
		ptr = malloc(nbytes);
	}
	//protegemos cualquier error del puntero final, mandando NULL
	if (!ptr)
		return (NULL);
	//rellenamos con 0 las memoria
	ft_bzero(ptr, nbytes);
	//finalmente liberamos la memoria
	free(ptr);
	//devolvemos el puntero
	return (ptr);
	❌ ¿Por qué NO debes hacer free() dentro de calloc?
	Porque entonces estarías liberando la memoria antes de que nadie la pueda usar,
		y además
	retornarías un puntero a memoria que ya ha sido liberada (¡muy peligroso!)
}*/

	/*FUNCION STRDUP
	char	*ft_strdup(const char *s)
	{
		size_t i;
		size_t len;
		char *dup;
		//consigo la longitud de s
		while (s[len])
			len++;
		//asignamos un espacio mas, para guardar el '\0'
		dup = (char *)malloc(len + 1);
		//protegemos cualquier error del puntero final, mandando NULL
		if (!dup)
			return (NULL);
		//rellenamos el puntero con los mismos valores de s + '\0'
		while (i<len+1)
		{
			dup[i] = s[i];
			i++;
		}
		// dup[i] = '\0'; explícito, fácil de ver(en vez de len+1)
		return (dup);
	} */
}