/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:21 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 15:43:41 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	to_free(t_game	*game)
{
	if (game)
	{
		if (game->cub)
			free_cub(game);
		if (game->player)
			free(game->player);
		if (game->cast)
			free(game->cast);
		if (game->wall)
			free(game->wall);
		if (game->texture)
		{
			free_textures(game);
			if (game->texture->Spath)
				free(game->texture->Spath);
			free(game->texture);
		}
		if (game->maps)
			free_map(game->maps);
		free(game);
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_textures(t_game *game)
{
	if (game->texture->Nimage)
		mlx_delete_texture(game->texture->Nimage);
	if (game->texture->Wimage)
		mlx_delete_texture(game->texture->Wimage);
	if (game->texture->Simage)
		mlx_delete_texture(game->texture->Simage);
	if (game->texture->Eimage)
		mlx_delete_texture(game->texture->Eimage);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->texture->Ncolors)
		free(game->texture->Ncolors);
	if (game->texture->Ecolors)
		free(game->texture->Ecolors);
	if (game->texture->Wcolors)
		free(game->texture->Wcolors);
	if (game->texture->Scolors)
		free(game->texture->Scolors);
	if (game->texture->Npath)
		free(game->texture->Npath);
	if (game->texture->Epath)
		free(game->texture->Epath);
	if (game->texture->Wpath)
		free(game->texture->Wpath);
}

void	free_cub(t_game *game)
{
	if (game->cub->NO)
		free(game->cub->NO);
	if (game->cub->EA)
		free(game->cub->EA);
	if (game->cub->SO)
		free(game->cub->SO);
	if (game->cub->WE)
		free(game->cub->WE);
	if (game->cub->C)
		free(game->cub->C);
	if (game->cub->F)
		free(game->cub->F);
	if (game->cub->c_color)
		free(game->cub->c_color);
	if (game->cub->f_color)
		free(game->cub->f_color);
	if (game->cub)
		free(game->cub);
}
