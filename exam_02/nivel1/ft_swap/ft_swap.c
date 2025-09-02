void	ft_swap(int *a, int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

/*#include <stdio.h>
int main(int argc, char *argv[])
{
    int a = 0;
    int b = 2;
    
    ft_swap(&a, &b);

    printf("%d\n", a);
    printf("%d", b);
}*/