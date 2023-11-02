/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:54:53 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 15:49:02 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exiter(t_game *game)
{
	to_free(game);
	mlx_close_window(game->mlx);
}

int	valide_move(int tmpy, int tmpx, t_game *game)
{
	tmpy /= 64;
	tmpx /= 64;
	if ((game->maps[(int)game->player->y / 64][tmpx] == '1' && \
	game->maps[tmpy][(int)game->player->x / 64] == '1') \
	|| game->maps[tmpy][tmpx] == '1')
		return (0);
	return (1);
}

void	draw(void *game2)
{
	t_game	*game;

	game = (t_game *)game2;
	ray_casting(game);
}
