/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:11:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/05 05:02:14 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	refactor_com(t_params **para, char **com)
{
	t_params	*head;
	int			i;
	int			z;

	i = 0;
	z = 0;
	head = *para;
	while (head != NULL)
	{
		free(head->com);
		while (com[i] != NULL && com[i][0] != '|')
		{
			if (com[i][0] != '<' && com[i][0] != '>' )
	 			z++;
			i++;
		}
		head->com = (char **)malloc ((z + 1) * sizeof(char *));
		i = 0;
		z = 0;
		while (com[i] != NULL && com[i][0] != '|')
		{
			head->com[z] = ft_strdup(com[i]);
			if (com[i][0] != '<' && com[i][0] != '>')
			{
				head->com[z] = ft_strdup(com[i]);
		 		z++;
			}
			i++;
		}
		head->com[z] = NULL;
		head = head->next;
	}
}

void	init_com(t_params **para, char **com)
{
	t_params	*head;
	int			i;
	int			z;

	i = 0;
	z = 0;
	head = *para;
	while (com[i] != NULL && com[i][0] != '|')
	{
		// if (com[i][0] != '<' && com[i][0] != '>' )
	 	z++;
		i++;
	}
	head->com = (char **)malloc ((z + 1) * sizeof(char *));
	i = 0;
	z = 0;
	while (com[i] != NULL && com[i][0] != '|')
	{
		head->com[z] = ft_strdup(com[i]);
		// if (com[i][0] != '<' && com[i][0] != '>')
		// {
		// 	head->com[z] = ft_strdup(com[i]);
		 	z++;
		// }
		i++;
	}
	head->com[z] = NULL;
	set_output(para);
	set_input(para);
}

void	set_para(t_params **param, char *input, t_env **env)
{
	char		**inp_sep;
	t_params	*para;
	t_env		*v_env;
	int			i;

	para = *param;
	v_env = *env;
	inp_sep = ft_split(input, ' ');
	init_com(&para, inp_sep);
	set_var(&para, &v_env);
	para->next = NULL;
	i = 0;
	while (inp_sep[i] != NULL)
	{
		if (inp_sep[i][0] == '<')
		{
			if (inp_sep[i][1] == '\0')
				para->inp_red = entre1;
			else
				para->inp_red = entre2;
		}
		else if (inp_sep[i][0] == '>')
		{
			if (inp_sep[i][1] == '\0')
				para->out_red = sortie1;
			else
				para->out_red = sortie2;
		}
		else if (inp_sep[i][0] == '|')
		{
			para->nbcom = i;
			if_del(&para);
			para->next = (t_params *)malloc (sizeof(t_params));
			para = para->next;
			para->next = NULL;
			init_com(&para, inp_sep + i + 1);
		}
		i++;
	}
	para->nbcom = i;
	if_del(&para);
	refactor_com(&para, inp_sep);
	return ;
}
