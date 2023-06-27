/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_file_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:20 by abettini          #+#    #+#             */
/*   Updated: 2023/06/26 14:11:52 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
void	ft_heredoc()
 */

/*
int	ft_in_open_err(void)
{
	ft_putstr_fd("No such file or directory\n", 2);
	return (1);
}

int	ft_error_open(void)
{
	ft_putstr_fd("open error\n", 2);
	return (1);
}
*/

int	ft_redir_one(char *str, t_msh *msh)
{
	if (!ft_strncmp(str, "<<", 2))
	{
		//heredoc
		;
	}
	else if (!ft_strncmp(str, ">>", 2))
	{
		if (msh->fd[1] > -1)
			close(msh->fd[1]);
		msh->fd[1] = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		if (msh->fd[1] > -1)
			close(msh->fd[1]);
		msh->fd[1] = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		if (msh->fd[0] > -1)
			close(msh->fd[0]);
		msh->fd[0] = open(str + 1, O_RDONLY);
	}
	return (0);
}

int	ft_redirects(t_list *cmd, t_msh *msh)
{
	int	i;

	i = 0;
	while (((t_prs *)(cmd->content))->red[i])
	{
		if (ft_redir_one(((t_prs *)(cmd->content))->red[i], msh))
			return (1);
		i++;
	}
	return (0);
}
