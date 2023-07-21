# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/30 12:22:46 by aachfenn          #+#    #+#              #
#    Updated: 2023/07/17 15:13:53 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c map_check/map_check.c map_check/map_reader.c \
			get_next_line/get_next_line.c 
			

CC		= cc

# CFLAGS	= arch -x86_64 cc -L../mlx -lmlx -framework OpenGL -framework AppKit

CFLAGS	= #-fsanitize=address -g #-Wall -Werror -Wextra 

OBJ		= ${SRC:.c=.o}

NAME	= cub3D

%.o : %.c Makefile
	${CC} ${CFLAGS} -c $< -o $@
	 
	
${NAME}	:	${OBJ} cub3d.h
		make -C libft
		${CC} ${CFLAGS} ${OBJ} libft/libft.a MLX/libmlx.a -o ${NAME} -framework OpenGL -framework Appkit

all		: ${NAME}

bonus	:	all

clean	:
		${RM} ${OBJ}
		make clean -C libft

fclean	:	clean
		make fclean -C libft
		${RM} cub3D

# it		: all ./cub3D

re		: fclean all
