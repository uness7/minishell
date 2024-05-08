/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:38:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/08 18:49:55 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	**ft_split_2(const char *str)
{
	int		inside_quotes;
	int		word_count;
	int		str_length;
	char	**result;
	int		word_index;
	int		start_index;
	int		quoted_start;

	inside_quotes = 0;
	word_count = 0;
	str_length = strlen(str);
	for (int i = 0; i < str_length; i++)
	{
		if (is_quote(str[i]))
		{
			inside_quotes = !inside_quotes;
		}
		else if (!inside_quotes && is_space(str[i]) && (i == 0
				|| !is_quote(str[i - 1])))
		{
			word_count++;
		}
	}
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL); // Memory allocation failed
	word_index = 0;
	start_index = 0;
	quoted_start = -1;
	for (int i = 0; i <= str_length; i++)
	{
		if (is_quote(str[i]))
		{
			inside_quotes = !inside_quotes;
			if (inside_quotes)
				quoted_start = i;
			else
			{
				if (quoted_start != -1 && i - start_index > 1)
				{
					result[word_index] = (char *)malloc((i - start_index + 1)
							* sizeof(char));
					strncpy(result[word_index], str + start_index, i
						- start_index);
					result[word_index][i - start_index] = '\0';
					word_index++;
				}
				start_index = i + 1;
				quoted_start = -1;
			}
		}
		else if (!inside_quotes && (is_space(str[i]) || str[i] == '\0'))
		{
			if (i > start_index)
			{
				result[word_index] = (char *)malloc((i - start_index + 1)
						* sizeof(char));
				strncpy(result[word_index], str + start_index, i - start_index);
				result[word_index][i - start_index] = '\0';
				word_index++;
			}
			start_index = i + 1;
		}
	}
	result[word_index] = NULL;
	return (result);
}

void	custom_cd(t_arena *arena, char *input, t_env *env)
{
	char	*cmd;
	char	*path;
	char	**args;
	int		i;

	i = 0;
	args = ft_split(arena, input, ' ');
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("too many arguments :( \n");
		return ;
	}
	cmd = ft_strtok_2(input, " \t\n");
	path = ft_strtok_2(NULL, " \t\n");
	(void)cmd;
	ft_cd(arena, path, env);
}

bool	check_env_var_rules(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (!isdigit(name[i]) && !isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	custom_export(t_stock *stock, char *input)
{
	char	*cmd;
	char	*var;
	char	*value;
	char	*name;
	char	**args;

	(void)cmd;
	cmd = ft_strtok_2(input, " \t\n");
	var = ft_strtok_2(NULL, "\t\n");
	if (var == NULL)
		print_env(stock->env);
	else
	{
		args = ft_split_2(var);
		if (args != NULL)
		{
		while (*args)
			{
				if (ft_strstr(*args, "="))
				{
					name = ft_strtok_2(*args, "=");
					if (isdigit(name[0]) && check_env_var_rules(name))
					{
						printf("bash: export: `%s': not a valid identifier\n", *args);
						return ;
					}
					value = ft_strtok_2(NULL, "=");
					if (value == NULL)
						value = ft_strdup(stock->arena, "(null)");
					if (ft_strncmp(value, "\"", 1) != 0 && ft_strncmp(value,
								"\'", 1) != 0)
						value = ft_strtok_2(value, " ");
					else
						++value;
					if (value != NULL && name != NULL)
						add_or_update_env(stock->arena, &(stock->env), name,
								trim_quotes(stock->arena, value));
				}
				args++;
			}
		}
	}
}
