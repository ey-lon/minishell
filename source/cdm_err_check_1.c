/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdm_err_check_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:10:50 by abettini          #+#    #+#             */
/*   Updated: 2023/07/03 18:12:26 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_max_consec_char(char *str, char c);

int	ft_check_weird_1(char *str);

int	ft_check_weird_2(char *str, char c);

int	ft_check_weird_3(char *str, char c);

int	ft_syntax(char *str)
{
	if (ft_max_consec_char(str, '|') > 1)
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `|'\n") * 0 + 1);
	if (ft_max_consec_char(str, '>') > 2)
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `>>'\n") * 0 + 1);
	if (ft_max_consec_char(str, '<') > 2)
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `<<'\n") * 0 + 1);
	if (ft_check_weird_1(str))
		return (ft_dprintf(2, "minishell: \
			syntax error\n") * 0 + 1);
	if (ft_check_weird_2(str, '|'))
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `|'\n") * 0 + 1);
	if (ft_check_weird_3(str, '>'))
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `>'\n") * 0 + 1);
	if (ft_check_weird_3(str, '<'))
		return (ft_dprintf(2, "minishell: \
			syntax error near unexpected token `<'\n") * 0 + 1);
	return (0);
}

int	ft_stat_update(int stat, char c)
{
	if (stat != 1 && c == '\"')
		stat = 2 - stat;
	else if (stat != 2 && c == '\'')
		stat = 1 - stat;
	return (stat);
}

int	ft_check_cmd_err(char *str)
{
	int	i;
	int	stat;

	stat = 0;
	i = 0;
	while (str[i])
	{
		stat = ft_stat_update(stat, str[i]);
		if (!stat && (str[i] == '\'' || str[i] == '\"'))
			i++;
		if (!stat)
		{
			if (ft_syntax(&str[i]))
				return (1);
			else
			{
				while (!stat && str[i])
					stat = ft_stat_update(stat, str[i++]);
			}
		}
		else
			i++;
	}
	return (0);
}
