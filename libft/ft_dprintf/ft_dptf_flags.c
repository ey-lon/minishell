/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dptf_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:09:56 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:51:24 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

void	ft_flags_init(t_ptf *ptf)
{
	ptf->flags = PTF_NOFLAGS;
	ptf->format = 0;
	ptf->prec_count = 0;
	ptf->pad_count = 0;
	ptf->pad = ' ';
}

void	ft_flags_update(va_list ap, t_ptf *ptf)
{
	if (ft_flag_check(ptf->flags, PTF_WIDTH))
	{
		ptf->pad_count = va_arg(ap, int);
		if (ptf->pad_count < 0)
		{
			ptf->pad_count = -ptf->pad_count;
			ptf->flags |= PTF_MINUS;
		}
	}
	if (ft_flag_check(ptf->flags, PTF_PLUS))
		ptf->flags = ft_remove_flag(ptf->flags, PTF_SPACE);
	if ((ft_flag_check(ptf->flags, PTF_PREC) \
		|| ft_flag_check(ptf->flags, PTF_MINUS) \
		|| ptf->format == 's' || ptf->format == 'c') \
		&& ft_check_format(ptf->format))
		ptf->flags = ft_remove_flag(ptf->flags, PTF_ZERO);
	if (ft_flag_check(ptf->flags, PTF_ZERO))
		ptf->pad = '0';
}

int	ft_flags(int fd, va_list ap, const char *s, int *i)
{
	int		print_len;
	t_ptf	ptf;

	*i += 1;
	ft_flags_init(&ptf);
	ft_set_flags(&ptf, s, i);
	ft_flags_update(ap, &ptf);
	print_len = ft_conv_fd(fd, ap, ptf);
	return (print_len);
}
