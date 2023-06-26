/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:32:12 by abettini          #+#    #+#             */
/*   Updated: 2023/06/26 15:54:27 by abettini         ###   ########.fr       */
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

void	ft_mod_var_value(t_list *vars, char *str)
{
	if (vars)
	{
		if (((t_var *)(vars->content))->value)
			free(((t_var *)(vars->content))->value);
		((t_var *)(vars->content))->value = ft_strdup(str);
	}
}

void	ft_add_var(t_list **vars, char *str, int exp)
{
	t_var	*new;
	int		len;

	new = malloc(sizeof(t_var));
	if (!new)
		return ;
	len = ft_strlen_mod(str, '=');
	new->name = ft_substr(str, 0, len);
	if (str[len] == '=')
		len++;
	new->value = ft_substr(str, len, ft_strlen(str) - len);
	new->exp = exp;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
}

void	ft_handle_var(t_list **vars, char *str)
{
	t_list	*tmp;
	int		len;
	char	*var_name;

	len = ft_strlen_mod(str, '=');
	if (len)
	{
		var_name = ft_substr(str, 0, len);
		tmp = ft_find_var(vars, var_name);
		free(var_name);
		if (!tmp)
			ft_add_var(vars, str, 0);
		else
			ft_mod_var_value(tmp, &str[len + 1]);
	}
}
