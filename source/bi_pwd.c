/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:43:13 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 14:58:40 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//----------------------------------------------
void	ft_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
}

//----------------------------------------------

/*
//[deprecated]
void	ft_update_oldpwd(t_list **vars, char *pwd)
{
	ft_handle_var_by_name(vars, "OLDPWD", pwd);
}
*/

/*
//[deprecated]
void	ft_update_pwd(t_list **vars)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	ft_handle_var_by_name(vars, "PWD", pwd);
}
*/