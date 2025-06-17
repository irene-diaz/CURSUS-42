
#include <stdio.h>
//calcula cuántos caracteres del principio de una cadena (s) no contienen ninguno de los caracteres de otra cadena (reject).
size_t	ft_strcspn(const char *s, const char *reject)
{
    int i = 0;

    //recorremos s
    while(s[i])
    {
        //iniciamos aqui el contador de reject
        int j = 0;
        //recorremos reject
        while(reject[j])
        {
            //Devuelve la cantidad de caracteres recorridos hasta que encuentra un carácter que esté en reject.
            if(s[i]==reject[j])
                //devolvemos i pq es el contador de la longitud d s, y asi se para aqui el programa
                return i;
            j++;
        }
        i++;
    }
    //Si no encuentra ningun caracter igual, devuelve la longitud entera de s.
    return i;
}

/*int main(void)
{
    printf("%ld\n", ft_strcspn("Hola mundo!", "!d"));  // Resultado esperado: 8 (porque 'd' está en la posición 8)
    printf("%ld\n", ft_strcspn("Hola mundo!", "aeiou"));  // Resultado esperado: 1 (porque 'o' está en reject)
    printf("%ld\n", ft_strcspn("Hola mundo!", "xyz"));  // Resultado esperado: 11 (ninguna coincidencia)
}*/