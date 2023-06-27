/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:42:05 by abettini          #+#    #+#             */
/*   Updated: 2023/06/21 11:07:21 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_1_arg(t_list **vars, char *str)
{
	t_list	*pwd;

	ft_check_pwd(vars);
	pwd = (ft_find_var(vars, "PWD"));
	if (*str && !chdir(str))
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
	else if (*str)
		perror("cd");
	return (0);
}

int	ft_cd_no_args(t_list **vars)
{
	t_list	*home;
	int		ret;

	ret = 1;
	home = (ft_find_var(vars, "HOME"));
	if (home)
		ret = ft_cd_1_arg(vars, ((t_var *)(home->content))->value);
	return (ret);
}

//tilde works except in the case of ~[user]
int	ft_cd_tilde(t_list **vars, char *str)
{
	t_list	*home;
	int		ret;
	char	*path;

	ret = 1;
	if (!str[1])
		ret = ft_cd_no_args(vars);
	else if (str[1] == '/')
	{
		home = (ft_find_var(vars, "HOME"));
		if (home)
		{
			path = ft_strjoin(((t_var *)(home->content))->value, &str[1]);
			ret = ft_cd_1_arg(vars, path);
			free(path);
		}
	}
	return (ret);
}

int	ft_cd(t_list **vars, char **args)
{
	int	ret;

	ret = 1;
	if (args[0] && args[1])
		return (printf("cd: too many arguments\n") * 0 + 1);
	else if (!args[0] || (args[0][0] == '~' && !args[0][1]))
		ret = ft_cd_no_args(vars);
	else if (args[0][0] == '~')
		ret = ft_cd_tilde(vars, args[0]);
	else
		ret = ft_cd_1_arg(vars, args[0]);
	return (ret);
}
