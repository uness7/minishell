/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:00:25 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/04/02 00:27:40 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(t_arena *arena)
{
	char	*dir;

	dir = arena_alloc(arena, PATH_MAX);
	if (dir == NULL)
	{
		printf("Error Allocating Memory\n");
		return (NULL);
	}
	if (getcwd(dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (dir);
}

void	ft_pwd(t_arena *arena)
{
	char	*directory;

	directory = get_dir(arena);
	if (directory != NULL)
		printf("%s\n", directory);
}
