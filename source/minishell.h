/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:47:15 by abettini          #+#    #+#             */
/*   Updated: 2023/05/10 16:04:28 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//history-----------------------------------------------------------------------
int	ft_add_str_to_history(char *str, t_list **hst);
int	ft_print_history(t_list *hst);

#endif