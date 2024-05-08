#include "minishell.h"

/*
 *
 * malloc, isalnum, strcpy, strlen
 *
 * */

char    *expand_variables(t_stock *stock, const char *input)
{
        const char      *current;
        char            *out_ptr;
        char            var_name[128];
        int                     var_len;
        char	*var_value;
	char	*start;
        char	*output;
	t_env	*env;
	
	current = input;
	output = arena_alloc(stock->arena, strlen(input) + 1024);
        out_ptr = output;
        while (*current)
        {
		if (*current == '$' && (!(*(current - 1) && *(current - 1) == '\'')))
		{
				current++;
				start = out_ptr;
				var_len = 0;
				while (*current && (*current == '_' || isalnum(*current)))
					var_name[var_len++] = *current++;
				var_name[var_len] = '\0';
				env = find_env_var(&(stock->env), var_name);
				if (env != NULL)
					var_value = env->value;
				else
					var_value = var_name;
				if (var_value)
				{
					ft_strcpy(out_ptr, var_value);
					out_ptr += ft_strlen(var_value);
				}
				else
					out_ptr = start;
                }
		else
			*out_ptr++ = *current++;
        }
        *out_ptr = '\0';
        return (output);
}
