/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:10:07 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/15 11:17:23 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check1(t_node *temp)
{
	if (temp->type == TOKEN_REDIR_IN && temp->next->type == TOKEN_REDIR_IN)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_IN && temp->next->type == TOKEN_REDIR_HEREDOC)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_IN && temp->next->type == TOKEN_REDIR_OUT)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_IN && temp->next->type == TOKEN_REDIR_APPEND)
	{
		printf("Syntax error.  \n");
		return (false);
	}
	return (true);
}

bool	check2(t_node *temp)
{
	if (temp->type == TOKEN_REDIR_OUT && temp->next->type == TOKEN_REDIR_OUT)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_OUT && temp->next->type == TOKEN_REDIR_IN)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_OUT && temp->next->type == TOKEN_REDIR_APPEND)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_OUT
		&& temp->next->type == TOKEN_REDIR_HEREDOC)
	{
		printf("Syntax error. \n");
		return (false);
	}
	return (true);
}

bool	check3(t_node *temp)
{
	if (temp->type == TOKEN_REDIR_APPEND
		&& temp->next->type == TOKEN_REDIR_APPEND)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_APPEND && temp->next->type == TOKEN_REDIR_OUT)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_APPEND && temp->next->type == TOKEN_REDIR_IN)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_APPEND
		&& temp->next->type == TOKEN_REDIR_HEREDOC)
	{
		printf("Syntax error. \n");
		return (false);
	}
	return (true);
}

bool	check4(t_node *temp)
{
	if (temp->type == TOKEN_REDIR_HEREDOC
		&& temp->next->type == TOKEN_REDIR_HEREDOC)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_HEREDOC
		&& temp->next->type == TOKEN_REDIR_OUT)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_HEREDOC && temp->next->type == TOKEN_REDIR_IN)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_HEREDOC
		&& temp->next->type == TOKEN_REDIR_APPEND)
	{
		printf("Syntax error. \n");
		return (false);
	}
	return (true);
}

bool	check5(t_node *temp)
{
	if (temp->type == TOKEN_REDIR_IN && temp->next->type == TOKEN_PIPE)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_OUT && temp->next->type == TOKEN_PIPE)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_APPEND && temp->next->type == TOKEN_PIPE)
	{
		printf("Syntax error. \n");
		return (false);
	}
	if (temp->type == TOKEN_REDIR_HEREDOC && temp->next->type == TOKEN_PIPE)
	{
		printf("Syntax error. \n");
		return (false);
	}
	return (true);
}
