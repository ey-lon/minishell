/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:54:25 by aconta            #+#    #+#             */
/*   Updated: 2023/06/20 11:25:02 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_execute_cmd(char *cmd_path, char **cmd_w_flag, t_list **vars)
{
	char	**env;

	env = ft_env_matrix(vars);
	if (execve(cmd_path, cmd_w_flag, env) == -1)
	{
		free(cmd_path);
		ft_free_mat(env);
		exit(EXIT_FAILURE);
	}
	else
		ft_free_mat(env);
}

void	ft_try_path(char **cmd_w_flag, t_list **vars)
{
	char	**arr_paths;
	char	*cmd_path;
	char	*add_slash;
	int		i;

	arr_paths = ft_get_path(vars);
	i = 0;
	if (arr_paths)
	{
		while (arr_paths[i])
		{
			add_slash = ft_strjoin(arr_paths[i], "/");
			cmd_path = ft_strjoin(add_slash, cmd_w_flag[0]);
			free(add_slash);
			if (!access(cmd_path, F_OK))
			{
				ft_free_mat(arr_paths);
				ft_execute_cmd(cmd_path, cmd_w_flag, vars);
			}
			else
				free(cmd_path);
			i++;
		}
		ft_free_mat(arr_paths);
	}
	ft_putstr_fd("Command not found\n", 2);
}

int	ft_execution(char **wrd, t_list **vars)
{
	int	ret;

	ret = 0;
	if (!*wrd || !**wrd)
		return (1);
	if (!ft_strncmp(*wrd, "echo", 5))
		ft_echo(&wrd[1]);
	else if (!ft_strncmp(*wrd, "env", 4))
		ft_env(vars);
	else if (!ft_strncmp(*wrd, "cd", 3))
		ft_cd(vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "pwd", 4))
		ft_pwd(vars);
	else if (!ft_strncmp(*wrd, "export", 7))
		ft_export(vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "unset", 6))
		ft_unset(vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "exit", 5))
		ft_exit(vars);
	else if (ft_strchr(*wrd, '='))
	{
		ft_handle_var(vars, *wrd);
		ret = ft_execution(wrd + 1, vars);
	}
	else
		ft_try_path(wrd, vars);
	return (ret);
}
