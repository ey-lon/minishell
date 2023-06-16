/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:43:13 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 13:28:45 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//updates oldpwd
int	ft_update_oldpwd(t_list **vars)
{
	t_list	*oldpwd;
	t_var	*pwd;
	char	*tmp;

	oldpwd = ft_find_var(vars, "OLDPWD");
	pwd = (t_var *)(ft_find_var(vars, "PWD")->content);
	if (oldpwd)
		ft_mod_var_value(oldpwd, pwd->value);
	else
	{
		tmp = ft_strjoin("OLDPWD=", pwd->value);
		ft_add_var(vars, tmp, 1);
		free(tmp);
	}
	return (0);
}

//checks if PWD doesn't exist or if it's broken
void	ft_check_pwd(t_list **vars)
{
	t_list	*tmp;

	tmp = ft_find_var(vars, "PWD");
	if (!tmp)
	{
		ft_add_var(vars, "PWD=/nfs/homes", 1);
		chdir("/nfs/homes");
		ft_update_oldpwd(vars);
	}
	else if (chdir(((t_var *)(tmp->content))->value))
	{
		ft_mod_var_value(tmp, "/nfs/homes");
		chdir("/nfs/homes");
		ft_update_oldpwd(vars);
	}
}

int	ft_pwd(t_list **vars)
{
	t_list	*tmp;

	ft_check_pwd(vars);
	tmp = ft_find_var(vars, "PWD");
	if (tmp)
		return (printf("%s\n", ((t_var *)(tmp->content))->value) * 0);
	return (1);
}
