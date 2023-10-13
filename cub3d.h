/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:08:41 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/13 11:56:24 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "MLX42/include/MLX42/MLX42.h"


#define WIGHT 1024
#define HEIGHT 512

# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2


typedef struct s_cub
{
	int	maplines;
	int	i;
	int	j;
}	t_cub;

typedef struct s_player
{
    int x;
    int y;
    double angle;
} t_player;

typedef struct s_game
{
	int		height;
	int		width;
	mlx_t*	mlx;
	mlx_image_t* img;
    char    **maps;
	t_player *player;
    t_cub    *cub;
}		t_game;

//map_check
void	check_the_path(char **map, t_cub *cub);
void	check_the_path_2(char **map, t_cub *cub);
void	check_component(char **map);
int		name_check(char *name);
int		exiter(void);

//map_reader
int		maplines(char *mapber);
char	**mapreader(char *mapber);

#endif