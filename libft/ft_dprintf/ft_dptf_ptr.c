/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dptf_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:48:17 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:51:15 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

static void	ft_put_long_hex(int fd, long unsigned int n)
{
	if (n >= 16)
	{
		ft_put_long_hex(fd, n / 16);
		n = n % 16;
	}
	if (n >= 10)
		n = n - 10 + 'a';
	else
		n = n + '0';
	write(fd, &n, 1);
}

static int	ft_ptr_len(long unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 16)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static int	ft_ptr_symbol(int fd, t_ptf ptf, int x)
{
	int	len;

	len = 2;
	if (ft_flag_check(ptf.flags, PTF_SPACE))
	{
		len++;
		if (x == 0)
			write(fd, " ", 1);
	}
	if (ft_flag_check(ptf.flags, PTF_PLUS))
	{
		len++;
		if ((ft_flag_check(ptf.flags, PTF_ZERO) && x == 0) \
			|| (!ft_flag_check(ptf.flags, PTF_ZERO) && x == 1))
			write(fd, "+", 1);
	}
	if ((ft_flag_check(ptf.flags, PTF_ZERO) && x == 0) \
			|| (!ft_flag_check(ptf.flags, PTF_ZERO) && x == 1))
		write(fd, "0x", 2);
	return (len);
}

static int	ft_print_ptr_nil(int fd, t_ptf ptf)
{
	int	print_len;
	int	len;

	len = 5;
	print_len = len;
	ptf.pad_count = ft_n_of(len, ptf.pad_count);
	ptf.pad = ' ';
	if (!ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	write(fd, "(nil)", 5);
	if (ft_flag_check(ptf.flags, PTF_MINUS))
		print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	return (print_len);
}

int	ft_dprint_ptr(int fd, long unsigned int n, t_ptf ptf)
{
	int	print_len;
	int	len;

	if (!n)
		print_len = ft_print_ptr_nil(fd, ptf);
	else
	{
		len = ft_ptr_len(n);
		print_len = len;
		ptf.prec_count = ft_n_of(len, ptf.prec_count);
		ptf.pad_count = ft_n_of(len + ptf.prec_count, ptf.pad_count);
		ptf.pad_count -= ft_ptr_symbol(fd, ptf, 0);
		if (!ft_flag_check(ptf.flags, PTF_MINUS))
			print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
		print_len += ft_ptr_symbol(fd, ptf, 1);
		print_len += ft_dprint_special(fd, '0', ptf.prec_count);
		ft_put_long_hex(fd, n);
		if (ft_flag_check(ptf.flags, PTF_MINUS))
			print_len += ft_dprint_special(fd, ptf.pad, ptf.pad_count);
	}
	return (print_len);
}
