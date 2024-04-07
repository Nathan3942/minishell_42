/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 05:37:13 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/04 05:25:00 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_output(t_params **para)
{
	t_params	*head;
	int			i;

	head = *para;
	head->output = NULL;
	i = 0;
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] == '>')
			head->output = head->com[i + 1];
		i++;
	}
}

void	set_input(t_params **para)
{
	t_params	*head;
	int			i;
	int			z;

	head = *para;
	i = 1;
	z = 0;
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] != '-' && head->com[i][0] != '|' &&
			head->com[i - 1][0] != '>' && head->com[i][0] != '>' &&
			head->com[i][0] != '>')
		{
			z++;
		}
		i++;
	}
	head->input = (char **)malloc ((z + 1) * sizeof(char *));
	i = 1;
	z = 0;
	while (head->com[i] != NULL)
	{
		if (head->com[i][0] != '-' && head->com[i][0] != '|' &&
			head->com[i - 1][0] != '>' && head->com[i][0] != '>' &&
			head->com[i][0] != '<')
		{
			head->input[z] = ft_strdup(head->com[i]);
			z++;
		}
		i++;
	}
	head->input[z] = NULL;
}
