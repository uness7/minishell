/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redir_heredoc2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:10 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/02 17:59:11 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_args(t_arena *arena, char *input)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = arena_alloc(arena, sizeof(char) * 100);
	if (cmd == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	while (input[i] != '\0')
	{
		cmd[j++] = input[i++];
		if (input[i] == '>')
			break ;
	}
	return (ft_split(arena, cmd, ' '));
}

char	**extract_files(t_arena *arena, char *input)
{
	char	**files;

	files = arena_alloc(arena, sizeof(char *) * 10);
	while (*input != '\0' && *input != '>')
		input++;
	files = ft_split(arena, input, '>');
	return (files);
}

void	run_multiple_redir_out(t_arena *arena, char *input)
{
	char	**args;
	char	**files;

	args = extract_args(arena, input);
	files = extract_files(arena, input);
	while (*args)
		printf("ar %s \n", *args++);
	while (*files)
		printf("file : %s\n", *files++);
}
