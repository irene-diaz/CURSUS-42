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

int	main(int argc, char **argv)
{
	int					server_fd;
	int					client_fd;
	int					max_fd;
	int					i;
	int					ret;
	int					next_id;
	char				buf[60000];
	char				msg[70000];
	char				*newline;
	t_client			*clients;
	t_client			*new_client;
	t_client			*next;
	t_client			*tmp;
	fd_set				readfds;
	fd_set				writefds;
	struct sockaddr_in	addr;
	int					j;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		fatal();
	// assign IP, PORT
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	addr.sin_port = htons(atoi(argv[1]));
	// Binding newly created socket to given IP and verification
	if ((bind(server_fd, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
		fatal();
	if (listen(server_fd, 128) < 0)
		fatal();
	clients = NULL;
	next_id = 0;
	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(server_fd, &readfds);
		tmp = clients;
		max_fd = server_fd;
		while (tmp)
		{
			FD_SET(tmp->fd, &readfds);
			if (tmp->out_len > 0)
				FD_SET(tmp->fd, &writefds);
			if (tmp->fd > max_fd)
				max_fd = tmp->fd;
			tmp = tmp->next;
		}
		ret = select(max_fd + 1, &readfds, &writefds, NULL, NULL);
		if (ret < 0)
			fatal();
		if (FD_ISSET(server_fd, &readfds))
		{
			client_fd = accept(server_fd, NULL, NULL);
			if (client_fd < 0)
				fatal();
			new_client = malloc(sizeof(t_client));
			if (!new_client)
				fatal();
			new_client->fd = client_fd;
			new_client->id = next_id++;
			new_client->in = NULL;
			new_client->in_len = 0;
			new_client->out = NULL;
			new_client->out_len = 0;
			new_client->next = clients;
			clients = new_client;
			sprintf(msg, "server: client %d just arrived\n", new_client->id);
			broadcast(clients, new_client->fd, msg, strlen(msg));
		}
	}
}
