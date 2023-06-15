/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:14:37 by abettini          #+#    #+#             */
/*   Updated: 2023/06/15 12:03:53 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if PWD doesn't exist or if it's broken
void	ft_check_pwd(t_list **vars)
{
	t_list	*tmp;

	tmp = ft_find_var(vars, "PWD");
	if (!tmp)
	{
		ft_add_var(vars, "PWD=/nfs/homes", 1);
		chdir("/nfs/homes");
	}
	else if (chdir(((t_var *)(tmp->content))->value))
	{
		ft_mod_var_value(tmp, "PWD=/nfs/homes");
		chdir("/nfs/homes");
	}
}

void	ft_clone_env(t_list **vars, char **env)
{
	int		i;
	int		len;
	t_var	*new;

	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(t_var));
		len = ft_strlen_mod(env[i], '=');
		new->name = ft_substr(env[i], 0, len);
		new->value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - len);
		new->exp = 1;
		ft_lstadd_back(vars, ft_lstnew((void *)new));
		i++;
	}
	ft_check_pwd(vars);
}
