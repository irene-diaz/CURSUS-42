#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc==4)
    {
        int result=0;
        int n1=atoi(argv[1]);
        int n2=atoi(argv[3]);

        char sign= argv[2][0];

        if(sign=='+')
            result = n1+n2;
        else if(sign=='-')
            result= n1-n2;
        else if(sign=='*')
            result= n1*n2;
        else if(sign=='/')
            result= n1/n2;
        else if(sign=='%')
            result= n1%n2;

        printf("%d", result);

    }
        
    printf("%c", '\n');
}