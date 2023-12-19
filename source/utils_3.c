/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:11:17 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 17:13:17 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_exit_code(int status)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status) + 128;
	return (ret);
}

void	ft_close_fds(int fd_1, int fd_2)
{
	if (fd_1 > -1)
		close(fd_1);
	if (fd_2 > -1)
		close (fd_2);
}
