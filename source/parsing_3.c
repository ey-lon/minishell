/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:01:18 by abettini          #+#    #+#             */
/*   Updated: 2023/05/29 11:33:52 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_var_len(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]))
	{
		i++;
		while (ft_isalnum(str[i]))
			i++;
	}
	return (i);
}

//FIND_VAR-----------------------------------------------------------------------
//cerca variabile:
// - nell'env, oppure
// - nella lista di vars
//restituisce:
// - stringa dopo l'uguale (=), oppure
// - "\0" se non la trova

char	*ft_find_var(char *var_name, char **env, t_list **vars)
{
	t_list	*tmp;
	int		len;
	int		i;

	len = ft_strlen(var_name);
	i = 0;
	while (env[i] && !(!ft_strncmp(var_name, env[i], len) && env[i][len] == '='))
		i++;
	if (env[i])
		return (env[i] + len + 1);
	tmp = *vars;
	while (tmp && !(!ft_strncmp(var_name, ((t_var *)tmp->content)->str, len) \
		&& ((t_var *)tmp->content)->str[len] == '='))
		tmp = tmp->next;
	if (tmp)
		return (((t_var *)tmp->content)->str + len + 1);
	return ("\0");
}
//-------------------------------------------------------------------------------

int		ft_quotes_vars_len(char *str, char **env, t_list **vars)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else if (str[i] == '\'')
		{
			len += ft_char_char_len(&str[i], '\'') - 2;
			i += ft_char_char_len(&str[i], '\'');
		}
		else if (str[i] == '$')
		{
			var_name = ft_substr(&str[i + 1], 0, ft_var_len(&str[i + 1]));
			len += ft_strlen(ft_find_var(var_name, env, vars));
			free(var_name);
			i += 1 + ft_var_len(&str[i + 1]);
		}
		else if (++i)
			len++;
	}
	return (len);
}

void	ft_quotes_vars_cpy(char *line, char *str, char **env, t_list **vars)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				line[len++] = str[i++];
			if (str[i])
				i++;
		}
		else if (str[i] == '$')
		{
			var_name = ft_substr(&str[i + 1], 0, ft_var_len(&str[i + 1]));
			ft_strlcpy(&line[len], ft_find_var(var_name, env, vars), \
				ft_strlen(ft_find_var(var_name, env, vars)) + 1);
			len += ft_strlen(ft_find_var(var_name, env, vars));
			free(var_name);
			i += 1 + ft_var_len(&str[i + 1]);
		}
		else
			line[len++] = str[i++];
	}
	line[len] = '\0';
}

char	*ft_quotes_vars(char *str, char **env, t_list **vars)
{
	//calcola lenght
	//allocare
	//copiare

	int		len;
	char	*line;

	len = ft_quotes_vars_len(str, env, vars);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	ft_quotes_vars_cpy(line, str, env, vars);
	free(str);
	return (line);
}

void	ft_check_expand(t_list **lst, char **env, t_list **vars)
{
	t_prs	*tmp;
	t_list	*scr;
	int		y;

	scr = *lst;
	while (scr)
	{
		tmp = (t_prs *)scr->content;
		y = 0;
		while (tmp->wrd[y])
		{
			tmp->wrd[y] = ft_quotes_vars(tmp->wrd[y], env, vars);
			y++;
		}
		y = 0;
		while (tmp->red[y])
		{
			tmp->red[y] = ft_quotes_vars(tmp->red[y], env, vars);
			y++;
		}
		scr = scr->next;
	}
}
