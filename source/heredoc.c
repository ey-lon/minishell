/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:49:26 by abettini          #+#    #+#             */
/*   Updated: 2023/06/29 11:48:25 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_butcher(int pid)
{
	static int	pid_to_kill = 0;

	if (pid_to_kill)
	{
		ft_putchar_fd('\0', 0);
		kill(pid_to_kill, SIGKILL);
		pid_to_kill = 0;
		write (1, "\n", 1);
	}
	else if (pid)
		pid_to_kill = pid;
}

void	ft_heredoc_sighandler(int signal)
{
	if (signal == CTRL_C)
	{
		ft_child_butcher(0);
	}
}

void	ft_heredoc_write(char *heredoc_path, const char *delimiter)
{
	int		heredoc_fd;
	char	*str;
	int		len;

	heredoc_fd = open(heredoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		return ;
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str || !*str)
			break ;
		if (!ft_strncmp(str, delimiter, len) && str[len] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, heredoc_fd);
		free(str);
	}
	close(heredoc_fd);
}

int	ft_heredoc(const char *delimiter, t_msh *msh)
{
	char	*heredoc_path;
	int		fd;
	int		pid;
	int		status;

	heredoc_path = "/tmp/.heredoc";
	unlink(heredoc_path);
	pid = fork();
	ft_child_butcher(pid);
	if (!pid)
	{
		ft_heredoc_write(heredoc_path, delimiter);
		ft_free_cmdlst(msh->cmd);
		ft_free_varslst(msh->vars);
		exit(1);
	}
	signal(CTRL_C, ft_heredoc_sighandler);
	waitpid(pid, &status, 0);
	if (!WEXITSTATUS(pid))
		return (-1);
	fd = open(heredoc_path, O_RDONLY);
	return (fd);
}

	/* if (WIFEXITED(status))
		WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		WTERMSIG(status);// + 128; */