/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:08:41 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/19 10:42:28 by rennatiq         ###   ########.fr       */
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
#define FOV 60


typedef struct s_cub
{
	int	maplines;
	int	i;
	int	j;
}	t_cub;

typedef struct s_player
{
    float x;
    float y;
    double angle;
} t_player;

enum s_deraction{
	right,
	left,
	up,
	down
};

typedef struct s_wall
{
	float dist_to_wall;
	float wall_height;
	float wall_start;
	float wall_end;
	float corrected_angle;

	float diraction;
	
}	t_wall;

typedef struct s_casting
{
	float hx;
	float hy;
	float vx;
	float vy;
	float dx;
	float dy;
	float ra;
	enum s_deraction der;
}	t_casting;

typedef struct s_game
{
	int		height;
	int		width;
	mlx_t*	mlx;
	mlx_image_t* img;
    char    **maps;
	t_player *player;
    t_cub    *cub;
	t_casting *cast;
	t_wall *wall;
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

// casting
void ray_casting(t_game *game);

#endif