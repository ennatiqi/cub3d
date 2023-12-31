# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/30 12:22:46 by aachfenn          #+#    #+#              #
#    Updated: 2023/11/02 21:38:07 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			map_check/map_check.c \
			map_check/map_check_2.c \
			map_check/map_check_3.c \
			map_check/map_reader.c \
			map_check/map_reader_2.c \
			ray_casting/ray_casting.c \
			ray_casting/ray_casting_2.c \
			ray_casting/key_press.c \
			ray_casting/init_images.c \
			ray_casting/image_macker.c \
			map_check/check_textures.c \
			map_check/check_textures_ext.c \
			map_check/to_free.c \
			ray_casting/horizental_vertical_cas.c \

CC		= cc

CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address -g 

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
	 ${RM} ${OBJ}
	./cub3D ./maps/map.cub
