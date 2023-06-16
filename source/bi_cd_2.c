/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:45:36 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 13:54:08 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to go back to the previous dir ("..")
char	*ft_cd_go_back(char *old_pwd)
{
	int		len;
	int		i;
	char	*new_pwd;

	if (!ft_strncmp(old_pwd, "/", 2))
		return (old_pwd);
	len = ft_strlen(old_pwd);
	while (len > 0 && old_pwd[len] != '/')
		len--;
	new_pwd = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		new_pwd[i] = old_pwd[i];
		i++;
	}
	new_pwd[i] = '\0';
	free(old_pwd);
	return (new_pwd);
}

//moves to a subdir
char	*ft_cd_rel_subdir(char *old_pwd, char *str)
{
	char	*tmp;
	char	*new_pwd;

	if (ft_strncmp(old_pwd, "/", 2))
	{
		tmp = ft_strjoin(old_pwd, "/");
		new_pwd = ft_strjoin(tmp, str);
		free(tmp);
	}
	else
		new_pwd = ft_strjoin(old_pwd, str);
	free(old_pwd);
	return (new_pwd);
}

//handle relative path
char	*ft_cd_relative(char *old_pwd, char *str)
{
	char	*new_pwd;
	char	**moves;
	int		i;

	moves = ft_split(str, '/');
	if (!moves || !*moves)
		return (old_pwd);
	new_pwd = old_pwd;
	i = 0;
	while (moves[i])
	{
		if (!ft_strncmp(moves[i], "..", 3))
			new_pwd = ft_cd_go_back(new_pwd);
		else if (!ft_strncmp(moves[i], ".", 2))
			;
		else
			new_pwd = ft_cd_rel_subdir(new_pwd, moves[i]);
		i++;
	}
	ft_free_mat(moves);
	return (new_pwd);
}