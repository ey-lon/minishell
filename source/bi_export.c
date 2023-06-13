/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:47 by abettini          #+#    #+#             */
/*   Updated: 2023/06/13 10:26:58 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_var(t_list **vars, t_list *var, char *str, int len)
{
	if (var)
	{
		((t_var *)(var->content))->exp = 1;
		if (str[len] == '=')
		{
			free(((t_var *)(var->content))->value);
			((t_var *)(var->content))->value = ft_strdup(&str[len + 1]);
		}
	}
	else if (str[len] == '=')
		ft_add_var(vars, str, 1);
	else
		ft_add_var(vars, str, 2);
}

static void	ft_print_exp(t_list **vars)
{
	t_list	*tmp;

	tmp = *vars;
	while (tmp)
	{
		if (((t_var *)tmp->content)->exp > 0)
		{
			printf("declare -x %s", \
				((t_var *)tmp->content)->name);
			if (((t_var *)tmp->content)->exp == 1)
				printf("=\"%s\"", \
					((t_var *)tmp->content)->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
}

void	ft_export(t_list **vars, char **args)
{
	t_list	*var;
	char	*var_name;
	int		len;
	int		i;

	if (args && *args)
	{
		i = 0;
		while (args[i])
		{
			len = ft_strlen_mod(args[i], '=');
			var_name = ft_substr(args[i], 0, len);
			var = ((ft_find_var(vars, var_name)));
			free(var_name);
			ft_export_var(vars, var, args[i], len);
			i++;
		}	
	}
	else
		ft_print_exp(vars);
}
