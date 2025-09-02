#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}
/*#include <stdio.h>
#include <stdlib.h>

// Tu función
void	ft_list_foreach(t_list *begin_list, void (*f)(void *));

// Una función de ejemplo para usar con foreach
void	print_str(void *data)
{
	printf("%s\n", (char *)data);
}

// Crear un nuevo nodo de lista
t_list	*create_node(void *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

int	main(void)
{
	// Creamos nodos manualmente
	t_list *n1 = create_node("Hola");
	t_list *n2 = create_node("Mundo");
	t_list *n3 = create_node("42");
	t_list *n4 = create_node("Exam");

	// Encadenamos
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;

	// Aplicamos foreach con print_str
	ft_list_foreach(n1, &print_str);

	// Liberar memoria
	free(n1);
	free(n2);
	free(n3);
	free(n4);

	return (0);
}*/