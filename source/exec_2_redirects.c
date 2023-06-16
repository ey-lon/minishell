/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:20 by abettini          #+#    #+#             */
/*   Updated: 2023/06/16 12:05:11 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
void	ft_heredoc()
 */

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

int	ft_redir_one(char *str)
{
	int	fd;
	int check;

	check = 0;
	if (!ft_strncmp(str, "<<", 2))
	{
		//heredoc
		;
	}
	else if (!ft_strncmp(str, ">>", 2))
	{
		fd = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (ft_error_open());
		dup2(fd, STDOUT_FILENO);
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		fd = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_error_open());
		dup2(fd, STDOUT_FILENO);
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		fd = open(str + 1, O_CREAT | O_RDONLY);
		if (fd == -1)
			return (ft_in_open_err());
		dup2(fd, STDIN_FILENO);
	}
	else
		check = 1;
	if (!check)
		close(fd);
	return (0);
}

int	ft_redirects(t_list *cmd)
{
	int	i;

	i = 0;
	while (((t_prs *)(cmd->content))->red[i])
	{
		if (ft_redir_one(((t_prs *)(cmd->content))->red[i]))
			return (1);
		i++;
	}
	return (0);
}