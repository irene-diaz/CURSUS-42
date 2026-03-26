#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char *s;

void unexpected(char c)
{
    if(c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");

    exit(1);
}

int sum(void);

int factor(void)
{
    int n;

    if(*s == '\0')
        unexpected(0);

    if (isdigit(*s))
        return *s++ - '0';

    if(*s == '(')
    {
        s++;
        n = sum();

        if(*s != ')')
            unexpected(*s);
        
        s++;
        return n;
    }

    unexpected(*s);
    return 0;
}

int product(void)
{
    int n;
    n=factor();

    while(*s == '*')
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

    while(*s == '+')
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

    result= sum();

    if (*s != '\0')
        unexpected(*s);

    printf("%d\n", result);
    return 0;
}