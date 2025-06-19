unsigned int hcf(unsigned int number1, unsigned int number2)
{
    while (number1 != number2)
    {
        //resta el mayor menos el menor.
        //si n1 es mayor que n2 la resta sera n1-n2
        if (number1 > number2)
            number1 = number1 - number2;
        //si n2 es mayor que n1 la resta sera n2-n1
        else
            number2 = number2 - number1;
    }
    return number1;
}
unsigned int   lcm(unsigned int a, unsigned int b)
{
    unsigned int result;
    if(a==0||b==0)
    {
        return 0;
    }
    
    //LCM(x, y) = | x * y | / HCF(x, y)
    result= (a*b)/hcf(a,b);
    
    return result;
}
