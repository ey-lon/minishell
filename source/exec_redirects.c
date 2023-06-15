/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:02:20 by abettini          #+#    #+#             */
/*   Updated: 2023/06/15 09:47:55 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
void	ft_heredoc()
 */

int ft_in_open_err()
{
    perror("No such file or directory");
    return (1);
}

int ft_error_open()
{
    perror("open error");
    return (1);
}

int ft_redirects(char *str)
{   
    int fd;

    if (ft_strncmp(str, "<<", 2) == 0)
    {
        ; //HEREDOC
    }
    else if (ft_strncmp(str, ">>", 2) == 0)
    {
        fd = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1)
            return (ft_error_open());
        dup2(fd, STDOUT_FILENO);
    }
    else if (ft_strncmp(str, ">", 1) == 0)
    {
        fd = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
            return (ft_error_open());
        dup2(fd, STDOUT_FILENO);
    }
    else if (ft_strncmp(str, "<", 1) == 0)
    {
        fd = open(str + 1, O_CREAT | O_RDONLY);
        if (fd == -1)
            return (ft_in_open_err());
        dup2(fd, STDIN_FILENO);
    }
    close(fd);
	return (0);
}