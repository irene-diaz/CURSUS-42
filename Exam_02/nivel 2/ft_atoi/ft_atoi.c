//funcion para identificar espacios
int ft_isspace(int c)
{
    if((c>=9 && c<=13) || c==' ')
    {
        return 1;
    }
    else{
        return 0;
    }
}
//funcion para saber si el caractewr es un numero
int ft_isdigit(int c)
{
    if(c>='0' && c<='9')
    {
        return 1;
    }
    else{
        return 0;
    }
}
int	ft_atoi(const char *str)
{
    int i;
    int s;
    int res;

    res=0;
    i=0;
    s=1;

    //si hay espacios, salta al siguiente caracter
   while(ft_isspace(str[i]))
        i++;

    //si hay simbolos de - y mas salta al siguiente caracter, y si es - pon el s en negativo
    if(str[i]=='-' || str[i]=='+')
    {
        if(str[i]=='-')
            s=-1;
        i++;
    }

    //si el caracter es un numero
    while(ft_isdigit(str[i]))
    {
        //multiplicalo por 10
        res*=10;
        //hazlo numero
        res+=str[i] - '0';
        i++;
    }

    //multiplica el resultado final por el signo
    res=res*s;
    return res;
}