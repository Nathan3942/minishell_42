/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:41:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/18 17:11:43 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_var_beg(t_params **para, t_env **env)
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
			}
		}
		i++;
	}
}

static char	**mid_var_env(char **split_str, t_env **env)
{
	int		i;
	char	*var;

	i = 0;
	while (split_str[i] != NULL)
	{
		if (split_str[i][0] == '$')
		{
			var = recherche_env(split_str[i], env);
			free(split_str[i]);
			split_str[i] = ft_strdup(var);
		}
		i++;
	}
	return (split_str);
}

static char	*mid_var(char *str, t_env **env)
{
	char	**split_str;
	char	*var;
	int		i;

	split_str = split_var(str);
	split_str = mid_var_env(split_str, env);
	i = 0;
	var = NULL;
	while (split_str[i] != NULL)
	{
		var = ft_strjoin(var, split_str[i]);
		i++;
	}
	return (var);
}

static void	set_var_mid(t_params **para, t_env **env)
{
	t_params	*headp;
	char		*var;
	int			i;
	int			z;

	headp = *para;
	var = NULL;
	i = 0;
	while (headp->com[i] != NULL)
	{
		z = 0;
		while (headp->com[i][z] != '\0')
		{
			if (headp->com[i][z] == '\'')
				break ;
			if (headp->com[i][z] == '$')
			{
				var = mid_var(headp->com[i], env);
				free(headp->com[i]);
				headp->com[i] = var;
			}
			z++;
		}
		i++;
	}
}

void	set_var(t_params **para, t_env **env)
{
	set_var_beg(para, env);
	set_var_mid(para, env);
}
