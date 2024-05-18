/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:00:32 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/04 14:18:29 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd ");
		return (-1);
	}
	return (0);
}

static int	change_to_home(char **path, char *home)
{
	if (home == NULL)
	{
		perror("home not set");
		return (-1);
	}
	*path = home;
	return (0);
}

static void	update_pwd_old_pwd(t_arena *arena, char *cur, t_env **env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		free(path);
		return ;
	}
	unset(env, "OLDPWD");
	add_or_update_env(arena, env, "OLDPWD", cur);
	unset(env, "PWD");
	add_or_update_env(arena, env, "PWD", path);
	free(path);
}

void	ft_cd(t_arena *arena, char *path, t_env *env)
{
	static char	*old;
	char		*home;
	char		*current;

	current = get_dir(arena);
	old = NULL;
	home = getenv("HOME");
	if (path == NULL || ft_strcmp(path, "~") == 0)
		change_to_home(&path, home);
	else if (ft_strcmp(path, "-") == 0)
	{
		if (old == NULL)
		{
			perror("old not set");
			return ;
		}
		path = old;
		printf("%s\n", path);
	}
	if (current == NULL)
		return ;
	change_dir(path);
	update_pwd_old_pwd(arena, current, &env);
	free(old);
	old = current;
}
