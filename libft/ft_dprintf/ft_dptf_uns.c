/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dptf_uns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:48:17 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:57:48 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

static void	ft_put_uns(int fd, unsigned int n)
{
	if (n >= 10)
	{
		ft_put_uns(fd, n / 10);
		n = n % 10;
	}
	n = n + '0';
	write(fd, &n, 1);
}

static int	ft_uns_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_dprint_uns(int fd, unsigned int n, t_ptf ptf)
{
	int	print_len;
	int	len;

	if (n == 0 && ft_flag_check(ptf.flags, PTF_PREC) && ptf.prec_count < 1)
		len = 0;
	else
		len = ft_uns_len(n);
	print_len = len;
	ptf.prec_count = ft_n_of(len, ptf.prec_count);
	ptf.pad_count = ft_n_of(len + ptf.prec_count, ptf.pad_count);
	if (!ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	print_len += ft_dprint_special(fd, '0', ptf.prec_count);
	if (len)
		ft_put_uns(fd, n);
	if (ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	return (print_len);
}
