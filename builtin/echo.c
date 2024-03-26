/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:42:27 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/03/26 14:56:03 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char		target;
	const char			*ptr;

	target = (unsigned char)c;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == target)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == target)
		return ((char *)ptr);
	return (NULL);
}
int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	if (s)
		write(fd, s, len);
}
static  int count_arg(char **argument)
{
    int i;

    i = 0;
    while(argument[i])
    {
        i++;
    }
    return (i);
}

                                    // index for pars echo argument + is_n bollen that chekc if there is a n via the fonction 
int ft_echo(char **argument)
{
    int index;
    int is_n;
    int res;

    index = 1;
    is_n = 0;
    res = count_arg(argument);
    if (res > 1)
    {
        while(argument[index] && argument[1][0] == '-' && argument[1][1] == 'n' && ft_strchr(argument[index], 'n'))
        {
            is_n = 1;
            index++;
        }
        while(argument[index])
        {
            ft_putstr_fd(argument[index], 1);
            if(argument[index + 1] && argument[1][0])
                write(1, " ", 1);
            index++;
        }
    }
    if (is_n == 0)
        write(1, "\n", 1);    
    return (1);
}

int main(int argc, char *argv[])
{
        ft_echo(argv);
}