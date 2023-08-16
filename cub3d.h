/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:22:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/22 00:16:51 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "MLX/mlx.h"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI/2
#define P4 2 * PI
#define WIGHT 1024
#define HEIGHT 512
#define DR 0.0174533/8

# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2

typedef struct s_casting
{
	float hx;
	float hy;
	float vx;
	float vy;
	float ra;
}	t_casting;

typedef struct s_cub
{
	int	maplines;
	int	i;
	int	j;
}	t_cub;

typedef struct s_player {
    int x;
    int y;
    double angle;

} t_player;

typedef struct s_image
{
	void	*avatar;
	void	*wall;
	void	*imt;
}		t_img;

typedef struct s_path
{
	char	*path_avatar;
	char	*path_wall;
	char	*path_imt;
}	t_path;

typedef struct s_game
{
	char	*line;
	int		height;
	int		width;
	void	*mlx;
	void	*win;
	t_img	img;
	t_path	path;
	t_player *player;
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


// void	move_a(t_game *game);
// void	move_s(t_game *game);
// void	move_d(t_game *game);
// void	move_w(t_game *game);
void	read_maps(t_game *game, char *map);
void	setting_img(t_game *game);

void	put_image(t_game *game);
int key_press(int keycode, t_game *game) ;
int valid_move(int x, int y, t_game *game) ;
void draw_map(t_game *game);
void draw_rectangle(void *mlx_ptr, void *win_ptr, int x, int y, int width);

void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) ;
float degToRad(int a) ;
int FixAng(int a);
float dist(float ax , float ay, float bx, float by, float ang);
t_game	*insert_to_game(void);
void	set_game(t_game *game, char *map);
void horizontal_vertical_lines(t_casting *cast,t_player *player, t_game *game);



#endif