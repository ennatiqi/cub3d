/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_macker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:25:30 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 13:42:50 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_wall_printer_ext(t_game *game, int i, int j, int x)
{
	int	y;

	y = (int)((j - game->wall->wall_start) * (64.0 / game->wall->wall_height));
	if (game->cast->der == north)
		mlx_put_pixel(game->img, i, j, \
		game->texture->Ncolors[x + (y * game->texture->Nimage->width)]);
	else if (game->cast->der == south)
		mlx_put_pixel(game->img, i, j, \
		game->texture->Scolors[x + (y * game->texture->Simage->width)]);
	else if (game->cast->der == east)
		mlx_put_pixel(game->img, i, j, \
		game->texture->Ecolors[x + (y * game->texture->Eimage->width)]);
	else if (game->cast->der == west)
		mlx_put_pixel(game->img, i, j, \
		game->texture->Wcolors[x + (y * game->texture->Wimage->width)]);
}

void	game_wall_printer(t_game *game, t_wall *wall, int i)
{
	int	j;
	int	y;
	int	x;

	j = -1;
	if (game->cast->der == east || game->cast->der == west) 
		x = (int)game->cast->dy % 64;
	else if (game->cast->der == north || game->cast->der == south)
		x = (int)game->cast->dx % 64;
	while (++j < HEIGHT)
	{
		if (j > wall->wall_start && j < wall->wall_end)
			game_wall_printer_ext(game, i, j, x);
		if (j <= wall->wall_start)
			mlx_put_pixel(game->img, i, j, game->texture->Ccolor);
		else if (j >= wall->wall_end)
			mlx_put_pixel(game->img, i, j, game->texture->Fcolor);
	}
}
