/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:47 by abettini          #+#    #+#             */
/*   Updated: 2023/08/14 10:57:43 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_export_var(t_list **vars, t_list *var, char *str, int len)
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

static void	ft_export_var(t_list **vars, char *str)
{
	t_list	*var;
	char	*var_name;
	int		len;

	len = ft_strlen_mod(str, '=');
	if (len)
	{
		var_name = ft_substr(str, 0, len);
		var = ((ft_find_var(vars, var_name)));
		free(var_name);
		ft_set_export_var(vars, var, str, len);
	}
}

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
			{
				ft_export_var(vars, args[i]);
			}
			else
				ret = 1;
			i++;
		}
	}
	else
		ft_print_exp(vars);
	return (ret);
}
