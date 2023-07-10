/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:42:05 by abettini          #+#    #+#             */
/*   Updated: 2023/07/10 10:29:19 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_1_arg(t_list **vars, char *str)
{
	char	oldpwd[1024];
	int		ret;

	getcwd(oldpwd, 1024);
	ret = 1;
	if (*str && !chdir(str))
	{
		ft_update_oldpwd(vars, oldpwd);
		ft_update_pwd(vars);
		ret = 0;
	}
	else if (*str)
		perror("cd");
	return (ret);
}

int	ft_cd_no_args(t_list **vars)
{
	t_list	*home;
	int		ret;

	ret = 1;
	home = (ft_find_var(vars, "HOME"));
	if (home)
		ret = ft_cd_1_arg(vars, ((t_var *)(home->content))->value);
	else
		ft_dprintf(2, "bash: cd: HOME not set\n");
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
		else
			ft_dprintf(2, "bash: cd: HOME not set\n");
	}
	return (ret);
}

int	ft_cd(t_list **vars, char **args)
{
	int	ret;

	ret = 1;
	if (args[0] && args[1])
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	else if (!args[0] || (args[0][0] == '~' && !args[0][1]))
		ret = ft_cd_no_args(vars);
	else if (args[0][0] == '~')
		ret = ft_cd_tilde(vars, args[0]);
	else
		ret = ft_cd_1_arg(vars, args[0]);
	return (ret);
}
