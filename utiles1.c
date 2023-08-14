/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:12:01 by rennatiq          #+#    #+#             */
/*   Updated: 2023/01/21 17:27:50 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void horizontal_vertical_lines(t_casting *cast,t_player *player, t_game *game)
{
	float rx,ry,xo,yo;
	int r, mx,my,mp;
	float atan;

	atan = 1/tan(cast->ra);
	cast->hy = 0;
	cast->hx = 0;
	cast->vy = 0;
	cast->vx = 0;
	if (cast->ra < PI)
	{
		cast->hy = (int)player->y * 64 / 64 - 1; 
		cast->hx = (player->y - cast->hy ) * atan + player->x; 
		yo = -0.5; 
		xo = -yo * atan;
	}
	if (cast->ra > PI) 
	{
		cast->hy = ((int)player->y * 64 / 64) + 64;
		cast->hx = (player->y - cast->hy ) * atan + player->x; 
		yo = 0.5; 
		xo = -yo * atan;
	}
	if (cast->ra == 0 || cast->ra == (float)PI)
	{
		cast->hy = player->y;
		cast->hx = player->x;
	}
	else
	{
		while (1)
		{
			mx = (int)(cast->hx) / 64;
			my = (int)(cast->hy) / 64;
			mp = my * game->width + mx;

			if (mx >= 0 && mx < game->width && my >= 0 && my < game->height)
			{
				if (game->line[mp] == '1')
					break;
				else
				{
					cast->hx += xo;
					cast->hy += yo;
				}
			}
			else
				break;
		}
    }
	atan = tan(cast->ra);
	if (cast->ra < P2 || cast->ra > P3)  
	{
		cast->vx = (int)player->x * 64 / 64 + 64; 
		cast->vy = (player->x - cast->vx ) * atan + player->y; 
		xo = 0.5; 
		yo = -xo * atan;
	}
	if (cast->ra > P2 && cast->ra < P3) 
	{
		cast->vx = ((int)player->x * 64 / 64) - 1;
		cast->vy = (player->x - cast->vx ) * atan + player->y; 
		xo = -0.5; 
		yo = -xo * atan;
	}
	if (cast->ra == P2 || cast->ra == P3)
	{
		cast->vx = player->x; 
		cast->vy = player->y;
	}
	else
	{
		while (1)
		{
			mx = (int)(cast->vx) / 64;
			my = (int)(cast->vy) / 64;
			mp = my * game->width + mx;

			if (mx >= 0 && mx < game->width && my >= 0 && my < game->height)
			{
				if (game->line[mp] == '1')
				{
					break;
				}
				else
				{
					cast->vx += xo;
					cast->vy += yo;
				}
			}
			else
				break;

		}
	}
}

t_game	*insert_to_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->height = 0;
	game->player = malloc(sizeof(t_player));
	game->player->angle = 0;


	return (game);
}

void	set_game(t_game *game, char *map)
{
	read_maps(game, map);
	game->win = mlx_new_window(game->mlx,1024, 512, "cub3d");
	game->player = malloc(sizeof(t_player));

	// 7sab position dyalo
	int		i;
	int		j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->line[(i * game->width) + j] == 'W')
			{
				game->player->x = j *64;
				game->player->y = i * 64;
				return;
				
			}
         
			j++;
		}
		i++;
	}
    
}

float degToRad(int a) 
{ 
	return a*M_PI/180.0;
}

int FixAng(int a)
{ 
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return a;
}

float dist(float ax , float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) * cos(degToRad(ang)));
}

void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) 
{ 
	int dx;
    int dy;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	int err2;
    int sign_x;
    int sign_y;

	if (x1 < x2)
		sign_x = 1;
	else
		sign_x = -1;
	if (y1 < y2)
		sign_y = 1;
	else
		sign_y = -1;
    int err;
	err = dx - dy;

    mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, color);

    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
        err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sign_x;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sign_y;
        }
    }
}



void draw_rectangle(void *mlx_ptr, void *win_ptr, int x, int y, int width)
{
    int i = 0;
	int j ;

	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}


void draw_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->line[(i * game->width) + j] == '1')
				draw_rectangle(game->mlx, game->win, j * 64, i * 64, 62);
         
			j++;
		}
		i++;
	}
}

int valid_move(int x, int y, t_game *game) {
    if (x < 0 || y < 0 || x >= game->width * 64 || y >= game->height * 64)
        return 0;

    if (game->line[((int)(y / 64) * game->width) + (int)(x / 64)] == '1')
        return 0;
    return 1;
} 
 
int key_press(int keycode, t_game *game) {
    int speed = 5;
    int tmpx = game->player->x;
    int tmpy = game->player->y;

    if (keycode == 53)
        exit(0);
    if (keycode == 13)
    {
		tmpy -= speed * cos(game->player->angle - P2);
        tmpx += speed * sin(game->player->angle + P2);
	}
    if (keycode == 1)
	{
        tmpy += speed * cos(game->player->angle - P2);
        tmpx -= speed * sin(game->player->angle + P2);
	}
    if (keycode == 2)
	{
        game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
	}
    if (keycode == 0)
	{
		game->player->angle += 0.1;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
	}

    if (valid_move(tmpx, tmpy, game))
	{
        game->player->x = tmpx;
        game->player->y = tmpy;
    }

    return 0;
}

int	check_ifis_file(char *map)
{
	int		fd;

	fd = open(map, O_DIRECTORY);
	if (fd == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_rectangular(char *check, int size)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (check[i])
	{
		if (check[i] == '\n')
		{
			if (count - 1 != size)
				return (0);
			count = 0;
		}
		count++;
		i++;
		if (!check[i])
		{
			if (count - 1 != size)
				return (0);
		}
	}
	return (1);
}
char	*ft_strdup_noline(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(ft_strlen(line));
	if (!tmp)
		return (0);
	while (i < (int)ft_strlen(line) - 1)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	free(line);
	return (tmp);
}
char	*ft_strdup_m(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s2)
		return (0);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*read_norm(char *line, t_game *game)
{
	char	*check;

	check = ft_strdup_m(line);
	game->width = ft_strlen(line) - 1;
	game->line = ft_strdup_noline(line);
	return (check);
}
char	*ft_strjoin_so_long(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*resulta;
	int		m;
	int		n;

	i = 0;
	if (!s1 || !s2)
		return (0);
	n = ft_strlen(s1);
	m = ft_strlen(s2);
	resulta = (char *)malloc((n + m + 1) * sizeof(char));
	if (!resulta)
		return (0);
	while (i < n)
	{
		resulta[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && s2[j] != '\n')
		resulta[i++] = s2[j++];
	resulta[i] = 0;
	free(s1);
	free(s2);
	return (resulta);
}
void	read_maps(t_game *game, char *map)
{
	int		fd;
	char	*line;
	char	*check;

	// if (!check_ifis_file(map))
	// 	ft_error('F');
	fd = open(map, O_RDONLY);
	// if (fd < 0)
	// 	ft_error('S');
	line = get_next_line(fd);
	// if (!line)
	// 	ft_error('W');
	check = read_norm(line, game);
	while (line)
	{
		game->height++;
		line = get_next_line(fd);
		if (!line)
			break ;
		check = ft_strjoin(check, line);
		game->line = ft_strjoin_so_long(game->line, line);
	}
	// if (game->width > 40 || game->width < 2 || game->height > 30
	// 	|| game->height < 2 /* || !check_rectangular(check, game->width) */)
	// {
	// 	free(check);
	// 	ft_error('R');
	// }
	free(check);
	close(fd);
}
