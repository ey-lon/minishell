/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dptf_flags_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:48:26 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 09:51:30 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int	ft_check_format(char format)
{
	char	*formats;
	int		i;

	formats = "cspdiuxX%";
	i = 0;
	while (formats[i])
	{
		if (format == formats[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_flag_check(int flags, int flag_to_find)
{
	if (flag_to_find && flags)
	{
		if ((flags & flag_to_find) == flag_to_find)
			return (1);
	}
	return (0);
}

int	ft_remove_flag(int flags, int flag_to_find)
{
	if (flag_to_find && flags)
	{
		if ((flags & flag_to_find) == flag_to_find)
			flags = flags ^ flag_to_find;
	}
	return (flags);
}

int	ft_dprint_special(int fd, int c, int count)
{
	int	len;

	len = 0;
	while (count-- > 0)
		len += write(fd, &c, 1);
	return (len);
}
