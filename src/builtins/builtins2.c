/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:38:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 15:02:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_word(char *dest, char *src, int start, int end)
{
	ft_strncpy(dest, src + start, end - start);
	dest[end - start] = '\0';
}

void	split_string_helper(t_split_2_state *state, char *str)
{
	if (state->i > state->start_index)
	{
		state->result[state->word_index] = malloc((state->i - state->start_index
					+ 1) * sizeof(char));
		copy_word(state->result[(state->word_index)++], str, state->start_index,
			state->i);
	}
}
