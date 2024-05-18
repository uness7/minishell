/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:07 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 16:31:43 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_colons(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static char	**ft_extract(t_arena *arena, char *s, t_sk_2 *sk)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	while (++k < ft_count_colons(s) + 1)
	{
		sk->start = i;
		while (s[++i])
			if (s[i] == ':')
				break ;
		sk->result[k] = arena_alloc(arena, sizeof(char) * ((i - sk->start)
					+ 1));
		if (sk->result[k] == NULL)
			return (NULL);
		sk->temp = -1;
		while (++(sk->temp) < (i - sk->start))
			sk->result[k][sk->temp] = s[sk->start + sk->temp];
		sk->result[k][sk->temp] = '\0';
		i++;
	}
	sk->result[ft_count_colons(s) + 1] = NULL;
	return (sk->result);
}

char	**ft_strtok(t_arena *arena, char *s)
{
	char	**result;
	int		temp;
	int		start;
	int		count;
	t_sk_2	*sk;

	if (s == NULL)
		return (NULL);
	count = ft_count_colons(s);
	result = arena_alloc(arena, sizeof(char *) * (count + 2));
	if (result == NULL)
		return (NULL);
	temp = 0;
	start = 0;
	sk = arena_alloc(arena, sizeof(t_sk_2));
	sk->result = result;
	sk->temp = temp;
	sk->start = start;
	return (ft_extract(arena, s, sk));
}

char	*find_paths(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*find_cmd(t_arena *arena, char **paths, char *cmd)
{
	char	*command;
	char	*command0;

	if (paths == NULL)
	{
		printf("There is no PATH :( \n");
		return (NULL);
	}
	while (*paths)
	{
		command0 = ft_strjoin(arena, *paths, "/");
		command = ft_strjoin(arena, command0, cmd);
		if (access(command, 0) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}
