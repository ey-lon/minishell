/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2023/08/17 13:29:18 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_last_arg(t_list **vars, char **wrd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (wrd[i] && wrd[i + 1])
		i++;
	if (wrd[i])
	{
		tmp = ft_strjoin("_=", wrd[i]);
		ft_handle_var(vars, tmp);
		free(tmp);
	}
}

int	ft_single_node(t_list *cmd, t_msh *msh, int fd_in, int fd_out)
{
	int	ret;

	ret = ft_redirects(cmd, msh);
	if (!ret)
	{
		ft_choose_redir(msh, fd_in, fd_out);
		ret = ft_execution(((t_prs *)(cmd->content))->wrd, msh);
	}
	ft_reset_redir(msh);
	ft_update_last_arg(msh->vars, ((t_prs *)(cmd->content))->wrd);
	return (ret);
}

int	ft_handle_node(t_list *cmd, t_msh *msh, int fd_in, int fd_out)
{
	int		pid;
	int		status;
	int		ret;

	pid = fork();
	if (!pid)
	{
		if (!ft_redirects(cmd, msh))
		{
			ft_choose_redir(msh, fd_in, fd_out);
			ret = ft_execution(((t_prs *)(cmd->content))->wrd, msh);
		}
		else
			ret = 1;
		ft_free_varslst(msh->vars);
		ft_free_cmdlst(msh->cmd);
		exit(ret);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	close(fd_in);
	return (status);
}

int	ft_pipes_handler(t_list **cmd, t_msh *msh, int fd_out)
{
	int	fd[2];

	if (!(*cmd)->next)
	{
		fd[0] = dup(msh->std[0]);
		fd[1] = -2;
	}
	else
	{
		pipe(fd);
		ft_pipes_handler(&(*cmd)->next, msh, fd[1]);
	}
	if (fd[1] > -1)
		close(fd[1]);
	return (ft_handle_node(*cmd, msh, fd[0], fd_out));
}

int	ft_pipes(t_list **cmd, t_msh *msh)
{
	int	ret;

	if (!(*cmd)->next)
	{
		ret = ft_single_node(*cmd, msh, 0, 1);
	}
	else
	{
		ret = ft_pipes_handler(cmd, msh, 1);
	}
	return (ret);
}
