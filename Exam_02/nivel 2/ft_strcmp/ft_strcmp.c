int ft_strcmp(const char *s1, const char *s2)
{
    int i=0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return(s1[i] - s2[i]);
        i++;
    }
    return(s1[i] - s2[i]);
}
