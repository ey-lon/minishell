/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2023/06/21 16:29:26 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_node(t_list *cmd, t_msh *msh, int fd_in, int fd_out)
{
	int		s_in;
	int		s_out;

	//fork();
	(void)fd_in;
	(void)fd_out;
	s_in = dup(STDIN_FILENO);
	s_out = dup (STDOUT_FILENO);
	ft_redirects(cmd);
	ft_execution(((t_prs *)(cmd->content))->wrd, msh);
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
	return (0);
}

int ft_pipes(t_list **cmd, t_msh *msh, int fd_out)
{
    int fd[2];

    if (!(*cmd)->next)
	{
		fd[0] = 0;
		fd[1] = -1;
	}
	else
    {
        pipe(fd);
        ft_pipes(&(*cmd)->next, msh, fd[1]);
    }
	if (fd[1] != -1)
		close(fd[1]);
    return (ft_handle_node(*cmd, msh, fd[0], fd_out));
}
