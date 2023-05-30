/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamici <lamici@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:03:19 by lamici            #+#    #+#             */
/*   Updated: 2023/05/24 09:43:08 by lamici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_go_back(char *my_pwd)
{
	int		x;
	int		z;
	char	*new_pwd;

	x = ft_strlen(my_pwd);
	while(my_pwd[x] != '/')
		x--;
	new_pwd = malloc(sizeof(char) * x + 1);
	z = 0;
	while(z < x)
	{
		new_pwd[z] = my_pwd[z];
		z++;
	}
	new_pwd[z] = '\0';
	free(my_pwd);
	return (new_pwd);
}

char	*ft_relative_cd(char *my_cd, char *str)
{
	char *temp;
	char *result;

	temp = ft_strjoin(my_cd, "/");
	result = ft_strjoin(temp, str);
	free(temp);
	free(my_cd);
	return(result);
}

int		ft_cd(char *str, char **my_env)
{
	int		x;
	char	*temp;
	char	**moves;
	int		i;

	i = 0;
	x = ft_get_env_addr(my_env, "PWD");
	if(!chdir(str))
	{
		if(str[0] == '/')
		{
			free(my_env[x]);
			temp = ft_strdup(str);
			my_env[x] = ft_strjoin("PWD=", temp);
			free(temp);
		}
		else
		{
			moves = ft_split(str, '/');
			while(moves[i])
			{
				if (moves[i][0] == '.' && moves[i][1] == '.')
					my_env[x] = ft_go_back(my_env[x]);
				else
					my_env[x] = ft_relative_cd(my_env[x], moves[i]);
				i++;
			}
		}
	}
	else
		perror("Error");
}