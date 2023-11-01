# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/30 12:22:46 by aachfenn          #+#    #+#              #
#    Updated: 2023/11/01 11:30:25 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c \
			get_next_line/get_next_line.c \
			map_check/map_check.c \
			map_check/map_reader.c \
			ray_casting/ray_casting.c \
			ray_casting/init_images.c \
			ray_casting/image_macker.c \
			map_check/check_textures.c \

CC		= cc

CFLAGS	= -fsanitize=address -g -Wall -Werror -Wextra 

OBJ		= ${SRC:.c=.o}

NAME	= cub3D

%.o : %.c Makefile
	${CC} ${CFLAGS} -c $< -o $@
	 
	
${NAME}	:	${OBJ} cub3d.h
		make -C libft
		${CC} ${CFLAGS} ${OBJ} libft/libft.a -o ${NAME} ./MLX42/build/libmlx42.a -I include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all		: ${NAME}

bonus	:	all

clean	:
		${RM} ${OBJ}
		make clean -C libft

fclean	:	clean
		make fclean -C libft
		${RM} cub3D

re		: fclean all

run	:  all
	# ${RM} ${OBJ}
	./cub3D ./maps/map.cub
