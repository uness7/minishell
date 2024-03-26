/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:55:40 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/26 17:05:50 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
 * execvp()
 * execve(cmd_path, av, envp);
 *
 * cmd_paths = find_cmd_path(envp);
 * cmd_path = ft_strtok(cmd_paths);
 */

int	ft_count_colons(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ':')
			count++;
		i++;
	}
	return (count);
}

char	**ft_extract(char *s, char **res, int start, int temp)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (++k < ft_count_colons(s) + 1)
	{
		start = i;
		while (s[i])
		{
			if (s[i] == ':')
				break ;
			i++;
		}
		res[k] = malloc(sizeof(char) * ((i - start) + 1));
		if (res[k] == NULL)
			return (NULL);
		temp = -1;
		while (++temp < (i - start))
			res[k][temp] = s[start + temp];
		res[k][temp] = '\0';
		i++;
	}
	res[ft_count_colons(s) + 1] = NULL;
	return (res);
}

char	**ft_strtok(char *s)
{
	char	**result;
	int		temp;
	int		start;
	int		count;

	count = ft_count_colons(s);
	result = malloc(sizeof(char *) * (count + 2));
	if (result == NULL)
		return (NULL);
	temp = 0;
	start = 0;
	return (ft_extract(s, result, start, temp));
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned int)s1[i] > (unsigned int)s2[i])
			return (1);
		else if ((unsigned int)s1[i] < (unsigned int)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*find_path(char **envp)
{
	if (envp == NULL)
		return (NULL);
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*find_cmd(char **paths, char *cmd)
{
	char	*command;
	char	*command0;

	while (*paths)
	{
		command0 = ft_strjoin(*paths, "/");
		command = ft_strjoin(command0, cmd);
		free(command0);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}


char	*ft_strdup(const char *s)
{
	size_t		s_size;
	char		*block;
	int			i;
	const char	*temp;

	s_size = 0;
	temp = s;
	while (*s)
	{
		s_size++;
		s++;
	}
	block = (char *)malloc(s_size + 1);
	if (block == NULL)
		return (NULL);
	i = 0;
	while (temp[i] != '\0')
	{
		block[i] = temp[i];
		i++;
	}
	block[i] = '\0';
	return (block);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*j_str;
	size_t	i;
	size_t	j;

	j_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!j_str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		j_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		j_str[i] = s2[j];
		i++;
		j++;
	}
	j_str[i] = '\0';
	return (j_str);
}
