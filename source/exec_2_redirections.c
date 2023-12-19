/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:20 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 16:17:38 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//------------------------------------------------------------------------------
// handles "<<" ,"<", ">>", ">" cases 

static void	ft_redir_one_p2(char *str, t_msh *msh)
{
	if (!ft_strncmp(str, ">>", 2))
	{
		if (msh->fd[1] > -1)
			close(msh->fd[1]);
		msh->fd[1] = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd[1] == -1)
			ft_dprintf(2, "minishell: %s: Permission denied\n", str + 2);
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		if (msh->fd[1] > -1)
			close(msh->fd[1]);
		msh->fd[1] = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd[1] == -1)
			ft_dprintf(2, "minishell: %s: Permission denied\n", str + 1);
	}
}

static void	ft_redir_one(char *str, t_msh *msh)
{
	if (!ft_strncmp(str, "<<", 2))
	{
		if (msh->fd[0] > -1)
			close(msh->fd[0]);
		msh->fd[0] = ft_heredoc(&str[2], msh);
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		if (msh->fd[0] > -1)
			close(msh->fd[0]);
		msh->fd[0] = open(str + 1, O_RDONLY);
		if (msh->fd[0] == -1)
			ft_dprintf(2, "minishell: %s: No such file or directory\n", \
				str + 1);
	}
	else
		ft_redir_one_p2(str, msh);
}

int	ft_redirects(t_list *cmd, t_msh *msh)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (!ret && ((t_prs *)(cmd->content))->red[i])
	{
		ft_redir_one(((t_prs *)(cmd->content))->red[i], msh);
		if (msh->fd[0] == -1)
			ret = 1;
		else if (msh->fd[1] == -1)
			ret = 1;
		else if (msh->fd[0] == -3)
			ret = 130;
		i++;
	}
	return (ret);
}

//------------------------------------------------------------------------------
/*
	redirects:
	- to a file		(if opened correctly)
	- to the pipe	(if it didn't even try to open a file) 
*/

void	ft_choose_redir(t_msh *msh, int pipe_in, int pipe_out)
{
	if (msh->fd[0] > -1)
	{
		dup2(msh->fd[0], STDIN_FILENO);
		close(msh->fd[0]);
	}
	if (pipe_in > -1)
	{
		if (msh->fd[0] == -2)
			dup2(pipe_in, STDIN_FILENO);
		close(pipe_in);
	}
	if (msh->fd[1] > -1)
	{
		dup2(msh->fd[1], STDOUT_FILENO);
		close(msh->fd[1]);
	}
	if (pipe_out > -1)
	{
		if (msh->fd[1] == -2)
			dup2(pipe_out, STDOUT_FILENO);
		close(pipe_out);
	}
}

//------------------------------------------------------------------------------
//resets stdin and stdout in case of a single node.

void	ft_reset_redir(t_msh *msh)
{
	if (msh->fd[0] > -1)
		dup2(msh->std[0], STDIN_FILENO);
	msh->fd[0] = -2;
	if (msh->fd[1] > -1)
		dup2(msh->std[1], STDOUT_FILENO);
	msh->fd[1] = -2;
	if (access(HEREDOC_PATH, R_OK))
		unlink(HEREDOC_PATH);
}
