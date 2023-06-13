/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:39:29 by aconta            #+#    #+#             */
/*   Updated: 2023/06/13 16:53:30 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_redir_exec(t_list *cmd, t_list **vars, int fd_in, int fd_out)
{
    int 	i;
	int		s_in;
	int		s_out;

	s_in = dup(STDIN_FILENO);
	s_out = dup(STDOUT_FILENO);
	i = 0;
	while (((t_prs *)(cmd->content))->red[i]) //exec all redirects (loop for all RED)
	{
		if (ft_redirects(((t_prs *)(cmd->content))->red[i]));
			return ;
		i++;
	}
	ft_check_and_execute(((t_prs *)(cmd->content))->wrd, vars); //exec cmds (check_and_execute();)
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
}

//void? argomenti?
void ft_pipes(t_list **cmd, t_list **vars, int fd_out)
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
    return (ft_redir_exec(*cmd, vars, fd[0], fd_out));
}
