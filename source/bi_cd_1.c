/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:42:05 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 14:14:17 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_1_arg(t_list **vars, char *str)
{
	t_list	*pwd;

	ft_check_pwd(vars);
	pwd = (ft_find_var(vars, "PWD"));
	if (!chdir(str))
	{
		ft_update_oldpwd(vars);
		if (str[0] == '/')
		{
			ft_mod_var_value(pwd, "/");
			((t_var *)(pwd->content))->value = \
				ft_cd_relative(((t_var *)(pwd->content))->value, str + 1);
		}
		else
			((t_var *)(pwd->content))->value = \
				ft_cd_relative(((t_var *)(pwd->content))->value, str);
	}
	else
		perror("cd");
	return (0);
}

int	ft_cd_no_args(t_list **vars)
{
	t_list	*home;
	int		ret;

	home = (ft_find_var(vars, "HOME"));
	ret = 1;
	if (home)
		ret = ft_cd_1_arg(vars, ((t_var *)(home->content))->value);
	return (ret);
}

int	ft_cd(t_list **vars, char **args)
{
	int	ret;

	if (args[0] && args[1])
		return (printf("cd: too many arguments\n") * 0 + 1);
	else if (args[0])
		ret = ft_cd_1_arg(vars, *args);
	else
		ret = ft_cd_no_args(vars);
	return (ret);
}
