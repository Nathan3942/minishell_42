/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/03 06:19:03 by njeanbou         ###   ########.fr       */
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

/* Constante */

/* Error messages */

// MINISHELL

// SYNTAX

// EXIT CMD

// CD CMD

/*sert a determiner comment les commandes doivent etre traiter
lors de l'analyse et l'execution*/
// typedef struct s_data {
// 	char    *com1;
// 	char    *com2;
// 	char    *red1;
// 	char    *red2;
// 	char    *input;
// 	char    *output;
// 	bool    has_n;
// }           t_params;

typedef enum e_operator {
	none,
	entre1,
	entre2,
	sortie1,
	sortie2,
}		t_operator;

typedef struct s_params {
	char	**com;
	int		nbcom;
	char	*input;
	char	*output;
	t_operator	inp_red;
	t_operator	out_red;
	struct s_params *next;
}           t_params;

typedef struct s_env {
	char	*env_name;
	char	*env_value;
	struct s_env *next;
}			t_env;

//cmd
int		cmd_echo(t_params *para);
int		cmd_pwd(void);

//parsing
void	set_para(t_params **param, char *input);
void	set_output(t_params **para);

//utils
char    *clean_input(char *raw_input);
t_env	*set_env(char **env);
void	print_all(t_params **para, t_env **env);

#endif
