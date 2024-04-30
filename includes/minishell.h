/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 17:04:38 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

/* Constante */

/* Error messages */

// MINISHELL

// SYNTAX

// EXIT CMD

// CD CMD

typedef enum e_operator {
	none,
	entre1,
	entre2,
	sortie1,
	sortie2,
}		t_operator;

typedef struct s_put {
	char	*input;
	char	*output;
}	t_put;

typedef struct s_params {
	char			**com;
	t_operator		inp_red;
	t_operator		out_red;
	struct s_params	*next;
}			t_params;

typedef struct s_env {
	char			*env_name;
	char			*env_value;
	bool			is_exported;
	struct s_env	*next;
}			t_env;

//cmd
int		cmd_echo(t_params *para);
int		cmd_pwd(void);
int		cmd_cd(t_params *para, t_env **env);

//parsing
int		set_para(t_params **param, char *input, t_env **env, t_put **put);
void	set_put(t_put **put, t_params **para);
char	*heredoc(char *exit);
void	ft_doc(t_params **para);
void	set_var(t_params **para, t_env **env);
void	set_enum(t_params **para);
char	**set_cote(char **input);
char	**split_para(char *input);
int		error_quote(char *str);
int		count_quote(char *str, int *i);
int		count_red(char *str, int *i);
int		red_len(char *str, int *i);
int		quote_len(char *str, int *i);
int		ft_error(char **input);
void	print_error(int error);

//exec
void	ft_exec(t_params **para, char **env);
void	commande(t_params **para, t_env **env, char **envv);

//utils
char	*clean_input(char *raw_input);
t_env	*set_env(char **env);
void	print_all(t_params **para, t_env **env, t_put **put);
void	print_com(t_params **para);
char	*recherche_env(char *str, t_env **env);
int		strchr1x(char *input, char c);
int		ft_strchr2x(char **str, char c, int i);
char	*ft_strjoin_sp(char const *s1, char *s2);
char	**split_var(char *str);
int		count_wd_var(char *str);
char	*clean_var(char *var);
void	free_all(t_params **para, t_put **put);

#endif
