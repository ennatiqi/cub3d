/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:35:37 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 14:12:48 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_distans_calculater_ext(t_game *game, float *distance_h)
{
	game->cast->dx = game->cast->hx;
	game->cast->dy = game->cast->hy;
	if (game->cast->ra >= 0 && game->cast->ra <= M_PI)
		game->cast->der = south;
	if (game->cast->ra < (M_PI * 2) && game->cast->ra > M_PI)
		game->cast->der = north;
	game->wall->dist_to_wall = (*distance_h) * cos(game->wall->corrected_angle);
}

void	wall_distans_calculater(t_game *game, t_casting *cast, t_wall *wall)
{
	float	distance_h;
	float	distance_v;

	distance_h = sqrt(pow(game->player->x - cast->hx, 2)
			+ pow(game->player->y - cast->hy, 2));
	distance_v = sqrt(pow(game->player->x - cast->vx, 2)
			+ pow(game->player->y - cast->vy, 2));
	if (distance_h < distance_v)
		wall_distans_calculater_ext(game, &distance_h);
	else
	{
		game->cast->dx = cast->vx;
		game->cast->dy = cast->vy;
		if (cast->ra <= M_PI / 2 || cast->ra >= 3 * (M_PI / 2))
			game->cast->der = east;
		if (cast->ra > M_PI / 2 && cast->ra < 3 * (M_PI / 2))
			game->cast->der = west;
		game->wall->dist_to_wall = distance_v * cos(wall->corrected_angle);
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

void	ray_casting(t_game *game)
{
	float	angle_br;
	int		i;

	angle_br = (FOV * M_PI / 180) / WIGHT;
	game->cast->ra = game->player->angle - (FOV * M_PI / 180) / 2;
	game->cast->ra = angle_correcter(game->cast->ra);
	i = -1;
	while (++i < WIGHT)
	{
		horizental_casting(game, game->cast);
		vertical_casting(game, game->cast);
		wall_distans_calculater(game, game->cast, game->wall);
		wall_calculater(game, game->cast, game->wall);
		game_wall_printer(game, game->wall, i);
		game->cast->ra += angle_br;
		game->cast->ra = angle_correcter(game->cast->ra);
	}
}
