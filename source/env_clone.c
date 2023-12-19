/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:14:37 by abettini          #+#    #+#             */
/*   Updated: 2023/12/19 16:52:04 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//------------------------------------------------------------------------------
//turn env from matrix to list

t_list	*ft_env_from_matrix_to_list(char **env)
{
	int		i;
	int		len;
	t_var	*new;
	t_list	*vars;

	vars = NULL;
	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(t_var));
		len = ft_strlen_mod(env[i], '=');
		new->name = ft_substr(env[i], 0, len);
		new->value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - len);
		new->exp = 1;
		ft_lstadd_back(&vars, ft_lstnew((void *)new));
		i++;
	}
	return (vars);
}

//------------------------------------------------------------------------------
//turn env from list to matrix

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
	char	*tmp;
	char	*line;

	line = ft_strjoin(var->name, "=");
	tmp = line;
	line = ft_strjoin(tmp, var->value);
	free(tmp);
	return (line);
}

char	**ft_env_from_list_to_matrix(t_list **vars)
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
