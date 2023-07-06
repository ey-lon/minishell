/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_file_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:20 by abettini          #+#    #+#             */
/*   Updated: 2023/07/05 10:49:38 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_one_p2(char *str, t_msh *msh)
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

void	ft_redir_one(char *str, t_msh *msh)
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
			ft_dprintf(2, "minishell: %s: No such file or directory\n", str + 1);
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
