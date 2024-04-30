/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:33:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 12:03:42 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_para(t_params **para)
{
	int	i;

	i = 0;
	if ((*para) == NULL)
		return ;
	while ((*para)->com[i] != NULL)
	{
		free((*para)->com[i]);
		i++;
	}
	free((*para)->com);
	free_para(&(*para)->next);
	free((*para));
}

void	free_all(t_params **para, t_put **put)
{
	free_para(para);
	if ((*put)->input != NULL)
		free((*put)->input);
	if ((*put)->output != NULL)
		free((*put)->output);
	free((*put));
}
