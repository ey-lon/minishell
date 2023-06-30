/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_4_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:54:25 by aconta            #+#    #+#             */
/*   Updated: 2023/06/30 12:20:56 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_cmd(char *cmd_path, char **cmd_w_flag, t_list **vars)
{
	char	**env;
	int		pid;
	int		status;

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
	waitpid(pid, &status, 0);
	return (status);
}

# include <dirent.h>

int	ft_check_dir(char *str)
{
	DIR	*test;
	int	check;

	check = 0;
	test = opendir(str);
	if(test)
	{
		closedir(test);
		printf("minishell: %s: Is a directory\n", str);
		check = 1;
	}
	return (check);
}

int	ft_executable(char **cmd_w_flag, t_list **vars)
{
	int	ret;

	if (ft_check_dir(*cmd_w_flag))
		ret = 126;
	if (ft_strchr(*cmd_w_flag, '/') && !access(*cmd_w_flag, F_OK))
	{
		if (access(*cmd_w_flag, X_OK))
			ret = printf("minishell: %s: Permission denied\n", *cmd_w_flag) \
				* 0 + 126;
		else
			ret = ft_execute_cmd(*cmd_w_flag, cmd_w_flag, vars);
	}
	else if (!ft_strchr(*cmd_w_flag, '/') && ft_try_path(cmd_w_flag, vars))
		ret = 0;
	else
		ret = printf("minishell: %s: command not found\n", *cmd_w_flag) \
			* 0 + 127;
	return (ret);
}

int	ft_execution(char **wrd, t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!*wrd || !**wrd)
		return (127);
	if (!ft_strncmp(*wrd, "echo", 5))
		ft_echo(&wrd[1]);
	else if (!ft_strncmp(*wrd, "env", 4))
		ft_env(msh->vars);
	else if (!ft_strncmp(*wrd, "cd", 3))
		ret = ft_cd(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "pwd", 4))
		ft_pwd(msh->vars);
	else if (!ft_strncmp(*wrd, "export", 7))
		ret = ft_export(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "unset", 6))
		ft_unset(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "exit", 5))
		ret = ft_exit(msh, &wrd[1]);
	else if (ft_variable_cmd(msh->vars, *wrd))
		ret = ft_execution(wrd + 1, msh);
	else
		ret = ft_executable(wrd, msh->vars);
	return (ret);
}
