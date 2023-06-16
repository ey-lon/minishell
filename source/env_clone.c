/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:14:37 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 10:00:30 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
