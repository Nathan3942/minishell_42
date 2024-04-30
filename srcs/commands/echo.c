/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:16 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 11:26:57 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				ft_putchar_fd(str[i], STDOUT_FILENO);
				i += 2;
			}
			else
			{
				ft_putchar_fd(str[i], STDOUT_FILENO);
				break ;
			}
		}
		else
		{
			ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

int	cmd_echo(t_params *para)
{
	int	i;

	i = 1;
	if (ft_strstrbool(para->com[1], "-n") == 0)
		i++;
	while (para->com[i] != NULL)
	{
		print_echo(para->com[i]);
		if (!para->com[i + 1])
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strstrbool(para->com[1], "-n") != 0)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
