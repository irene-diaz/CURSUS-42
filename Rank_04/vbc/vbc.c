#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int g_error = 0;
char *s;

void unexpected(char c)
{
    if(c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");

    g_error = 1;
}

int sum(void);

int factor(void)
{
    int n;
    
    if(g_error)
        return 0;

    if(*s == '\0')
        return(unexpected(0), 0);

    if (isdigit(*s))
        return *s++ - '0';

    if(*s == '(')
    {
        s++;
        n = sum();

        if(*s != ')')
            return(unexpected(*s), 0);
        
        s++;
        return n;
    }

    unexpected(*s);
    return 0;
}

int product(void)
{
    int n;
    n = factor();

    while(*s == '*' && !g_error)
    {
        s++;
        n *= factor();
    }

    return n;
}

int sum(void)
{
    int n;
    n = product();

    while(*s == '+' && !g_error)
    {
        s++;
        n += product();
    }

    return n;
}

int main(int argc, char *argv[])
{
    int result;

    if(argc != 2)
        return 1;

    s = argv[1];

    result = sum();

    if (!g_error && *s != '\0')
        unexpected(*s);

    if (!g_error)
        printf("%d\n", result);
        
    return g_error;
}