/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:47 by abettini          #+#    #+#             */
/*   Updated: 2023/05/30 17:55:44 by abettini         ###   ########.fr       */
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
	while (tmp && !(!ft_strncmp(var_name, ((t_var *)tmp->content)->str, len) \
		&& ((t_var *)tmp->content)->str[len] == '='))
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

void	ft_export(t_list **vars, char *var_name)
{
	t_list	*var;

	var = ((ft_find_var(vars, var_name)));
	if (var)
		((t_var *)(var->content))->exp = true;
}
