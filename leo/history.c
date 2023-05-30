/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamici <lamici@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:44:10 by lamici            #+#    #+#             */
/*   Updated: 2023/05/10 15:52:35 by lamici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_history(char **hst)
{
	int		i;

	i = 0;
	while(hst[i])
	{
		printf("%5d %s\n", i + 1, hst[i]);
		i++;
	}
}

char	**ft_get_hst(char *str, int	type)
{
	static char *hst[4000];
	static int	i;

	if(!i)
		hst[i] = 0;
	if(type)
	{
		if(hst[i] == 0)
		{
			hst[i] = ft_strdup(str);
			i++;
			hst[i] = NULL;
		}
		return(hst);
	}
	else
		return(hst);
}