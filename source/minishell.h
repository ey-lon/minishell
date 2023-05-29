/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:47:15 by abettini          #+#    #+#             */
/*   Updated: 2023/05/29 16:35:02 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>

# define CTRL_C SIGINT
# define CTRL_D SIGSEGV
# define CTRL_BS SIGQUIT

# define SPACES "\t\n\v\f\r "

typedef struct s_prs
{
	char	**wrd;
	char	**red;
}	t_prs;

typedef struct s_var
{
	char	*str;
	bool	exp;
}	t_var;

//cmd_err_check-----------------------------------------------------------------
int		ft_check_cmd_err(char *str);

//PARSING-----------------------------------------------------------------------
void	ft_parsing(t_list **lst, char *str, char **env, t_list **vars);
//words & redirects (count & lenght)
int		ft_red_count(char *str);
int		ft_wrd_count(char *str);
int		ft_red_len(char *str);
int		ft_wrd_len(char *str);
int		ft_char_char_len(char *str, char c);
//------------------------------------------------------------------------------
void	ft_check_expand(t_list **lst, char **env, t_list **vars);
char	*ft_find_var(char *var_name, char **env, t_list **vars);
int		ft_quotes_vars_len(char *str, char **env, t_list **vars);
void	ft_quotes_vars_cpy(char *line, char *str, char **env, t_list **vars);

//history-----------------------------------------------------------------------
int		ft_add_str_to_history(char *str, t_list **hst);
int		ft_print_history(t_list *hst);
//utils-------------------------------------------------------------------------
int		ft_is_special(char c);
int		ft_isspace(char c);
void	ft_free_mat(char **mat);
//utils_2-----------------------------------------------------------------------
char	*ft_rm_chars(char *str, char *rm, int len);
int		ft_count_chars(char *str, char *c, int n);

//PRINT-------------------------------------------------------------------------
void	ft_print_lst(t_list *lst);
#endif