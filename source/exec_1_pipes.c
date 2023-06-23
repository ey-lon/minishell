/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2023/06/23 11:20:20 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_choose_redir(t_msh *msh, int fd_in, int fd_out)
{
	//input----------------------
	if (msh->fd[0] > -1)
		dup2(msh->fd[0], 0);
	else if (msh->fd[0] == -2)
		dup2(fd_in, 0);
	//output---------------------
	if (msh->fd[1] > -1)
		dup2(msh->fd[1], 1);
	else if (msh->fd[1] == -2)
		dup2(fd_out, 1);
}

void	ft_reset_redir(t_msh *msh)
{
	//input----------------------
	if (msh->fd[0] > -1)
		close(msh->fd[0]);
	msh->fd[0] = -2;
	dup2(msh->std[0], 0);
	//output---------------------
	if (msh->fd[1] > -1)
		close(msh->fd[1]);
	msh->fd[1] = -2;
	dup2(msh->std[1], 1);
}

int ft_handle_node(t_list *cmd, t_msh *msh, int fd_in, int fd_out)
{
	int		pid;
	int		exit_code;

	pid = fork();
	if (!pid)
	{
		ft_redirects(cmd, msh);
		ft_choose_redir(msh, fd_in, fd_out);
		ft_execution(((t_prs *)(cmd->content))->wrd, msh);
		ft_reset_redir(msh);
		exit(0);
	}
	waitpid(pid, &exit_code, 0);
	close(fd_in);
	return (0);
}

int ft_pipes(t_list **cmd, t_msh *msh, int fd_out)
{
    int fd[2];

    if (!(*cmd)->next)
	{
		fd[0] = dup(msh->std[0]);
		fd[1] = -2;
	}
	else
    {
        pipe(fd);
        ft_pipes(&(*cmd)->next, msh, fd[1]);
    }
	if (fd[1] > -1)
		close(fd[1]);
    return (ft_handle_node(*cmd, msh, fd[0], fd_out));
}

