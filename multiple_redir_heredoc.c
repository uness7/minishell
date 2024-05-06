/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redir_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/02 17:59:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_multiple_redir_out(char *command)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '>')
			count++;
		i++;
	}
	if (count > 1)
		return (true);
	return (false);
}

bool	has_multiple_redir_in(char *command)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<')
			count++;
		i++;
	}
	if (count > 1)
		return (true);
	return (false);
}

bool	has_multiple_delimeters(char *command)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] && command[i + 1] == '<')
		{
			count++;
			i++;
		}
		i++;
	}
	if (count > 1)
		return (true);
	return (false);
}

bool	has_multiple_redir_append(char *command)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '>' && command[i + 1] && command[i + 1] == '>')
		{
			count++;
			i++;
		}
		i++;
	}
	if (count > 1)
		return (true);
	return (false);
}

bool	has_multiple_redir_heredoc(char *input)
{
	if (has_multiple_redir_out(input) == true)
		return (true);
	else if (has_multiple_redir_in(input) == true)
		return (true);
	else if (has_multiple_redir_append(input) == true)
		return (true);
	else if (has_multiple_delimeters(input) == true)
		return (true);
	return (false);
}
