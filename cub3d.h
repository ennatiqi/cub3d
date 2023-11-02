/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:08:41 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 12:54:42 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

# define WIGHT 1024
# define HEIGHT 512
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define FOV 60

typedef struct s_cub
{
	int		check;
	int		maplines;
	char	start_p;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	int		x;
	int		y;
	int		lines;
	int		check_tex;
	int		*c_color;
	int		*f_color;
}	t_cub;

typedef struct s_player
{
	float	x;
	float	y;
	double	angle;
}	t_player;

enum s_deraction{
	east,
	west,
	north,
	south,
};

typedef struct s_texture
{
	mlx_texture_t*	Nimage;
	mlx_texture_t*	Wimage;
	mlx_texture_t*	Simage;
	mlx_texture_t*	Eimage;
	int				*Ncolors;
	int				*Wcolors;
	int				*Scolors;
	int				*Ecolors;
	char*			Wpath;
	char*			Npath;
	char*			Epath;
	char*			Spath;
	int				Ccolor;
	int				Fcolor;
}	t_texture;

typedef struct s_wall
{
	float dist_to_wall;
	float wall_height;
	float wall_start;
	float wall_end;
	float corrected_angle;
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
	int				height;
	int				width;
	mlx_t*			mlx;
	mlx_image_t*	img;
	char			**maps;
	t_player		*player;
	t_cub			*cub;
	t_casting		*cast;
	t_wall			*wall;
	t_texture		*texture;
}	t_game;

//map_check
void	check_mid(char **map, t_game *game);
void	check_first_line(char **map, t_cub *cub, t_game *game);
void	check_component(char **map, t_game *game);
int		name_check(char *name, t_game *game);
void	error(char *str, t_game *game);
void	check_c_f(t_cub	*cub, t_game *game);
void	check_c_f_ext(t_cub *cub, char **c_str, char **f_str, t_game *game);
int		counter(const char *s, char c);
int		ft_toint_check(char *str, t_game *game);
int		ft_toint_check_ext(char *str, int res, int *i, t_game *game);
void	to_free(t_game	*game);
void	check_newline(char **map, t_game *game);
void	check_newline_ext(t_game *game, char *tmp, int *i, char **map);
void	comma_calcu(char *str, t_game *game);

//check_textures
int		check_for_map(char *s, t_cub *cub, t_game *game);
void	no(char *str, t_game *game);
void	so(char *str, t_game *game);
void	we(char *str, t_game *game);
void	ea(char *str, t_game *game);

//check_textures_ext
void	f(char *str, t_game *game);
void	c(char *str, t_game *game);

//map_reader
char	**just_map(char *mapber, t_cub *cub, t_game *game);
int		maplines(char *mapber);
int		width_calc(char **map);
char	**buff_map(char **map, t_cub *cub);
void	buff_map_ext(char **map, char **new_map, t_cub *cub);

//to_free
void	to_free(t_game	*game);
void	free_cub(t_game *game);
void	free_map(char **map);
void	free_textures(t_game *game);

// casting
void	ray_casting(t_game *game);
void	game_wall_printer(t_game *game, t_wall *wall, int i);
void	init_images(t_game *game);

#endif