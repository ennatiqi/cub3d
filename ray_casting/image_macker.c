/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_macker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:25:30 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/30 10:24:29 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_wall_printer(t_game *game, t_wall *wall, int i)
{
    int j = -1;
    int x,y;

    if (game->cast->der == right || game->cast->der == left) 
		x = (int)game->cast->dy % 64;
	else if (game->cast->der == up || game->cast->der == down)
		x = (int)game->cast->dx % 64;
    while (++j < HEIGHT)
    {
        if (j > wall->wall_start && j < wall->wall_end)
        {
            y = (int)((j - wall->wall_start) * (64.0 / wall->wall_height));

            if (game->cast->der == left)
            	mlx_put_pixel(game->img, i, j, game->texture->Ncolors[x + (y * game->texture->Nimage->width)]);
            else if (game->cast->der == right)
            	mlx_put_pixel(game->img, i, j, game->texture->Scolors[x + (y * game->texture->Simage->width)]);
            else if (game->cast->der == up)
            	mlx_put_pixel(game->img, i, j, game->texture->Ecolors[x + (y * game->texture->Eimage->width)]);
            else if (game->cast->der == down)
            	mlx_put_pixel(game->img, i, j, game->texture->Wcolors[x + (y * game->texture->Wimage->width)]);
        }
        if (j <= wall->wall_start)
             mlx_put_pixel(game->img, i, j, game->texture->Ccolor);
        else if (j >= wall->wall_end)
             mlx_put_pixel(game->img, i, j, game->texture->Fcolor);
    }

}