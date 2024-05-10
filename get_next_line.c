/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:50:47 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/10 17:58:15 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin(char *result, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!result)
	{
		result = (char *)malloc(1 * sizeof(char));
		result[0] = '\0';
	}
	if (!result || !buffer)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(result) + ft_strlen(buffer)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (result)
		while (result[++i] != '\0')
			str[i] = result[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft_strlen(result) + ft_strlen(buffer)] = '\0';
	free(result);
	return (str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char) c;
	return (s);
}

char	*ft_update_buffer(char *buffer)
{
	char	*new_buffer;
	int		len;
	int		j;

	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	if (!buffer[len])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - len + 1));
	if (!new_buffer)
		return (NULL);
	len++;
	j = 0;
	while (buffer[len])
		new_buffer[j++] = buffer[len++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	if (buffer[len] == '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_read_data(int fd, char *result)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	ft_memset(buffer, 0, BUFFER_SIZE);
	while (!ft_strchr(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[bytes] = '\0';
		result = strjoin(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_read_data(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	result = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (result);
}
