/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:54:25 by aconta            #+#    #+#             */
/*   Updated: 2023/06/23 10:39:41 by abettini         ###   ########.fr       */
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
	int		pid;
	int		exit_code;

	pid = fork();
	if (!pid)
	{
		env = ft_env_matrix(vars);
		if (execve(cmd_path, cmd_w_flag, env) == -1)
		{
			free(cmd_path);
			ft_free_mat(env);
			exit(EXIT_FAILURE);
		}
		else
			ft_free_mat(env);
		exit(0);
	}
	/* if (WIFEXITED(exit_code))
	{
		return ;
	} */
	//WIFEXITED(exit_code);
	waitpid(pid, &exit_code, 0);
}

int	ft_try_path(char **cmd_w_flag, t_list **vars)
{
	char	**arr_paths;
	char	*cmd_path;
	char	*add_slash;
	int		i;
	int		check;

	check = 0;
	arr_paths = ft_get_path(vars);
	if (arr_paths)
	{
		i = 0;
		while (arr_paths[i] && !check)
		{
			add_slash = ft_strjoin(arr_paths[i], "/");
			cmd_path = ft_strjoin(add_slash, cmd_w_flag[0]);
			free(add_slash);
			if (!access(cmd_path, F_OK))
			{
				ft_execute_cmd(cmd_path, cmd_w_flag, vars);
				check = 1;
			}
			free(cmd_path);
			i++;
		}
		ft_free_mat(arr_paths);
	}
	return (check);
}

void	ft_executable(char **cmd_w_flag, t_list **vars)
{
	if (!access(*cmd_w_flag, F_OK))
	{
		ft_execute_cmd(*cmd_w_flag, cmd_w_flag, vars);
	}
	else if (!ft_strchr(*cmd_w_flag, '/'))
	{
		ft_try_path(cmd_w_flag, vars);
	}
	else
		ft_putstr_fd("Command not found\n", 2);
}

int	ft_execution(char **wrd, t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!*wrd || !**wrd)
		return (1);
	if (!ft_strncmp(*wrd, "echo", 5))
		ft_echo(&wrd[1]);
	else if (!ft_strncmp(*wrd, "env", 4))
		ft_env(msh->vars);
	else if (!ft_strncmp(*wrd, "cd", 3))
		ft_cd(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "pwd", 4))
		ft_pwd(msh->vars);
	else if (!ft_strncmp(*wrd, "export", 7))
		ft_export(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "unset", 6))
		ft_unset(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "exit", 5))
		ft_exit(msh);
	else if (ft_strchr(*wrd, '='))
	{
		ft_handle_var(msh->vars, *wrd);
		ret = ft_execution(wrd + 1, msh);
	}
	else
		ft_executable(wrd, msh->vars);
	return (ret);
}
