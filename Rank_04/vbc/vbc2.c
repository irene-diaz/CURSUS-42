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
}

int sum(void);

int factor(void)
{
    int n;

    if(*s == '\0')
        unexpected(0);
    
    if(isdigit(*s))
       return *s++ - '0';

}