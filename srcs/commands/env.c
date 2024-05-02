/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:12:04 by njeanbou          #+#    #+#             */
/*   Updated: 2024/05/02 19:17:45 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_env(t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL)
	{
		ft_putstr_fd(head->env_name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(head->env_value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
