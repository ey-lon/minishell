/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2024/01/17 12:03:18 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//------------------------------------------------------------------------------
//single node

static void	ft_update_last_arg(t_list **vars, char **wrd)
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

static int	ft_single_node(t_list *cmd, t_msh *msh)
{
	int	ret;
	int	fd_in;
	int	fd_out;

	fd_in = -2;
	fd_out = -2;
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

//------------------------------------------------------------------------------
//2 or more nodes

static int	ft_handle_node(t_list *cmd, t_msh *msh, int fd_in, int pipe_fd_out)
{
	int		pid;
	int		status;
	int		ret;

	pid = fork();
	if (!pid)
	{
		if (!ft_redirects(cmd, msh))
		{
			ft_choose_redir(msh, fd_in, pipe_fd_out);
			ft_close_fds(msh->std[0], msh->std[1]);
			ret = ft_execution(((t_prs *)(cmd->content))->wrd, msh);
		}
		else
			ret = 1;
		ft_close_fds(fd_in, pipe_fd_out);
		ft_close_fds(msh->std[0], msh->std[1]);
		ft_free_varslst(msh->vars);
		ft_free_cmdlst(msh->cmd);
		exit(ret);
	}
	waitpid(pid, &status, 0);
	ft_close_fds(fd_in, pipe_fd_out);
	ret = ft_get_exit_code(status);
	return (ret);
}

static int	ft_pipes_handler(t_list **cmd, t_msh *msh)
{
	int		pipe_fd[2];
	int		ret;
	int		fd_in;
	t_list	*tmp;

	fd_in = -2;
	ret = 0;
	tmp = *cmd;
	while (tmp)
	{
		if (!tmp->next)
		{
			pipe_fd[0] = fd_in;
			pipe_fd[1] = -2;
		}
		else
		{
			pipe(pipe_fd);
		}
		ret = ft_handle_node(tmp, msh, fd_in, pipe_fd[1]);
		fd_in = pipe_fd[0];
		tmp = tmp->next;
	}
	return (ret);
}

//------------------------------------------------------------------------------

int	ft_pipes(t_list **cmd, t_msh *msh)
{
	int	ret;

	if (!(*cmd)->next)
	{
		ret = ft_single_node(*cmd, msh);
	}
	else
	{
		ret = ft_pipes_handler(cmd, msh);
	}
	return (ret);
}
