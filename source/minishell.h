/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:47:15 by abettini          #+#    #+#             */
/*   Updated: 2023/07/10 10:12:28 by abettini         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>

# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT

# define HEREDOC_PATH ".heredoc"

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

typedef struct s_msh
{
	t_list	**vars;
	t_list	**cmd;
	int		fd[2];
	int		std[2];
	bool	exit;
}	t_msh;

//PRINT-------------------------------------------------------------------------
void	ft_print_lst(t_list *lst);

//cmd_err_check-----------------------------------------------------------------
int		ft_check_cmd_err(char *str);

//PARSING-----------------------------------------------------------------------
void	ft_parsing(char *str, t_msh *msh);
//words & redirects (count & lenght)
int		ft_red_count(char *str);
int		ft_wrd_count(char *str);
int		ft_red_len(char *str);
int		ft_wrd_len(char *str);
int		ft_char_char_len(char *str, char c);
//expand_vars-------------------------------------------------------------------
void	ft_check_expand(t_msh *msh);
char	*ft_get_var_cont(char *var_name, t_list **vars);
int		ft_quotes_vars_len(char *str, t_msh *msh);
void	ft_quotes_vars_cpy(char *line, char *str, t_msh *msh);

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
int		ft_llong_limit_check(char *str);

//variables---------------------------------------------------------------------
int		ft_variable_cmd(t_list **vars, char *str);
t_list	*ft_find_var(t_list **vars, char *var_name);
void	ft_handle_var(t_list **vars, char *str);
void	ft_add_var(t_list **vars, char *str, int exp);
void	ft_mod_var_value(t_list *vars, char *str);

//clone_env-(env_list)----------------------------------------------------------
void	ft_clone_env(t_list **vars, char **env);
//env_matrix--------------------------------------------------------------------
char	**ft_env_matrix(t_list **vars);
//pwd_check---------------------------------------------------------------------
void	ft_update_pwd(t_list **vars);
void	ft_update_oldpwd(t_list **vars, char *str);

//build-ins---------------------------------------------------------------------
void	ft_pwd(void);
void	ft_env(t_list **vars);
void	ft_echo(char **args);
int		ft_cd(t_list **vars, char **args);
int		ft_export(t_list **vars, char **args);
int		ft_unset(t_list **vars, char **args);
int		ft_exit(t_msh *msh, char **args);

//execution---------------------------------------------------------------------
int		ft_pipes(t_list **cmd, t_msh *msh);
int		ft_redirects(t_list *cmd, t_msh *msh);
int		ft_execution(char **wrd, t_msh *msh);
int		ft_try_path(char **cmd_f, t_msh *msh);
int		ft_execute_cmd(char *cmd_path, char **cmd_f, t_msh *msh);

//redirects
void	ft_choose_redir(t_msh *msh, int fd_in, int fd_out);
void	ft_reset_redir(t_msh *msh);
int		ft_heredoc(const char *delimiter, t_msh *msh);

//free_stuff--------------------------------------------------------------------
void	ft_free_varslst(t_list **lst);
void	ft_free_varsnode(t_list *vars);
void	ft_free_cmdlst(t_list **lst);

#endif