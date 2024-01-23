/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_4_trypath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:59:48 by abettini          #+#    #+#             */
/*   Updated: 2024/01/23 12:17:23 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FT_TRY_PATH-------------------------------------------------------------------
/*
	if the command is not a built-in,
	it tries to find it in the paths (PATH variable in the env)
*/
static char	**ft_get_path(t_list **vars)
{
	char	**arr_paths;
	t_var	*tmp;

	arr_paths = NULL;
	tmp = ft_find_var(vars, "PATH");
	if (tmp)
		arr_paths = ft_split(tmp->value, ':');
	return (arr_paths);
}

static char	*ft_path_join(char *path, char *cmd)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

int	ft_try_path(char **cmd_f, t_msh *msh)
{
	char	**arr_paths;
	char	*cmd_path;
	int		i;
	int		ret;

	ret = 127;
	arr_paths = ft_get_path(msh->vars);
	if (arr_paths)
	{
		i = 0;
		while (arr_paths[i] && ret == 127)
		{
			cmd_path = ft_path_join(arr_paths[i], cmd_f[0]);
			if (!access(cmd_path, F_OK))
				ret = ft_execute_cmd(cmd_path, cmd_f, msh);
			free(cmd_path);
			i++;
		}
		ft_free_mat(arr_paths);
	}
	if (ret == 127)
		ft_dprintf(2, "minishell: %s: command not found\n", *cmd_f);
	return (ret);
}
