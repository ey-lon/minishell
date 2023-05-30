/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamici <lamici@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:57:56 by lamici            #+#    #+#             */
/*   Updated: 2023/05/19 09:16:17 by lamici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_new_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT);
	return (fd);
}

char	*ft_name_from_path(char *path)
{
	char *temp;
	int		x;
	int		z;

	x = 0;
	z = 0;
	while(path[x] != '\0')
		x++;
	z = x;
	while(path[x - 1] != '/' || x != 0)
		x--;
	temp = malloc(sizeof(char) * ((z - x) + 1));
	z = 0;
	while(path[x])
	{
		temp[z] = path[x];
		x++;
		z++;
	}
	temp[x] = '\0';
	return (temp);
}