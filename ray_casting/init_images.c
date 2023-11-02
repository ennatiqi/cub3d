/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:39:14 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/02 21:30:57 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	image_load(mlx_texture_t *image, int *color)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (i < image->width * image->height * image->bytes_per_pixel)
	{
		color[j++] = get_rgba(image->pixels[i], image->pixels[i + 1],
				image->pixels[i + 2], image->pixels[i + 3]);
		i += image->bytes_per_pixel;
	}
}

void	check_for_textures(t_game *game)
{
	game->texture->eimage = mlx_load_png(game->texture->epath);
	if (!game->texture->eimage)
		error("NO SUCH TEXTURE\n", game);
	game->texture->nimage = mlx_load_png(game->texture->npath);
	if (!game->texture->nimage)
		error("NO SUCH TEXTURE\n", game);
	game->texture->wimage = mlx_load_png(game->texture->wpath);
	if (!game->texture->wimage)
		error("NO SUCH TEXTURE\n", game);
	game->texture->simage = mlx_load_png(game->texture->spath);
	if (!game->texture->simage)
		error("NO SUCH TEXTURE\n", game);
	if (game->texture->simage->width != 64
		&& game->texture->simage->height != 64)
		error("TEXTURE SIZE MUST BE 64x64\n", game);
	if (game->texture->nimage->width != 64
		&& game->texture->nimage->height != 64)
		error("TEXTURE SIZE MUST BE 64x64\n", game);
	if (game->texture->eimage->width != 64
		&& game->texture->eimage->height != 64)
		error("TEXTURE SIZE MUST BE 64x64\n", game);
	if (game->texture->wimage->width != 64
		&& game->texture->wimage->height != 64)
		error("TEXTURE SIZE MUST BE 64x64\n", game);
}

void	init_images(t_game *game)
{
	game->texture->epath = game->cub->ea;
	game->texture->npath = game->cub->no;
	game->texture->wpath = game->cub->we;
	game->texture->spath = game->cub->so;
	check_for_textures(game);
	game->texture->ccolor = get_rgba(game->cub->c_color[0],
			game->cub->c_color[1], game->cub->c_color[2],
			game->cub->c_color[3]);
	game->texture->fcolor = get_rgba(game->cub->f_color[0],
			game->cub->f_color[1], game->cub->f_color[2],
			game->cub->f_color[3]);
	game->texture->wcolors = malloc(game->texture->wimage->width
			* game->texture->wimage->height * sizeof(int));
	image_load(game->texture->wimage, game->texture->wcolors);
	game->texture->ncolors = malloc(game->texture->nimage->width
			* game->texture->nimage->height * sizeof(int));
	image_load(game->texture->nimage, game->texture->ncolors);
	game->texture->scolors = malloc(game->texture->simage->width
			* game->texture->simage->height * sizeof(int));
	image_load(game->texture->simage, game->texture->scolors);
	game->texture->ecolors = malloc(game->texture->eimage->width
			* game->texture->eimage->height * sizeof(int));
	image_load(game->texture->eimage, game->texture->ecolors);
}
