/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/05 04:36:56 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char *get_input(void)
{
    char    *raw_input;
    char    *input;

    raw_input = readline("minishell: ");
    input = clean_input(raw_input);
    return (input);
}

int main(int argc, char **argv, char **env)
{
    t_params    *para;
    t_env       *lstenv;
    char        *input;

    if (argc > 1 && argv[1] == NULL)
        exit(EXIT_FAILURE);
    lstenv = set_env(env);
    while (1)
    {
        para = (t_params *)malloc (sizeof(t_params));
        input = get_input();
        if (input == NULL)
            break ;
        add_history(input);
        set_para(&para, input, &lstenv);
        print_all(&para, &lstenv);
        ft_exec(&para, env);
        free(para);
    }
    return (0);
}

