/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:42:05 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 15:25:31 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_path(t_list **vars, char *str)
{
	char	pwd[1024];
	int		ret;

	ret = 0;
	if (*str)
	{
		getcwd(pwd, 1024);
		if (!chdir(str))
		{
			ft_handle_var_by_name(vars, "OLDPWD", pwd);
			getcwd(pwd, 1024);
			ft_handle_var_by_name(vars, "PWD", pwd);
		}
		else
		{
			ft_dprintf(2, \
				"minishell: cd: %s: No such file or directory\n", str);
			ret = 1;
		}
	}
	return (ret);
}

static int	ft_cd_home(t_list **vars)
{
	t_var	*home;
	int		ret;

	ret = 1;
	home = ft_find_var(vars, "HOME");
	if (home)
	{
		ret = ft_cd_path(vars, home->value);
	}
	else
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
	}
	return (ret);
}

//tilde works except in the case of ~[user]
static int	ft_cd_tilde(t_list **vars, char *str)
{
	t_var	*home;
	int		ret;
	char	*path;

	ret = 1;
	if (!str[1])
	{
		ret = ft_cd_home(vars);
	}
	else if (str[1] == '/')
	{
		home = ft_find_var(vars, "HOME");
		if (home)
		{
			path = ft_strjoin(home->value, &str[1]);
			ret = ft_cd_path(vars, path);
			free(path);
		}
		else
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
		}
	}
	return (ret);
}

int	ft_cd(t_list **vars, char **args)
{
	int	ret;

	ret = 1;
	if (args[0] && args[1])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	}
	else if (!args[0])
	{
		ret = ft_cd_home(vars);
	}
	else if (args[0][0] == '~')
	{
		ret = ft_cd_tilde(vars, args[0]);
	}
	else
	{
		ret = ft_cd_path(vars, args[0]);
	}
	return (ret);
}
