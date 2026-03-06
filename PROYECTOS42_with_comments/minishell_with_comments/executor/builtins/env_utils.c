/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:34:30 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/06 17:50:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Verifica si el identificador es válido */
static int	is_valid_identifier(char *s)
{
	int	i;

	// Verifica si el primer carácter es una letra o un guion bajo
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	// Verifica si el resto de la cadena es válido
	while (s[i] && s[i] != '=')
	{
		// Verifica si el carácter es alfanumérico o un guion bajo
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Maneja identificadores inválidos */
int	handle_invalid_identifier(t_cmd *cmd, char *identifier)
{
	// Verifica si el identificador es válido
	if (!is_valid_identifier(identifier))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		// Establece el código de salida a 1 para indicar error
		if (cmd->exitcode)
			*cmd->exitcode = 1;
		return (1);
	}
	return (0);
}

/* Copia el entorno */
char	**copy_env(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	// Cuenta el número de variables de entorno
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	// Copia las variables de entorno
	while (envp[i])
	{
		/* Copia cada variable de entorno usando ft_strdup,
			para asegurar que cada cadena es independiente */
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	// Asegura que la última posición del nuevo entorno sea NULL
	new[i] = NULL;
	return (new);
}

/* Obtiene el valor de una variable de entorno */
char	*get_env_var(t_cmd *cmd, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key); // Longitud de la clave
	// Recorre las variables de entorno
	while ((*cmd->env_ptr)[i])
	{
		// Compara la clave con la variable de entorno actual
		if (!ft_strncmp((*cmd->env_ptr)[i], key, len)
			&& (*cmd->env_ptr)[i][len] == '=')
			return ((*cmd->env_ptr)[i] + len + 1);
		i++;
	}
	return (NULL);
}
