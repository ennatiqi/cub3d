/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_macker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:25:30 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/21 09:49:03 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_wall_printer(t_game *game, t_wall *wall, int i)
{
    int j = -1;
    int x,y;

    if (wall->diraction == right || wall->diraction == left) 
		x = (int)game->cast->dy % 64;
	else if (wall->diraction == up || wall->diraction == down)
		x =  (int)game->cast->dx % 64;
    while (++j < HEIGHT)
    {
        if (j >= wall->wall_start && j <= wall->wall_end)
        {
            y = (int)((j - wall->wall_start) * (64.0 / wall->wall_height));
            mlx_put_pixel(game->img, i, j, 0xFFFFFFFF);
            // mlx_put_pixel(game->img, i, j, game->texture->Ncolors[x * y]);
            // if (game->cast->der == left)
            // 	mlx_put_pixel(game->img, i, j, game->texture->Ncolors[x * y]);
            // else if (game->cast->der == right)
            // 	mlx_put_pixel(game->img, i, j, game->texture->Scolors[x * y]);
            // else if (game->cast->der == up)
            // 	mlx_put_pixel(game->img, i, j, game->texture->Ecolors[x * y]);
            // else if (game->cast->der == down)
            // 	mlx_put_pixel(game->img, i, j, game->texture->Wcolors[x * y]);
        }
        else if (j < wall->wall_start)
        {
             mlx_put_pixel(game->img, i, j, 0xFF0000FF);
        }
        else if (j > wall->wall_end)
        {
             mlx_put_pixel(game->img, i, j, 0xFF000000);
        }
    }

	/* // if (game->cast->der == left)
	// 	draw_line2(game, i, wall->wall_start, i, wall->wall_end,0xFFFFFFFF);
	// else if (game->cast->der == right)
	// 	draw_line2(game, i, wall->wall_start, i, wall->wall_end,0xFFCCFFFF);
	// else if (game->cast->der == up)
	// 	draw_line2(game, i, wall->wall_start, i, wall->wall_end, 0xFFFF00FF);
	// else if (game->cast->der == down)
	// 	draw_line2(game, i, wall->wall_start, i, wall->wall_end, 0xFFCC00FF);

	// draw_line2(game, i , 0, i, wall->wall_start,0x0000000 );
	// draw_line2(game, i, wall->wall_end, i, HEIGHT, 0x00000000); */
}