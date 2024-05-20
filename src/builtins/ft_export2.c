#include "minishell.h"

bool	check_env_var_rules(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) && !ft_isalnum(name[i]) && name[i] != '_')
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
					if (ft_isdigit(name[0]) || !check_env_var_rules(name))
					{
						printf("bash: export: `%s': not a valid identifier\n",
							*args);
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
							value);
				}
				args++;
			}
		}
	}
}
