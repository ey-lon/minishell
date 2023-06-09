/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:47 by abettini          #+#    #+#             */
/*   Updated: 2023/06/09 16:02:27 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FT_FIND_VAR-------------------------------------------------------------------
//looks for the variable:
// - in the vars list
t_list	*ft_find_var(t_list **vars, char *var_name)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	tmp = *vars;
	while (tmp && ft_strncmp(var_name, ((t_var *)tmp->content)->name, len + 1))
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

void	ft_exp_var(t_list **vars, t_list *var, char *str, int len)
{
	if (var)
	{
		((t_var *)(var->content))->exp = 1;
		if (len != ft_strlen(str))
		{
			free(((t_var *)(var->content))->value);
			((t_var *)(var->content))->value = ft_strdup(&str[len + 1]);
		}
	}
	else if (len != ft_strlen(str))
		ft_add_var(vars, str, 1);
	else
		ft_add_var(vars, str, 2);
}

void	ft_print_exp(t_list **vars)
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

void	ft_export(t_list **vars, char **mat)
{
	t_list	*var;
	char	*var_name;
	int		len;
	int		i;

	if (mat && *mat)
	{
		i = 0;
		while (mat[i])
		{
			len = ft_strlen_mod(mat[i], '=');
			var_name = ft_substr(mat[i], 0, len);
			var = ((ft_find_var(vars, var_name)));
			free(var_name);
			ft_exp_var(vars, var, mat[i], len);
			i++;
		}	
	}
	else
		ft_print_exp(vars);
}
