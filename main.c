/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/12 05:26:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char *get_input(void)
{
	char    *raw_input;
	char    *input;

	raw_input = readline("minishell: ");
	input = clean_input(raw_input);
	return (input);
}

int main(int argc, char **argv, char **env)
{
	t_params    *para;
	t_env       *lstenv;
	t_put       *put;
	char        *input;

	if (argc > 1 && argv[1] == NULL)
		exit(EXIT_FAILURE);
	lstenv = set_env(env);
	while (1)
	{
		para = (t_params *)malloc (sizeof(t_params));
		put = (t_put *) malloc (sizeof(t_put));
		put->input = NULL;
		put->output = NULL;
		input = get_input();
		if (input == NULL)
			break ;
		add_history(input);
		set_para(&para, input, &lstenv, &put);
		print_all(&para, &lstenv, &put);
		ft_exec(&para, env);
		free(para);
	}
	return (0);
}

