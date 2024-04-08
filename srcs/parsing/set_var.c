/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:41:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/08 06:01:02 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_var(t_params **para, t_env **env)
{
	t_params	*headp;
	t_env		*heade;
	char		*var;
	int			i;

	var = NULL;
	headp = *para;
	heade = *env;

 	i = 0;
	while (headp->com[i] != NULL)
	{	
		if (headp->com[i][0] == '$')
		{
			var = recherche_env(headp->com[i], &heade);
			if (var != NULL)
			{
				free(headp->com[i]);
				headp->com[i] = ft_strdup(var);
				printf("KSKS");
			}
		}
		i++;
	}
}






// {
// 	t_params	*head;
// 	t_env		*henv;
// 	int			i;
// 	char		*var;

// 	head = *para;
// 	henv = *env;
// 	while (head != NULL && henv != NULL)
// 	{
// 		i = 0;
// 		while (head->com[i] != NULL)
// 		{	
// 			if (head->com[i] != NULL && head->com[i][0] == '$')
// 			{
// 				var = recherche_env(head->com[i] + 1, &henv);
// 				if (var != NULL)
// 				{
// 					free(head->com[i]);
// 					head->com[i] = ft_strdup(var);
// 				}
// 			}
// 			i++;
// 		}
// 		head = head->next;
// 	}
// }
