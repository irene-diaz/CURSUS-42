#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct s_client
{
	int				fd;
	int				id;
	char			*in;
	int				in_len;
	char			*out;
	int				out_len;
	struct s_client	*next;
}					t_client;

void	fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void	add_to_buffer(char **buf, int *len, char *data, int data_len)
{
	char	*newbuf;
	int		i;

	newbuf = realloc(*buf, *len + data_len + 1);
	if (!newbuf)
		fatal();
	i = 0;
	while (i < data_len)
	{
		newbuf[*len + i] = data[i];
		i++;
	}
	*len += data_len;
	newbuf[*len] = '\0';
	*buf = newbuf;
}

void	remove_from_buffer(char **buf, int *len, int amount)
{
	char *newbuf;
	int i;

	if (amount >= *len)
	{
		free(*buf);
		*buf = NULL;
		*len = 0;
		return ;
	}

	newbuf = malloc(*len - amount + 1);
	if (!newbuf)
		fatal();

	i = 0;
	while (i < *len - amount)
	{
		newbuf[i] = (*buf)[amount + i];
		i++;
	}

	newbuf[*len - amount] = '\0';
	free(*buf);
	*buf = newbuf;
	*len -= amount;
}