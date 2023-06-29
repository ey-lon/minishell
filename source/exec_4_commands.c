/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_4_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:54:25 by aconta            #+#    #+#             */
/*   Updated: 2023/06/29 12:00:57 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_cmd(char *cmd_path, char **cmd_w_flag, t_list **vars)
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
}

void	ft_executable(char **cmd_w_flag, t_list **vars)
{
	if (!access(*cmd_w_flag, F_OK))
	{
		ft_execute_cmd(*cmd_w_flag, cmd_w_flag, vars);
	}
	else if (!ft_try_path(cmd_w_flag, vars))
	{
		ft_putstr_fd("Command not found\n", 2);
	}
}

int	ft_execution(char **wrd, t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!*wrd || !**wrd)
		return (0);
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
		ret = ft_exit(msh, &wrd[1]);
	else if (ft_strchr(*wrd, '=') && *wrd[0] != '=')
	{
		ft_handle_var(msh->vars, *wrd);
		ret = ft_execution(wrd + 1, msh);
	}
	else
		ft_executable(wrd, msh->vars);
	return (ret);
}
