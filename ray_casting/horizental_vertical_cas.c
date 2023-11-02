/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizental_vertical_cas.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:55:20 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 14:14:59 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	horizental_casting_ext(t_game *game, float *atan, \
float *xsteps, float *ysteps)
{
	if (game->cast->ra > 0 && game->cast->ra < M_PI)
	{
		game->cast->hy = ((int)(game->player->y / 64) * 64) + 64;
		game->cast->hx = (game->player->y - game->cast->hy) \
		* (*atan) + game->player->x;
		(*ysteps) = 64;
		(*xsteps) = -64 * (*atan);
	}
	else if (game->cast->ra < (M_PI * 2) && game->cast->ra > M_PI)
	{
		game->cast->hy = ((int)(game->player->y / 64) * 64) - 0.001;
		game->cast->hx = (game->player->y - game->cast->hy) * \
		(*atan) + game->player->x;
		(*ysteps) = -64;
		(*xsteps) = 64 * (*atan);
	}
}

void	horizental_casting(t_game *game, t_casting *cast)
{
	float	ysteps;
	float	xsteps;
	float	atan;
	int		tmpx;
	int		tmpy;

	atan = -1 / tan(cast->ra);
	horizental_casting_ext(game, &atan, &xsteps, &ysteps);
	while (1)
	{
		tmpx = (int)(cast->hx / 64);
		tmpy = (int)(cast->hy / 64);
		if (tmpx > 0 && tmpx < game->width && tmpy > 0 && tmpy < game->height)
		{
			if (game->maps[tmpy][tmpx] == '1')
				break ;
			cast->hx += xsteps;
			cast->hy += ysteps;
		}
		else
			break ;
	}
}

void	vertical_casting_ext(t_game *game, float *atan, \
float *xsteps, float *ysteps)
{
	(*atan) = -tan(game->cast->ra);
	if (game->cast->ra <= M_PI / 2 || game->cast->ra >= 3 * (M_PI / 2))
	{
		game->cast->vx = ((int)(game->player->x / 64) * 64) + 64;
		game->cast->vy = (game->player->x - game->cast->vx) * \
		(*atan) + game->player->y;
		(*xsteps) = 64; 
		(*ysteps) = -64 * (*atan);
	}
	else if (game->cast->ra > M_PI / 2 && game->cast->ra < 3 * (M_PI / 2))
	{
		game->cast->vx = ((int)(game->player->x / 64) * 64) - 0.001;
		game->cast->vy = (game->player->x - game->cast->vx) * \
		(*atan) + game->player->y;
		(*xsteps) = -64;
		(*ysteps) = 64 * (*atan);
	}
}

void	vertical_casting(t_game *game, t_casting *cast)
{
	float	xsteps;
	float	ysteps;
	float	atan;
	int		tmpx;
	int		tmpy;

	xsteps = 0;
	ysteps = 0;
	vertical_casting_ext(game, &atan, &xsteps, &ysteps);
	while (1)
	{
		tmpx = (int)(cast->vx / 64);
		tmpy = (int)(cast->vy / 64);
		if (tmpx > 0 && tmpx < game->width && tmpy > 0 && tmpy < game->height)
		{
			if (game->maps[tmpy][tmpx] == '1')
				break ;
			cast->vx += xsteps;
			cast->vy += ysteps;
		}
		else
			break ;
	}
}
