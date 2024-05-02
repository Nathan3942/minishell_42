# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 04:50:58 by njeanbou          #+#    #+#              #
#    Updated: 2024/05/02 16:57:32 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(wildcard srcs/utils/*.c srcs/parsing/*.c srcs/exec/*.c srcs/commands/*.c main.c)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Werror -Wextra -Wall -fsanitize=address -static-libsan

#-Werror -Wextra -Wall
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
				@${MAKE} -C ./libft
				@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME} -lreadline

clean:
				@${MAKE} -C ./libft fclean
				@${RM} ${OBJS}

fclean:	clean	
				@${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re