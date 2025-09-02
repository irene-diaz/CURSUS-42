typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

int	ft_list_size(t_list *begin_list)
{
	int	i;

	i = 0;
	while (begin_list != 0)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}
/*#include <stdio.h>

int	main(void)
{
	// rellenamos los campos de next y data
	t_list nodo3 = {NULL, "Tercero"}; // el utimo nodo no tiene next
	t_list nodo2 = {&nodo3, "Segundo"};
	t_list nodo1 = {&nodo2, "Primero"};

	printf("Tamaño de la lista: %d\n", ft_list_size(&nodo1)); // 3
	return (0);
}*/