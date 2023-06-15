/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:07:27 by abettini          #+#    #+#             */
/*   Updated: 2023/06/14 16:54:50 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list **vars)
{
	t_list	*tmp;

	tmp = *vars;
	while (tmp)
	{
		if (((t_var *)tmp->content)->exp == 1)
			printf("%s=%s\n", ((t_var *)tmp->content)->name, \
				((t_var *)tmp->content)->value);
		tmp = tmp->next;
	}
}

//------------------------------------------------------------------------------
static int	ft_count_exp(t_list **vars)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *vars;
	while (tmp)
	{
		if (((t_var *)(tmp->content))->exp == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	*ft_env_line(t_var *var)
{
	char 	*tmp;
	char	*line;

	line = ft_strjoin(var->name, "=");
	tmp = line;
	line = ft_strjoin(tmp, var->value);
	free(tmp);
	return (line);
}

char	**ft_env_matrix(t_list **vars)
{
	int		i;
	int		count;
	char	**env;
	t_list	*tmp;

	count = ft_count_exp(vars);
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	env[count] = NULL;
	tmp = *vars;
	i = 0;
	while (i < count)
	{
		if (((t_var *)(tmp->content))->exp == 1)
		{
			env[i] = ft_env_line((t_var *)(tmp->content));
			i++;
		}
		tmp = tmp->next;
	}
	return (env);
}
