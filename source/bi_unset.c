/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:10:37 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 10:08:59 by abettini         ###   ########.fr       */
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

static int	ft_unset_check(char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	if (ft_isalpha(str[i]))
	{
		i++;
		while (str[i] && !check)
		{
			if (ft_isalnum(str[i]))
				i++;
			else
				check = 1;
		}
	}
	else
		check = 1;
	if (check)
		ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n", str);
	return (check);
}

int	ft_unset(t_list **vars, char **args)
{
	int	i;
	int	ret;

	ret = 0;
	if (args && *args)
	{
		i = 0;
		while (args[i])
		{
			if (!ft_unset_check(args[i]))
				ft_unset_var(vars, args[i]);
			else
				ret = 1;
			i++;
		}
	}
	return (ret);
}
