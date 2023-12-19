/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:43:13 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 16:14:32 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//----------------------------------------------
void	ft_update_oldpwd(t_list **vars, char *pwd)
{
	t_list	*tmp;
	char	*str;

	tmp = ft_find_var(vars, "OLDPWD");
	if (tmp)
		ft_mod_var_value(tmp, pwd);
	else
	{
		str = ft_strjoin("OLDPWD=", pwd);
		ft_add_var(vars, str, 0);
		free(str);
	}
}

void	ft_update_pwd(t_list **vars)
{
	t_list	*tmp;
	char	pwd[1024];
	char	*str;

	getcwd(pwd, 1024);
	tmp = ft_find_var(vars, "PWD");
	if (tmp)
		ft_mod_var_value(tmp, pwd);
	else
	{
		str = ft_strjoin("PWD=", pwd);
		ft_add_var(vars, str, 0);
		free(str);
	}
}

//----------------------------------------------
void	ft_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
}
