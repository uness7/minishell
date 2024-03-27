/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:09:52 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/03/27 17:38:33 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_put(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
        return (NULL);
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    write(1, "\n", 1);
}
int ft_envi(t_env *env)
{
    while(env && env->next != NULL)
    {
        ft_put(env->value);
        env = env->next;
    }
    if(env)
        ft_put(env->next);
    return(SUCCES);
}