/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:07:27 by abettini          #+#    #+#             */
/*   Updated: 2023/05/30 17:16:58 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list **vars)
{
	t_list	*tmp;

	tmp = *vars;
	while (tmp)
	{
		if (((t_var *)tmp->content)->exp == true)
			printf("%s\n", ((t_var *)tmp->content)->str);
		tmp = tmp->next;
	}
}
