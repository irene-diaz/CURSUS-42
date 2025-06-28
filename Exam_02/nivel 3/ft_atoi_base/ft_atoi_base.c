// Función que convierte un carácter a su valor numérico según su posición en base 16
int get_digit_value(char c) {
    if (c >= '0' && c <= '9')        // Si el carácter está entre '0' y '9'
        return (c - '0');            // Ej: '3' - '0' = 3 → devuelve 3
    if (c >= 'a' && c <= 'f')        // Si el carácter está entre 'a' y 'f' (letras minúsculas)
        return (c - 'a' + 10);       // Ej: 'a' - 'a' = 0 → 0 + 10 = 10 → devuelve 10
    if (c >= 'A' && c <= 'F')        // Si el carácter está entre 'A' y 'F' (letras mayúsculas)
        return (c - 'A' + 10);       // Ej: 'B' - 'A' = 1 → 1 + 10 = 11 → devuelve 11
    return -1;                       // Si el carácter no es válido para la base → -1
}

// Función principal: convierte un string en una base dada (hasta base 16) a decimal
int	ft_atoi_base(const char *str, int str_base)
{
    int result = 0;     // Acumula el número final convertido
    int sign = 1;       // Para manejar si el número es negativo o positivo
    int value;          // Para guardar el valor de cada carácter convertido

    // Si el primer carácter es un signo '-', marcamos como número negativo
    if (*str == '-') {
        sign = -1;
        str++;          // Avanzamos al siguiente carácter (para ignorar el '-')
    }

    // Recorremos el string carácter por carácter
    while (*str)
    {
        value = get_digit_value(*str);  // Convertimos el carácter a su valor numérico

        // Si el valor no es válido o excede la base, terminamos el bucle
        if (value < 0 || value >= str_base)
            break;

        // Acumulamos el valor convirtiendo a base 10:
        // Por ejemplo, para base 16: result = result * 16 + valor_actual
        /*result es la posicion(cambia cuando se gestiona el primer caracter), str_base es la base y value es el valor en decimal que tiene la letra*/
        result = result * str_base + value;
        

        str++;  // Avanzamos al siguiente carácter
    }

    // Aplicamos el signo al resultado final
    return result * sign;
}

/*int main(void)
{
    printf("%d\n", ft_atoi_base("A", 16));        // 10
    printf("%d\n", ft_atoi_base("10", 2));        // 2
    printf("%d\n", ft_atoi_base("FF", 16));       // 255
    printf("%d\n", ft_atoi_base("-FF", 16));      // -255
    printf("%d\n", ft_atoi_base("21", 4));        // 9
    return 0;

        EJEMPLOS
        FF
        0*16+15=15
        15*16+15= 255

        10
        0*2+1= 1
        1*2+0=2;

        21
        0*4+2= 2
        2*4+1= 9
}*/