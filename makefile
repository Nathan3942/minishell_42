# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 04:50:58 by njeanbou          #+#    #+#              #
#    Updated: 2024/04/08 04:22:41 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(wildcard srcs/utils/*.c srcs/parsing/*.c srcs/exec/*.c main.c)

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS =  -fsanitize=address -static-libsan

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