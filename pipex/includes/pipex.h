/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:41:59 by oem               #+#    #+#             */
/*   Updated: 2025/08/07 18:58:52 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	error_exit(const char *msg);
char	*get_cmd_path(char *cmd);
void	execute_cmd(char *cmd, char **envp);
void	child1_process(char **argv, int *pipe_fd, char **envp);
void	child2_process(char **argv, int *pipe_fd, char **envp);
#endif