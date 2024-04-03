/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 05:37:13 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/03 06:15:44 by njeanbou         ###   ########.fr       */
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