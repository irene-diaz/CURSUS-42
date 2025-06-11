#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}
void print_hex(int number)
{
    int resto;
    int n;
    char *dic;
    dic = "0123456789abcdef";
    if(number>=16)
        print_hex(number/16);
    ft_putchar(dic[number%16]);
}
int ft_atoi(char *nb)
{
   int i=0;
   int result=0;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		result = result * 10 + (nb[i] - '0');
		i++;
	}
	return (result);

}
int main(int argc, char* argv[])
{
    if(argc!=2)
        ft_putchar('\n');
    else
    {
        int number;
        number=ft_atoi(argv[1]);
        
        print_hex(number);
        ft_putchar('\n');
    }
   
    return 0;
}