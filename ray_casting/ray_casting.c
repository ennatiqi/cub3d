/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:35:37 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/30 11:38:12 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



void    horizental_casting(t_game *game, t_casting *cast)
{
	float xsteps,ysteps;
	float atan = -1/tan(cast->ra);

	if (cast->ra > 0 && cast->ra < M_PI)
	{
		cast->hy = ((int)(game->player->y / 64) * 64) + 64;
		cast->hx = (game->player->y - cast->hy) * atan + game->player->x;
		ysteps = 64;
		xsteps = -64 * atan;
	}
	else if (cast->ra < (M_PI * 2) && cast->ra > M_PI)
	{
		cast->hy = ((int)(game->player->y / 64) * 64) - 0.0001;
		cast->hx = (game->player->y - cast->hy) * atan + game->player->x;
		ysteps = -64;
		xsteps = 64 * atan;
	}
	while (1)
	{
		int tmpx = (int)(cast->hx / 64);
		int tmpy = (int)(cast->hy / 64);
		if (tmpx > 0 && tmpx < game->width && tmpy > 0 && tmpy < game->height)
		{
			if (game->maps[tmpy][tmpx] == '1')
				break;
			cast->hx += xsteps;
			cast->hy += ysteps;
		}
		else
			break;
	}
}

void    vertical_casting(t_game *game, t_casting *cast)
{
	float   xsteps;
	float   ysteps;

	xsteps = 0;
	ysteps = 0;

	float atan = -tan(cast->ra);
	if (cast->ra <= M_PI / 2 || cast->ra >= 3 * (M_PI / 2))
	{
		cast->vx = ((int)(game->player->x / 64) * 64) + 64;
		cast->vy = (game->player->x - cast->vx) * atan + game->player->y;
		xsteps = 64; 
		ysteps = -64 * atan;
	}
	else if (cast->ra > M_PI / 2 && cast->ra < 3 * (M_PI / 2))
	{
		cast->vx = ((int)(game->player->x / 64) * 64) - 0.0001;
		cast->vy = (game->player->x - cast->vx) * atan + game->player->y;
		xsteps = -64;
		ysteps = 64 * atan;
	}
	while (1)
	{
		int tmpx = (int)(cast->vx / 64);
		int tmpy = (int)(cast->vy / 64);
		if (tmpx > 0 && tmpx < game->width && tmpy > 0 && tmpy < game->height)
		{
			if (game->maps[tmpy][tmpx] == '1')
				break;
			cast->vx += xsteps;
			cast->vy += ysteps;
		}
		else
			break;
	}
}

void    wall_distans_calculater(t_game *game, t_casting *cast, t_wall *wall)
{
	float distance_h;
	float distance_v;

	distance_h = sqrt(pow(game->player->x - cast->hx, 2) + pow(game->player->y - cast->hy, 2));
	distance_v = sqrt(pow(game->player->x - cast->vx, 2) + pow(game->player->y - cast->vy, 2));

	if (distance_h < distance_v)
	{
		game->cast->dx = cast->hx;
		game->cast->dy = cast->hy;
		if (cast->ra >= 0 && cast->ra <= M_PI)
			game->cast->der = south;
		if (cast->ra < (M_PI * 2) && cast->ra > M_PI)
			game->cast->der = north;
		game->wall->dist_to_wall = distance_h * cos(wall->corrected_angle);
	}
	else
	{
		game->cast->dx = cast->vx;
		game->cast->dy = cast->vy;
		if (cast->ra <= M_PI / 2 || cast->ra >= 3 * (M_PI / 2))
			game->cast->der = east;
		if (cast->ra > M_PI / 2 && cast->ra < 3 * (M_PI / 2))
			game->cast->der = west;
		game->wall->dist_to_wall = distance_v  * cos(wall->corrected_angle);
		
	}
}

void	wall_calculater(t_game *game, t_casting *cast, t_wall *wall)
{
	wall->corrected_angle = game->player->angle - cast->ra;
	
		
	wall->wall_height = ((HEIGHT) / wall->dist_to_wall) * 32;
	wall->wall_start = (int)((HEIGHT - wall->wall_height) / 2);
	wall->wall_end = wall->wall_start + wall->wall_height;
}

float	angle_correcter(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}


void ray_casting(t_game *game)
{
	t_casting *cast;
	float angle_br;
	t_wall *wall;

	angle_br = (FOV * M_PI / 180) / WIGHT;
	cast = malloc(sizeof(t_casting));
	wall = malloc(sizeof(t_wall));

	game->cast = cast;
	game->wall = wall;
	cast->ra = game->player->angle - (FOV * M_PI / 180) / 2;
	cast->ra = angle_correcter(cast->ra);

	int i = -1;
	while(++i < WIGHT)
	{
		
		horizental_casting(game, cast);
		
		vertical_casting(game, cast);
	
		wall_distans_calculater(game, cast, wall);
		
		wall_calculater(game, cast, wall);

		game_wall_printer(game, wall, i);

		
		cast->ra+= angle_br;
		cast->ra = angle_correcter(cast->ra);
	}
}
