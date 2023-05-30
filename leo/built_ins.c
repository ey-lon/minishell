/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:05:25 by lamici            #+#    #+#             */
/*   Updated: 2023/05/30 17:35:56 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(int flag, int fd, char *str)
{
	while(*str)
		write(fd, str++, 1);
	if (!flag)
		write(1, "\n", 1);
}

int		ft_pwd(char **my_env, int fd)
{
	int		x;
	char 	*path;

	x = 0;
	while(my_env[x])
	{
		if(!ft_strncmp(my_env[x], "PWD=", 4))
		{
			path = my_env[x];
			ft_putstr_fd(my_env[x] + 4, fd);
			write(fd, "\n", 1);
			break;
		}
		x++;
	}
}

int		ft_env(char **my_env, int fd)
{
	int		y;

	y = 0;
	while(my_env[y])
	{
		ft_putstr_fd(my_env[y], fd);
		write(fd, "\n", 1);
		y++;
	}
	return(0);
}

void	ft_free_list(t_list *vars)
{
	t_list	*temp;

	temp = vars;
	while(vars)
	{
		free(vars->content);
		free(vars->name);
		vars = temp->next;
		free(temp);
		temp = vars;
	}
}

int		ft_exit(t_list *vars, char *str)
{
	ft_free_list(vars);
	free(str);
	exit(0);
}

char 	**ft_export(char **my_env, t_list *vars, char *name)
{
	char *var;
	t_list	*temp;
	char **new_env;

	temp = vars;
	while(ft_strncmp(name, temp->name, ft_strlen(name)) && temp)
		temp = temp->next;
	if(temp)
	{
		name = ft_strjoin(name, "=");
		var = ft_strjoin(name, temp->content);
		new_env = ft_dup_env(my_env, 1, var); 
		free(var);
		return(new_env);
	}
	else
		return(my_env);
}

/*
int		ft_cat(char *path, t_fds fds)
{
	char *str;

	str = get_next_line(fds.rfd);
	while (str)
	{
		write(fds.wfd, &str, 1);
		str++;
	}
	free(str);
}*/