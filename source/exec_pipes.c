/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2023/06/14 16:25:54 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_redirects(t_list *cmd)
{
	int	i;

	i = 0;
	while (((t_prs *)(cmd->content))->red[i])
	{
		if (ft_redirects(((t_prs *)(cmd->content))->red[i]))
			return (1);
		i++;
	}
	return (0);
}

int ft_redir_and_exec(t_list *cmd, t_list **vars, int fd_in, int fd_out)
{
	int		s_in;
	int		s_out;

	fd_in = fd_in;
	fd_out = fd_out;
	s_in = dup(STDIN_FILENO);
	s_out = dup(STDOUT_FILENO);
	ft_do_redirects(cmd);
	ft_check_and_execute(((t_prs *)(cmd->content))->wrd, vars);
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
	return (0);
}

int ft_pipes(t_list **cmd, t_list **vars, int fd_out)
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
        ft_pipes(&(*cmd)->next, vars, fd[1]);
    }
	if (fd[1] != -1)
		close(fd[1]);
    return (ft_redir_and_exec(*cmd, vars, fd[0], fd_out));
}
