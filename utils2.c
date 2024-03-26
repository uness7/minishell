/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:22:54 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/26 17:53:29 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
        char    *j_str;
        size_t  i;
        size_t  j;

        j_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
