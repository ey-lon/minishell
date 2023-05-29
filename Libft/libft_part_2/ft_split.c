/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:29:50 by abettini          #+#    #+#             */
/*   Updated: 2023/05/26 10:38:47 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_strlenmod(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**mat;
	int		count;
	int		i;
	int		j;

	count = ft_str_count(s, c);
	mat = malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (j < count)
	{
		if (s[i] != c)
		{
			mat[j] = ft_substr(&s[i], 0, ft_strlenmod(&s[i], c));
			i = i + ft_strlenmod(&s[i], c);
			j++;
		}
		else
			i++;
	}
	mat[j] = NULL;
	return (mat);
}

/*
int	main()
{
	char	**arr;
	int j = 0;
	char str[] = "111ciao,111come1va?11111";
	char c = '1';
	arr = ft_split(str, c);
	while (arr[j] != 0)
	{
		printf("%s\n", arr[j]);
		j++;
	}
	return (0);
}
*/
