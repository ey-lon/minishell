/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:32:12 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 15:49:07 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FT_FIND_VAR-------------------------------------------------------------------
//looks for the variable:
// - in the vars list
t_var	*ft_find_var(t_list **vars, char *name)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(name);
	tmp = *vars;
	while (tmp && ft_strncmp(name, ((t_var *)tmp->content)->name, len + 1))
		tmp = tmp->next;
	if (tmp)
		return ((t_var *)tmp->content);
	return (NULL);
}

void	ft_mod_var_value(t_var *var, char *str)
{
	if (var)
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(str);
	}
}

/*
//[deprecated]
void	ft_add_var_by_str(t_list **vars, char *str, int exp)
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
} */

t_var	*ft_add_var_by_name(t_list **vars, char *name, char *value)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->exp = 0;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
	return (new);
}

void	ft_handle_var_by_name(t_list **vars, char *name, char *value)
{
	t_var	*tmp;
	char	*str;

	tmp = ft_find_var(vars, name);
	if (tmp)
	{
		ft_mod_var_value(tmp, value);
	}
	else
	{
		str = ft_strjoin(name, value);
		ft_add_var_by_name(vars, name, value);
		free(str);
	}
}

void	ft_handle_var_by_str(t_list **vars, char *str)
{
	int		len;
	char	*name;

	len = ft_strlen_mod(str, '=');
	if (len)
	{
		name = ft_substr(str, 0, len);
		ft_handle_var_by_name(vars, name, &str[len + 1]);
		free(name);
	}
}
