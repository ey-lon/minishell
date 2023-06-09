/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:32:12 by abettini          #+#    #+#             */
/*   Updated: 2023/06/09 10:19:15 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_var(t_list **vars, char *str, int exp)
{
	t_var	*new;
	int		len;

	new = malloc(sizeof(t_var));
	if (!new)
		return ;
	len = ft_strlen_mod(str, '=');
	new->name = ft_substr(str, 0, len);
	if (ft_strlen(str) != len)
		len++;
	new->value = ft_substr(str, len, ft_strlen(str) - len);
	new->exp = exp;
	ft_lstadd_back(vars, ft_lstnew((void *)new));
}

void	ft_free_varslst(t_list **lst)
{
	t_var	*tmp;

	if (lst && *lst)
	{
		ft_free_varslst(&(*lst)->next);
		tmp = (t_var *)(*lst)->content;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		free(*lst);
	}
}
