#include <unistd.h>

int ft_strlen(char *str)
{
    int i=0;
    while(*str)
    {
        str++;
        i++;
    }
    return i;
}
int main(int argc, char *argv[])
{
    if(argc==3)
    {
        int len1=ft_strlen(argv[1]);
        char *str1=argv[1];
        char *str2=argv[2];
        int i=0;
        int j=0;
        int cont=0;

        while(str1[i]&&str2[j])
        {
            if(str1[i]==str2[j])
            {
                i++;
                cont++;
            }
            j++;
        }
        
        if(cont==len1)
        {
            write(1, "1", 1);
        }
        else{
            write(1, "0", 1);
        }
    }
    write(1, "\n", 1);
}