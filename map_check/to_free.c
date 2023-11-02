/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:21 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/02 21:30:57 by aachfenn         ###   ########.fr       */
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
	if (game->texture->nimage)
		mlx_delete_texture(game->texture->nimage);
	if (game->texture->wimage)
		mlx_delete_texture(game->texture->wimage);
	if (game->texture->simage)
		mlx_delete_texture(game->texture->simage);
	if (game->texture->eimage)
		mlx_delete_texture(game->texture->eimage);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->texture->ncolors)
		free(game->texture->ncolors);
	if (game->texture->ecolors)
		free(game->texture->ecolors);
	if (game->texture->wcolors)
		free(game->texture->wcolors);
	if (game->texture->scolors)
		free(game->texture->scolors);
}

void	free_cub(t_game *game)
{
	if (game->cub->no)
		free(game->cub->no);
	if (game->cub->ea)
		free(game->cub->ea);
	if (game->cub->so)
		free(game->cub->so);
	if (game->cub->we)
		free(game->cub->we);
	if (game->cub->c)
		free(game->cub->c);
	if (game->cub->f)
		free(game->cub->f);
	if (game->cub->c_color)
		free(game->cub->c_color);
	if (game->cub->f_color)
		free(game->cub->f_color);
	if (game->cub)
		free(game->cub);
}
