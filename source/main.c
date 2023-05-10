/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:46:44 by abettini          #+#    #+#             */
/*   Updated: 2023/05/10 16:53:41 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	t_list	*hst;

	hst = NULL;
	while (1)
	{
		ft_putstr_fd("$>", 1);
		str = readline(0);
		ft_add_str_to_history(str, &hst);
		free(str);
	}
	return (0);
}