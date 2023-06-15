/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:10:37 by abettini          #+#    #+#             */
/*   Updated: 2023/06/14 16:50:29 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_var(t_list **vars, char *var_name)
{
	t_list	*scr;
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	scr = *vars;
	if (scr && !ft_strncmp(var_name, ((t_var *)scr->content)->name, len + 1))
	{
		*vars = scr->next;
		ft_free_varsnode(scr);
	}
	else
	{
		while (scr && scr->next \
			&& ft_strncmp(var_name, \
			((t_var *)scr->next->content)->name, len + 1))
			scr = scr->next;
		if (scr && scr->next)
		{
			tmp = scr->next->next;
			ft_free_varsnode(scr->next);
			scr->next = tmp;
		}
	}
}

static int	ft_unset_name_check(char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (str[i] && !check)
	{
		if (!ft_isalnum(str[i]))
			check = 1;
		i++;
	}
	return (check);
}

void	ft_unset(t_list **vars, char **args)
{
	int	i;
	int	check;

	if (args && *args)
	{
		check = 0;
		i = 0;
		while (args[i])
		{
			if (!ft_unset_name_check(args[i]))
				ft_unset_var(vars, args[i]);
			else if (!check)
			{
				ft_printf("unset: %s: invalid parameter name\n", args[i]);
				check = 1;
			}
			i++;
		}
	}
}
