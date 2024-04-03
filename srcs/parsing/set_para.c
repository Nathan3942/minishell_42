/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_para.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:11:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/03 06:29:04 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc(char *exit)
{
    char    *doctmp;
	char	*doc;
	//char	*tmp;
	
    doctmp = NULL;
    while (1)
	{
		doc = readline("heredoc> ");
        if (ft_strstr(doc, exit) == doc && ft_strlen(doc) == ft_strlen(exit))
            break ;
        doctmp = ft_strjoin(doctmp, doc);
	}
	return (doctmp);
}

void	if_del(t_params **para)
{
	t_params	*head;
	char		*tmp;
	int			i;
	char		*exit;

	i = 0;
	head = *para;
    exit = NULL;
	if (head->inp_red == entre2)
	{	
		while (head->com[i] != NULL)
		{
			if (head->com[i][0] == '<')
				exit = head->com[i + 1];
			i++;
		}
		tmp = heredoc(exit);
		if (tmp != NULL)
			head->com[--i] = tmp;
		else
			head->com[--i] = NULL;
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
}

void	set_para(t_params **param, char *input)
{
	char		**inp_sep;
	t_params	*para;
	int			i;

	para = *param;
	inp_sep = ft_split(input, ' ');
	init_com(&para, inp_sep);
	set_output(&para);
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
			set_output(&para);
		}
		i++;
	}
	para->nbcom = i;
	if_del(&para);
	return ;
}
