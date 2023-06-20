/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:47:15 by abettini          #+#    #+#             */
/*   Updated: 2023/06/20 11:25:16 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	char	*name;
	char	*value;
	int		exp;
}	t_var;

//cmd_err_check-----------------------------------------------------------------
int		ft_check_cmd_err(char *str);

//PARSING-----------------------------------------------------------------------
void	ft_parsing(t_list **lst, char *str, t_list **vars);
//words & redirects (count & lenght)
int		ft_red_count(char *str);
int		ft_wrd_count(char *str);
int		ft_red_len(char *str);
int		ft_wrd_len(char *str);
int		ft_char_char_len(char *str, char c);
//expand_vars-------------------------------------------------------------------
void	ft_check_expand(t_list **lst, t_list **vars);
char	*ft_get_var_cont(char *var_name, t_list **vars);
int		ft_quotes_vars_len(char *str, t_list **vars);
void	ft_quotes_vars_cpy(char *line, char *str, t_list **vars);

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
int		ft_strlen_mod(char *str, char end);

//PRINT-------------------------------------------------------------------------
void	ft_print_lst(t_list *lst);

//variables---------------------------------------------------------------------
t_list	*ft_find_var(t_list **vars, char *var_name);
void	ft_handle_var(t_list **vars, char *str);
void	ft_add_var(t_list **vars, char *str, int exp);
void	ft_mod_var_value(t_list *vars, char *str);

//clone_env-(env_list)----------------------------------------------------------
void	ft_clone_env(t_list **vars, char **env);
//env_matrix--------------------------------------------------------------------
char	**ft_env_matrix(t_list **vars);
//pwd_check---------------------------------------------------------------------
void	ft_check_pwd(t_list **vars);
int		ft_update_oldpwd(t_list **vars);

//build-ins---------------------------------------------------------------------
void	ft_env(t_list **vars);
int		ft_pwd(t_list **vars);
int		ft_cd(t_list **vars, char **args);
char	*ft_cd_relative(char *old_pwd, char *str);
void	ft_export(t_list **vars, char **args);
void	ft_unset(t_list **vars, char **args);
void	ft_echo(char **args);
void	ft_exit(t_list **vars);

//execution---------------------------------------------------------------------
int		ft_pipes(t_list **cmd, t_list **vars, int fd_out);
int		ft_redirects(t_list *cmd);
int		ft_execution(char **wrd, t_list **vars);

//free_stuff--------------------------------------------------------------------
void	ft_free_varslst(t_list **lst);
void	ft_free_varsnode(t_list *vars);
void	ft_free_cmdlst(t_list **lst);

#endif