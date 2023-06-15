/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:43:13 by abettini          #+#    #+#             */
/*   Updated: 2023/06/15 12:07:24 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_list **vars)
{
	t_list	*tmp;

	tmp = ft_find_var(vars, "PWD");
	if (tmp)
		return (printf("%s\n", ((t_var *)(tmp->content))->value) * 0);
	return (1);
}
