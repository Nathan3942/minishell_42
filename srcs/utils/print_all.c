/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:21:39 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/03 05:58:59 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_all(t_params **para, t_env **env)
{
	t_params	*headp;
	t_env		*heade;
	int			i;

	headp = *para;
	heade = *env;
	i = 0;
	printf("commande :\n\n");
	while (headp != NULL)
	{
		while (headp->com[i] != NULL)
		{
			printf("%s ", headp->com[i]);
			i++;
		}
		printf("\n");
		if (headp->output != NULL)
			printf("output : %s\n", headp->output);
		else
			printf("output : sortie std\n");
		if (headp->inp_red == entre1)
			printf("la commande possede un <\n");
		else if (headp->inp_red == entre2)
			printf("la commande possede un <<\n");
		else
			printf("la commande na pas de redirection d'entre\n");
		if (headp->out_red == sortie1)
			printf("la commande possede un >\n");
		else if (headp->out_red == sortie2)
			printf("la commande possede un >>\n");
		else
			printf("la commande na pas de redirection de sortie\n");
		i = 0;
		if (headp->next != NULL)
		{
			printf("la commande a un pipe\n");
		}
		headp = headp->next;
	}
	printf("\n\nEnvironnement :\n");
	while (heade != NULL)
	{
		printf("%s=", heade->env_name);
		printf("%s\n", heade->env_value);
		heade = heade->next;
	}
}