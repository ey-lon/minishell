/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamici <lamici@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:08:10 by lamici            #+#    #+#             */
/*   Updated: 2023/05/24 10:38:15 by lamici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nothing(int signal)
{
	if (signal)
		;
}

void	ft_newprompt(int signal)
{
	write(1, "\n", 1);
}

void	ft_sighandler(void)
{
	signal(SIGINT, ft_newprompt);
	signal(SIGQUIT, ft_nothing);
}

void	print_ancestor(void)
{
	char *str;
	int		x;

	x = open("/nfs/homes/lamici/esercizi corso/42cursus/ring_03/minishell/ancestor.txt", O_RDONLY);
	str = get_next_line(x);
	while(str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(x);
	}
}

void	print_abettini(void)
{
	char *str;
	int		x;

	x = open("/nfs/homes/lamici/esercizi corso/42cursus/ring_03/minishell/abettini.txt", O_RDONLY);
	str = get_next_line(x);
	while(str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(x);
	}
}