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
	char	*newbuf;
	int		i;

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

void	queue_message(t_client *client, char *msg, int len)
{
	add_to_buffer(&client->out, &client->out_len, msg, len);
}

void	broadcast(t_client *clients, int except_fd, char *msg, int len)
{
	t_client	*tmp;

	tmp = clients;
	while (tmp)
	{
		if (tmp->fd != except_fd)
			queue_message(tmp, msg, len);
		tmp = tmp->next;
	}
}

void	send_pending(t_client *clients)
{
	int	ret;

	if (!clients->out || clients->out_len == 0)
		return ;
	ret = send(clients->fd, clients->out, clients->out_len, 0);
	if (ret > 0)
		remove_from_buffer(&clients->out, &clients->out_len, ret);
}

void	remove_client(t_client **clients, t_client *client)
{
	t_client	*tmp;
	t_client	*prev;

	tmp = *clients;
	prev = NULL;
	while (tmp)
	{
		if (tmp == client)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*clients = tmp->next;
			close(tmp->fd);
			free(tmp->in);
			free(tmp->out);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
