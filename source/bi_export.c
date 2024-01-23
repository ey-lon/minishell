/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:47 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 15:41:18 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//------------------------------------------------------------------------------
//print env if export has no args

static void	ft_print_exp(t_list **vars)
{
	t_list	*tmp;

	tmp = *vars;
	while (tmp)
	{
		if (((t_var *)tmp->content)->exp > 0)
		{
			printf("declare -x %s", ((t_var *)tmp->content)->name);
			if (((t_var *)tmp->content)->exp == 1)
			{
				printf("=\"%s\"", ((t_var *)tmp->content)->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}

//------------------------------------------------------------------------------

static int	ft_exp_check(char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (str[i] && str[i] != '=' && !check)
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			else
				check = 1;
		}
	}
	else
		check = 1;
	if (check)
		ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", str);
	return (check);
}

static void	ft_add_and_export(t_list **vars, char *name, char *value, int exp)
{
	t_var	*var;

	var = ft_add_var_by_name(vars, name, value);
	if (var)
	{
		var->exp = exp;
	}
}

static void	ft_export_var(t_list **vars, char *str)
{
	t_var	*var;
	char	*name;
	int		len;

	len = ft_strlen_mod(str, '=');
	if (len)
	{
		name = ft_substr(str, 0, len);
		var = ((ft_find_var(vars, name)));
		if (var)
		{
			var->exp = 1;
			if (str[len] == '=')
				ft_mod_var_value(var, &str[len + 1]);
		}
		else if (str[len] == '=')
			ft_add_and_export(vars, name, &str[len + 1], 1);
		else
			ft_add_and_export(vars, name, "", 2);
		free(name);
	}
}

//------------------------------------------------------------------------------

int	ft_export(t_list **vars, char **args)
{
	int		i;
	int		ret;

	ret = 0;
	if (args && *args)
	{
		i = 0;
		while (args[i])
		{
			if (!ft_exp_check(args[i]))
				ft_export_var(vars, args[i]);
			else
				ret = 1;
			i++;
		}
	}
	else
	{
		ft_print_exp(vars);
	}
	return (ret);
}

/*
//[depracated]
static void	ft_export_var_by_name(t_list **vars, char *name, int exp)
{
	t_var	*var;

	var = ft_find_var(vars, name);
	if (var)
	{
		var->exp = exp;
	}
}
*/