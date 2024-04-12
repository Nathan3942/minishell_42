/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:11:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/12 05:58:24 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_com(t_params **para)
{
	t_params	*head;
	int			i;
	int			z;

	head = *para;
	i = 0;
	z = 0;
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] != '<' && head->com[i][0] != '>')
		{
			if (i == 0)
				break ;
			if (head->com[i - 1][0] != '<' && head->com[i - 1][0] != '>')
		 		z++;
			if (head->com[i - 1][0] == '<' && head->com[i - 1][1] != '<')
				z++;
		}
		i++;
	}
	return (z);
}

char	**set_com(t_params **para)
{
	t_params	*head;
	char		**com;
	int			i;
	int			z;

	head = *para;
	i = 1;
	z = 1;
	if (head->com[0][0] != '<' && head->com[0][0] != '>')
			com[0] = ft_strdup(head->com[0]);
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] != '<' && head->com[i][0] != '>')
		{
			if (head->com[i - 1][0] != '>' && head->com[i - 1][0] != '<')
			{
				com[z] = ft_strdup(head->com[i]);
		 		z++;
			}
			if (head->com[i - 1][0] == '<' && head->com[i - 1][1] == '<')
			{
				com[z++] = ft_strdup(head->com[i]);
				z++;
			}
		}
		i++;
	}
	com[z] = NULL;
	return (com);
}

void	refactor_com(t_params **para, char **input)
{
	t_params	*head;
	char		**com;
	int			z;

	z = 0;
	head = *para;
	while (head != NULL)
	{
		z = count_com(para);
		com = (char **)malloc ((z + 1) * sizeof(char *));
		com = set_com(para);
		head->com = com;
		head = head->next;
		*para = head;
	}
}

void	init_com(t_params **para, char **com, t_put **put, t_env **env)
{
	t_params	*head;
	int			i;
	int			z;

	i = 0;
	z = 0;
	head = *para;
	while (com[i] != NULL && com[i][0] != '|')
	{
	 	z++;
		i++;
	}
	head->com = (char **)malloc ((z + 1) * sizeof(char *));
	i = 0;
	z = 0;
	while (com[i] != NULL && com[i][0] != '|')
	{
		head->com[z] = ft_strdup(com[i]);
		 	z++;
		i++;
	}
	head->com[z] = NULL;
	set_put(put, para);
	set_var(para, env);
	set_enum(para);
	//
	print_com(para);
}

void	set_para(t_params **param, char *input, t_env **env, t_put **put)
{
	char		**inp_sep;
	t_params	*para;
	int			i;

	para = *param;
	inp_sep = ft_split(input, ' ');
	init_com(&para, inp_sep, put, env);
	para->next = NULL;
	i = 0;
	while (inp_sep[i] != NULL)
	{
		if (inp_sep[i][0] == '|')
		{
			ft_doc(&para);
			para->next = (t_params *)malloc (sizeof(t_params));
			para = para->next;
			para->next = NULL;
			init_com(&para, inp_sep + i + 1, put, env);
		}
		i++;
	}
	ft_doc(&para);
	refactor_com(&para, inp_sep);
	return ;
}
