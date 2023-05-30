/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamici <lamici@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:16:04 by lamici            #+#    #+#             */
/*   Updated: 2023/05/19 10:17:11 by lamici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_offset(char *str)
{
	int		x;
	int		offset;

	x = 0;
	offset = 0;
	while(str[x])
	{
		if(str[x] == '=' || str[x] == 34 || str[x] == 39)
			offset++;
		x++;
	}
	return(offset);
}

char	*ft_givename(int x, char *str)
{
	char	*name;
	int		i;

	i = 0;
	name = malloc(sizeof(char) * x + 1);
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[x] = '\0';
	return (name);
}

char	*ft_givecontent(int x, char *str)
{
	char	*content;
	int		i;
	int		z;

	i = 0;
	z = 0;
	content = malloc(sizeof(char) * x + 1);
	while (str[i] != '=')
		i++;
	i++;
	if(str[i] == 34 || str[i] == 39)
		i++;
	while(str[i] != '\0' && (str[i] != 34 || str[i] != 39))
	{
		content[z] = str[i];
		z++;
		i++;
	}
	content[x] = '\0';
	return (content);
}

t_list	*ft_var_creation(char *var)
{
	int			x;
	int			z;
	t_list		*vars;

	x = 0;
	vars = malloc(sizeof(t_list));
	while(var[x] != '=')
		x++;
	z = x + 1;
	while(var[z])
		z++;
	vars->content = ft_givecontent((z - x - ft_offset(var)), var);
	vars->name = ft_givename(x, var);
	vars->next = NULL;
	vars->exp_check = 0;
	return(vars);
}

t_list	*ft_find_var(t_list *vars, char *str)
{
	t_list	*temp;

	temp = vars;
	while(strcmp(temp->name ,str))
		temp = temp->next;
}