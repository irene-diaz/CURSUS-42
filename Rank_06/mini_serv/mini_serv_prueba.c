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
	char			*out;
	int				out_len;
	struct s_client	*next;
}					t_client;

/* GIVEN */
int	extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

/* GIVEN */
char	*str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void	fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void	broadcast(t_client *clients, int except_fd, char *data, int len)
{
	t_client	*tmp;
	char		*newbuf;
	int			i;

	tmp = clients;
	while (tmp)
	{
		if (tmp->fd != except_fd)
		{
			i = 0;
			newbuf = realloc(tmp->out, tmp->out_len + len + 1);
			if (!newbuf)
				fatal();
			while (i < len)
			{
				newbuf[tmp->out_len + i] = data[i];
				i++;
			}
			tmp->out_len += len;
			newbuf[tmp->out_len] = '\0';
			tmp->out = newbuf;
		}
		tmp = tmp->next;
	}
}

void	send_pending(t_client *client)
{
	int	ret;
	int	i;

	if (client->out_len == 0)
		return ;
	ret = send(client->fd, client->out, client->out_len, 0);
	if (ret > 0)
	{
		i = 0;
		while (i < client->out_len - ret)
		{
			client->out[i] = client->out[ret + i];
			i++;
		}
		client->out_len -= ret;
		client->out[client->out_len] = '\0';
	}
}

void	remove_client(t_client **clients, t_client *client)
{
	t_client	*tmp;
	t_client	*prev;

	tmp = clients;
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
	int server_fd;
	int client_fd;
	int max_fd;
	int next_id;
	int ret;
	char buf[60000];
	char msg[70000];
	char *newline;
	t_client *clients;
	t_client *new_client;
	t_client *tmp;
	t_client *next;
	fd_set readfds;
	fd_set writefds;
	struct sockaddr_in addr;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	// socket create and verification
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

	next_id = 0;
	clients = NULL;

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
			new_client->out = NULL;
			new_client->out_len = 0;
			new_client->next = clients;
			clients = new_client;

			sprintf(msg, "server: client %d just arrived\n", new_client->id);
			broadcast(clients, new_client->fd, msg, strlen(msg));
		}
	}
}