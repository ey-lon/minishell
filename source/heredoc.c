/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:49:26 by abettini          #+#    #+#             */
/*   Updated: 2023/06/28 12:29:30 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_sighandler(int signal)
{
	static int	pid;

	if (signal == CTRL_C)
	{
		if (!pid)
			kill(pid, SIGKILL);
	}
}

void	ft_heredoc_write(char *tempfilename, const char *delimiter)
{
	int		tempfilefd;
	char	*str;
	int		len;

	tempfilefd = open(tempfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tempfilefd == -1)
		return ;
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, delimiter, len) && str[len] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, tempfilefd);
		free(str);
	}
	close(tempfilefd);
}

int	ft_heredoc(const char *delimiter, t_msh *msh)
{
	int		pid;
	char	*heredoc_path;
	int		fd;
	int		ec;

	signal(CTRL_C, ft_heredoc_sighandler);
	heredoc_path = "/tmp/.heredoc";
	pid = fork();
	if (!pid)
	{
		ft_heredoc_write(heredoc_path, delimiter);
		ft_free_cmdlst(msh->cmd);
		ft_free_varslst(msh->vars);
		exit(0);
	}
	else
		waitpid(pid, &ec, 0);
	fd = open(heredoc_path, O_RDONLY);
	return (fd);
}