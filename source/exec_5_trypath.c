/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_5_trypath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:59:48 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 12:12:16 by abettini         ###   ########.fr       */
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
	t_list	*tmp;

	arr_paths = NULL;
	tmp = ft_find_var(vars, "PATH");
	if (tmp)
		arr_paths = ft_split(((t_var *)(tmp->content))->value, ':');
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

int	ft_try_path(char **cmd_w_flag, t_msh *msh)
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
			cmd_path = ft_path_join(arr_paths[i], cmd_w_flag[0]);
			if (!access(cmd_path, F_OK))
				ret = ft_execute_cmd(cmd_path, cmd_w_flag, msh);
			free(cmd_path);
			i++;
		}
		ft_free_mat(arr_paths);
	}
	return (ret);
}
