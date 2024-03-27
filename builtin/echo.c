/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:42:27 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/03/27 13:10:30 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	target;
	const char		*ptr;

	target = (unsigned char)c;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == target)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == target)
		return ((char *)ptr);
	return (NULL);
}

int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	if (s)
		write(fd, s, len);
}

static int	count_arg(char **argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		i++;
	}
	return (i);
}

int	ft_echo(char **argument)
{
	int	i;
	int	is_n;
	int	res;

	i = 1;
	is_n = 0;
	res = count_arg(argument);
	if (res > 1)
	{
		while (argument[i] && argument[1][0] == '-' && argument[1][1] == 'n'
			&& ft_strchr(argument[i], 'n'))
		{
			is_n = 1;
			i++;
		}
		while (argument[i])
		{
			ft_putstr_fd(argument[i], 1);
			if (argument[i + 1] && argument[1][0]) // Si il existe un argument suivant et l'argument actuel n'est pas vide, imprime un espace.
				write(1, " ", 1);
			i++;
		}
	}
	if (is_n == 0)
		write(1, "\n", 1);
	return (1);
}

int		main(void)
{
	// Définition des arguments à passer à ft_echo.
	// Nous pouvons définir ici différents scénarios de test.
	char *args[] = {"echo", "-n", "HELLOWOrLD\n", "oui" , NULL};

	// Appel de ft_echo avec le tableau d'arguments défini.
	ft_echo(args);
}