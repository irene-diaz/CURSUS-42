#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief Structure representing a client in the server
 * This structure holds information about each client connected to the server.
 */
typedef struct s_client
{
	int				fd; //descriptor del socket del cliente
	int				id; //identificador único del cliente que le asigna el servidor
	char			*in; //buffer donde guardamos lo que el cliente ha enviado, pero que todavia no constituye una línea completa (es decir, que no termina en '\n')
	int				in_len; //longitud del buffer in
	char			*out; //mensajes que el servidor tiene que enviar al cliente, pero que todavía no ha enviado
	int				out_len; //longitud del buffer out
	struct s_client	*next;
}					t_client;


/**
 * @brief Function to handle fatal errors
 * This function is called when a fatal error occurs.
 */
void	fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

/**
 * @brief Add data to a buffer
 * This function adds data to a buffer, resizing it if necessary.
 * @param buf Pointer to the buffer
 * @param len Pointer to the length of the buffer
 * @param data Data to add
 * @param data_len Length of the data
 */
void	add_to_buffer(char **buf, int *len, char *data, int data_len)
{
	char	*newbuf;
	int		i;

	//reservamos espacio para el nuevo buffer, que será del tamaño actual + tamaño de los datos a añadir + 1 para el '\0'
	newbuf = realloc(*buf, *len + data_len + 1);
	if (!newbuf)
		fatal();
	i = 0;
	//copiamos los datos al final del buffer
	while (i < data_len)
	{
		newbuf[*len + i] = data[i];
		i++;
	}
	//actualizamos la longitud del buffer y añadimos el terminador nulo
	*len += data_len;
	newbuf[*len] = '\0';
	*buf = newbuf;
}

/**
 * @brief Remove data from a buffer
 * This function removes data from a buffer, resizing it if necessary.
 * @param buf Pointer to the buffer
 * @param len Pointer to the length of the buffer
 * @param amount Amount of data to remove
 */
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

/**
 * @brief Queue a message for a client
 * This function adds a message to the client's output buffer.
 * @param client The client to which the message should be sent
 * @param msg The message to send
 * @param len The length of the message
 */
void	queue_message(t_client *client, char *msg, int len)
{
	add_to_buffer(&client->out, &client->out_len, msg, len);
}

/**
 * @brief Broadcast a message to all clients
 * This function sends a message to all clients except the one specified.
 * @param clients The list of clients
 * @param except_fd The file descriptor of the client to exclude
 * @param msg The message to send
 * @param len The length of the message
 */
void	broadcast(t_client *clients, int except_fd, char *msg, int len)
{
	t_client	*tmp;

	tmp = clients;
	while (tmp)
	{
		//send the message to all clients except the one with the specified file descriptor
		if (tmp->fd != except_fd)
			queue_message(tmp, msg, len);
		tmp = tmp->next;
	}
}

/**
 * @brief Send pending data to a client
 * This function sends any pending data in the client's output buffer.
 * @param client The client to which the data should be sent
 */
void	send_pending(t_client *client)
{
	int	ret;

	if (!client->out || client->out_len == 0)
		return ;
	ret = send(client->fd, client->out, client->out_len, 0);
	if (ret > 0)
		remove_from_buffer(&client->out, &client->out_len, ret);
}

/**
 * @brief Remove a client from the list
 * This function removes a client from the list of clients.
 * @param clients Pointer to the list of clients
 * @param client The client to remove
 */
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
			close(tmp->fd); // Close the client's socket
			free(tmp->in); // Free the input buffer
			free(tmp->out); // Free the output buffer
			free(tmp); // Free the client structure
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
	int					ret;
	int					next_id;
	int					i;
	char				buf[65536];
	char				msg[70000];
	char				*newline;
	t_client			*clients;
	t_client			*new_client;
	t_client			*tmp;
	struct sockaddr_in	addr;
	fd_set				readfds;
	fd_set				writefds;
	t_client			*next;
	int					j;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	// Create a TCP socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		fatal();
	addr.sin_family = AF_INET;
	// Set the server address to localhost (127.0.0.1)
	addr.sin_addr.s_addr = htonl(2130706433);
	// Set the server port to the value provided as a command-line argument
	addr.sin_port = htons(atoi(argv[1]));
	// Bind the socket to the specified address and port
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		fatal();
	// Start listening for incoming connections
	if (listen(server_fd, 128) < 0)
		fatal();
	clients = NULL;
	next_id = 0;
	// Main server loop
	while (1)
	{
		FD_ZERO(&readfds); // Clear the read file descriptor set
		FD_ZERO(&writefds); // Clear the write file descriptor set
		FD_SET(server_fd, &readfds); // Add the server socket to the read file descriptor set
		max_fd = server_fd; // Initialize the maximum file descriptor value
		tmp = clients; // Start iterating through the list of clients
		// Set the file descriptors for each client in the read and write sets
		while (tmp)
		{
			FD_SET(tmp->fd, &readfds);
			if (tmp->out_len > 0)
				FD_SET(tmp->fd, &writefds);
			if (tmp->fd > max_fd)
				max_fd = tmp->fd;
			tmp = tmp->next;
		}
		// Wait for activity on the sockets using select()
		ret = select(max_fd + 1, &readfds, &writefds, NULL, NULL);
		if (ret < 0)
			fatal();
		
		/* Handle new client connections*/
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

		/* Handle existing clients*/
		tmp = clients;
		while (tmp)
		{
			next = tmp->next;
			/*Send pending data*/
			if (FD_ISSET(tmp->fd, &writefds))
				send_pending(tmp);
			/*Receive data*/
			if (FD_ISSET(tmp->fd, &readfds))
			{
				ret = recv(tmp->fd, buf, sizeof(buf), 0);
				// If the client has disconnected or an error occurred, remove the client
				if (ret <= 0)
				{
					sprintf(msg, "server: client %d just left\n", tmp->id);
					broadcast(clients, tmp->fd, msg, strlen(msg));
					remove_client(&clients, tmp);
				}
				// If data was received, add it to the client's input buffer and process complete lines
				else
				{
					add_to_buffer(&tmp->in, &tmp->in_len, buf, ret);
					/*Process every complete line.*/
					while (1)
					{
						newline = NULL;
						i = 0;
						while (i < tmp->in_len)
						{
							if (tmp->in[i] == '\n')
							{
								newline = &tmp->in[i];
								break ;
							}
							i++;
						}
						if (!newline)
							break ;
						/*"client X: " + line*/
						sprintf(msg, "client %d: ", tmp->id);
						i = strlen(msg);
						/*
							* Copy the complete line,
							* including '\n'.
						*/
						{
							j = 0;
							while (j <= (int)(newline - tmp->in))
							{
								msg[i + j] = tmp->in[j];
								j++;
							}
							msg[i + j] = '\0';
							i += j;
						}
						// Broadcast the message to all other clients except the one that sent it
						broadcast(clients, tmp->fd, msg, i);
						/*Remove processed line.*/
						remove_from_buffer(&tmp->in, &tmp->in_len, newline
							- tmp->in + 1);
					}
				}
			}
			tmp = next;
		}
	}
	return (0);
}
