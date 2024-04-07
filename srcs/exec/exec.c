/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 05:28:42 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/05 03:49:00 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_exec(t_params **para, char **env)
{
	t_params	*head;
	pid_t		pid;
	char		*bin;
	int			out_fd;
	int			save_out;

	pid = fork();
	head = *para;
	save_out = dup(STDOUT_FILENO);

	if (head->out_red != none)
	{
		out_fd = open(head->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (pid == 0)
	{
		bin = ft_strjoin("/bin/", head->com[0]);
		execve(bin, head->com, env);
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
	else
		wait(NULL);
	return ;
}

// void ft_exec(t_params **para, char **env) 
// {
//     t_params *head = *para;
//     pid_t pid;
//     char *bin;

//     pid = fork();

//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // Processus enfant
//         if (head->out_red != none) {
//             int out_fd = open("ksks.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (out_fd == -1) {
//                 perror("open");
//                 exit(EXIT_FAILURE);
//             }
//             if (dup2(out_fd, STDOUT_FILENO) == -1) {
//                 perror("dup2");
//                 exit(EXIT_FAILURE);
//             }
//             close(out_fd);
//         }

//         bin = ft_strjoin("/bin/", head->com[0]);
//         if (bin == NULL) {
//             fprintf(stderr, "Erreur: Impossible de joindre le chemin du binaire\n");
//             exit(EXIT_FAILURE);
//         }

//         if (execve(bin, head->com, env) == -1) {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//         // Cette instruction ne sera exécutée que si execve échoue
//         exit(EXIT_FAILURE);
//     }
// 	// else {
//     //     // Processus parent
//     //     int status;
//     //     if (waitpid(pid, &status, 0) == -1) {
//     //         perror("waitpid");
//     //         exit(EXIT_FAILURE);
//     //     }
//     //     if (WIFEXITED(status)) {
//     //         printf("Le processus enfant s'est terminé avec le code de sortie %d\n", WEXITSTATUS(status));
//     //     } else {
//     //         printf("Le processus enfant s'est terminé de manière anormale\n");
//     //     }
//     // }
// }
