/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:06:23 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:54:01 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int	ft_conv_fd(int fd, va_list ap, t_ptf ptf)
{
	int	print_len;

	print_len = 0;
	if (ptf.format == 'c')
		print_len = ft_dprint_chr(fd, va_arg(ap, int), ptf);
	else if (ptf.format == 's')
		print_len = ft_dprint_str(fd, va_arg(ap, char *), ptf);
	else if (ptf.format == 'p')
		print_len = ft_dprint_ptr(fd, va_arg(ap, long unsigned int), ptf);
	else if (ptf.format == 'd' || ptf.format == 'i')
		print_len = ft_dprint_dec(fd, va_arg(ap, int), ptf);
	else if (ptf.format == 'u')
		print_len = ft_dprint_uns(fd, va_arg(ap, unsigned int), ptf);
	else if (ptf.format == 'x' || ptf.format == 'X')
		print_len = ft_dprint_hex(fd, va_arg(ap, unsigned int), ptf);
	else if (ptf.format == '%')
		print_len = write(fd, "%", 1);
	else
		print_len = ft_dprint_unknown(fd, ptf);
	return (print_len);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	int		print_len;
	va_list	ap;

	if (str)
	{
		print_len = 0;
		va_start(ap, str);
		i = 0;
		while (str[i])
		{
			if (str[i] == '%')
				print_len += ft_flags(fd, ap, str, &i);
			else
				print_len += write(fd, &str[i], 1);
			i++;
		}
		va_end(ap);
	}
	else
		print_len = -1;
	return (print_len);
}
