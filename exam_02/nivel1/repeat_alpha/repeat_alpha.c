#include <unistd.h> 
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int i=0;
        int repeat;
        while(argv[1][i])
        {
            char c= argv[1][i];
            if(c>='a' && c<='z')
            {
                repeat=c-'a'+1;
            }
            else if(c>='A' && c<='Z')
            {
                repeat=c-'A'+1;
            }
            else{
                repeat=1;
            }

            while(repeat>0)
            {
                write(1, &c, 1);
                repeat--;
            }
            i++;
        }
        
    }
    write(1, "\n", 1);
}