/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:54:25 by aconta            #+#    #+#             */
/*   Updated: 2023/12/19 17:13:29 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	ft_execute_cmd(char *cmd_path, char **cmd_f, t_msh *msh)
{
	char	**env;
	int		pid;
	int		status;
	int		ret;

	pid = fork();
	if (!pid)
	{
		env = ft_env_from_list_to_matrix(msh->vars);
		if (execve(cmd_path, cmd_f, env) == -1)
		{
			free(cmd_path);
			ft_free_mat(env);
			ft_free_cmdlst(msh->cmd);
			ft_free_varslst(msh->vars);
			ft_close_fds(msh->std[0], msh->std[1]);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	ret = ft_get_exit_code(status);
	return (ret);
}

//------------------------------------------------------

static int	ft_check_dir(char *str)
{
	DIR	*test;

	test = opendir(str);
	return (closedir(test) + 1);
}

static int	ft_executable(char **cmd_f, t_msh *msh)
{
	int	ret;

	ret = 127;
	if (ft_strchr(*cmd_f, '/') && cmd_f[0][ft_strlen(*cmd_f) - 1] != '/' \
		&& !access(*cmd_f, F_OK) && !ft_check_dir(*cmd_f))
	{
		if (access(*cmd_f, X_OK))
			ret = ft_dprintf(2, "minishell: %s: Permission denied\n", \
				*cmd_f) * 0 + 126;
		else
			ret = ft_execute_cmd(*cmd_f, cmd_f, msh);
	}
	else if (!ft_strchr(*cmd_f, '/'))
		ret = ft_try_path(cmd_f, msh);
	else if (ft_check_dir(*cmd_f))
		ret = ft_dprintf(2, "minishell: %s: Is a directory\n", *cmd_f) \
			* 0 + 126;
	else
		ft_dprintf(2, "minishell: %s: No such file or directory\n", *cmd_f);
	return (ret);
}

//------------------------------------------------------

static int	ft_execution_p2(char **wrd, t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(*wrd, "cd", 3))
		ret = ft_cd(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "export", 7))
		ret = ft_export(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "unset", 6))
		ret = ft_unset(msh->vars, &wrd[1]);
	else if (!ft_strncmp(*wrd, "exit", 5))
		ret = ft_exit(msh, &wrd[1]);
	else if (ft_variable_cmd(msh->vars, *wrd))
		ret = ft_execution(wrd + 1, msh);
	else
		ret = ft_executable(wrd, msh);
	return (ret);
}

int	ft_execution(char **wrd, t_msh *msh)
{
	int	ret;

	ret = 0;
	while (*wrd && !**wrd)
		wrd++;
	if (!*wrd)
		return (0);
	if (!ft_strncmp(*wrd, "echo", 5))
		ft_echo(&wrd[1]);
	else if (!ft_strncmp(*wrd, "env", 4))
		ft_env(msh->vars);
	else if (!ft_strncmp(*wrd, "pwd", 4))
		ft_pwd();
	else
		ret = ft_execution_p2(wrd, msh);
	return (ret);
}
