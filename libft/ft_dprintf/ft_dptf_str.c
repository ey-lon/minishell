/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dptf_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:27:10 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:56:34 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

static void	ft_put_str(int fd, char *str, int len)
{
	int	i;

	if (!str && len >= 6)
		write(fd, "(null)", 6);
	else if (str)
	{
		i = 0;
		while (str[i] && len--)
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

static int	ft_str_len(char *str, t_ptf ptf)
{
	int	len;

	len = 0;
	if (!ft_flag_check(ptf.flags, PTF_PREC))
	{
		if (!str)
			len = 6;
		else
		{
			while (str[len])
				len++;
		}
	}
	else
	{
		if (!str && ptf.prec_count >= 6)
			len = 6;
		else if (str)
		{
			while (str[len] && ptf.prec_count--)
				len++;
		}
	}
	return (len);
}

int	ft_dprint_str(int fd, char *str, t_ptf ptf)
{
	int	print_len;
	int	len;

	len = ft_str_len(str, ptf);
	print_len = len;
	ptf.pad_count = ft_n_of(len, ptf.pad_count);
	if (!ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	ft_put_str(fd, str, len);
	if (ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	return (print_len);
}
