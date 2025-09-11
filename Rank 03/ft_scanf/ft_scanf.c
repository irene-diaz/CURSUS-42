#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

/* EOF (End Of File) es una constante (-1) que indica que no hay más datos
   en el flujo (archivo, stdin, etc.). Funciones como fgetc devuelven EOF
   al final de la entrada. */

/* -----------------------------------------------------------
   match_space: lee y descarta todos los espacios en el flujo
   Devuelve:
		0  -> si encontró un carácter no-espacio y lo devuelve al flujo
	-1  -> si llegó a EOF
   ----------------------------------------------------------- */
int	match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF) // leer cada carácter
	{
		if (!isspace(c)) // si no es espacio
		{
			ungetc(c, f); // devolverlo al flujo
			return (0);   // éxito
		}
	}
	return (-1); // EOF
}

/* -----------------------------------------------------------
   match_char: verifica si el siguiente carácter coincide con 'c'
   Devuelve:
		1  -> coincidencia
		0  -> no coincidencia, y devuelve el carácter al flujo
	-1  -> EOF
   ----------------------------------------------------------- */
int	match_char(FILE *f, char c)
{
	int r = fgetc(f); // leer un carácter
	if (r == EOF)
		return (-1);           // EOF
	if (r != (unsigned char)c) // si no coincide
	{
		ungetc(r, f); // devolver al flujo
		return (0);   // fallo
	}
	return (1); // coincidencia
}

/* -----------------------------------------------------------
   scan_char: lee un solo carácter y lo guarda en la dirección
   provista por el argumento variable
   Devuelve:
		1  -> éxito
	-1  -> EOF
   ----------------------------------------------------------- */
int	scan_char(FILE *f, va_list ap)
{
	int c = fgetc(f); // leer un carácter
	if (c == EOF)
		return (-1);                // EOF
	char *ptr = va_arg(ap, char *); // obtener la dirección del char
	*ptr = (char)c;                 // guardar el carácter
	return (1);                     // éxito
}

/* -----------------------------------------------------------
   scan_int: lee un número entero decimal (con signo opcional)
   y lo guarda en la dirección del argumento variable
   Devuelve:
		1  -> éxito
		0  -> no se encontró ningún dígito
	-1  -> EOF antes de encontrar dígito
   ----------------------------------------------------------- */
int	scan_int(FILE *f, va_list ap)
{
	int	*ptr;
	int	c;

	int c, sign = 1, val = 0;
	c = fgetc(f);
	// 1️⃣ saltar espacios iniciales
	while (c != EOF && isspace(c))
	{
		c = fgetc(f); // avanzar hasta encontrar un no-espacio
	}
	// error
	if (c == EOF)
		return (-1);
	// 2️⃣ signo opcional(controlamos signo y avanzamos)
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f); // avanzar al siguiente carácter
	}
	// 3️⃣ si el primer carácter no es dígito
	if (!isdigit(c))
	{
		if (c != EOF)
			ungetc(c, f);
		return (0);
	}
	// 4️⃣ acumular dígitos
	do
	{
		/*es la misma formula que el atoi
		val *= 10;
		val = c - '0';*/
		val = val * 10 + (c - '0');
	} while ((c = fgetc(f)) != EOF && isdigit(c));
	// 5️⃣ devolver último carácter que no es dígito al flujo
	if (c != EOF)
		ungetc(c, f);
	// 6️⃣ guardar valor en la dirección provista
	ptr = va_arg(ap, int *);
	*ptr = val * sign;
	return (1); // exito
}

/* -----------------------------------------------------------
   scan_string: lee una palabra (cadena hasta espacio o EOF)
   y la guarda en el buffer provisto
   Devuelve:
		1  -> éxito
	-1  -> EOF
   ----------------------------------------------------------- */
int	scan_string(FILE *f, va_list ap)
{
	int		c;
	char	*ptr;

	ptr = va_arg(ap, char *);
	c = fgetc(f);
	// 1️⃣ saltar espacios iniciales
	while ((c = fgetc(f)) != EOF && isspace(c))
	{
		c = fgetc(f);
	}
	if (c == EOF)
		return (-1);
	// 2️⃣ leer hasta espacio o EOF
	do
	{
		*ptr++ = (char)c;
	} while ((c = fgetc(f)) != EOF && !isspace(c));
	// 3️⃣ devolver el último carácter que no pertenece a la cadena
	if (c != EOF)
		ungetc(c, f);
	// 4️⃣ terminar la cadena con '\0'
	*ptr = '\0';
	return (1);
}
// Esta  funcion nos la dan hecha!!
/* -----------------------------------------------------------
   match_conv: decide qué función de escaneo usar según la
   conversión del formato (%c, %d, %s)
   ----------------------------------------------------------- */
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return (scan_char(f, ap));
	case 'd':
		match_space(f); // saltar espacios antes de número
		return (scan_int(f, ap));
	case 's':
		match_space(f);
		return (scan_string(f, ap)); // saltar espacios antes de la palabra
	case EOF:
		return (-1);
	default:
		return (-1);
	}
}

// Esta  funcion nos la dan hecha!!
/* -----------------------------------------------------------
   ft_vfscanf: función principal que recorre la cadena de formato
   y aplica conversiones / compara literales
   Devuelve número de conversiones exitosas
   ----------------------------------------------------------- */
int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	c;

	int nconv = 0; // contador de conversiones exitosas
	c = fgetc(f);
	if (c == EOF)
		return (EOF); // flujo vacío
	ungetc(c, f);     // devolver primer carácter al flujo
	while (*format)
	{
		if (*format == '%') // conversión
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break ; // fallo o EOF
			else
				nconv++; // éxito
		}
		else if (isspace(*format)) // espacio en formato
		{
			if (match_space(f) == -1)
				break ; // EOF
		}
		else if (match_char(f, *format) != 1) // literal
			break ;                            // no coincide
		format++;
	}
	if (ferror(f))
		return (EOF); // error en el flujo
	return (nconv);   // número de conversiones exitosas
}

/* -----------------------------------------------------------
   ft_scanf: versión que usa stdin y recibe argumentos variables
   ----------------------------------------------------------- */
int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format); // inicializar lista de argumentos
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap); // limpiar lista de argumentos
	return (ret);
}

/* -----------------------------------------------------------
   Ejemplo de uso
   ----------------------------------------------------------- */
/*int	main(void)
{
	int x;
	char c;
	char s[100];

	// leemos un número, un carácter y una palabra
	ft_scanf("%d %c %s", &x, &c, s);
	printf("Enteros: %d, Char: %c, String: %s\n", x, c, s);
	return (0);
}*/