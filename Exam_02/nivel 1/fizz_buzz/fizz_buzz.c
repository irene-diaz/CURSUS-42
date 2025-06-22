#include <unistd.h>

void ft_putnbr(int n)
{
    int numbBase;
    if(n > 10)
        ft_putnbr(n / 10);
    numbBase = (n % 10) + '0';
    write (1, &numbBase, 1);
}

int main(void)
{
 int i=1;
 while(i<=100)
 {
    if(i%3==0)
    {
        write(1,"fizz", 4);
    }
    if(i%5==0)
    {
        write(1,"buzz", 4);
    }
    if(i % 3 != 0 && i % 5 != 0)
        ft_putnbr(i);
   write(1, "\n", 1);
   i++;
 }

}