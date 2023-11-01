/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:39:14 by rennatiq          #+#    #+#             */
/*   Updated: 2023/11/01 09:38:20 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    image_load(mlx_texture_t *image, int *color)
{
    unsigned int i = 0;
    int j = 0;
    while (i < image->width * image->height * image->bytes_per_pixel)
    {
        color[j++] = get_rgba(image->pixels[i], image->pixels[i + 1], image->pixels[i + 2], image->pixels[i + 3]);
        i += image->bytes_per_pixel;
    }
    
}

void error_image(char *str)
{
	while (*str)
		write(2, str++, 1);
	
	exit (1);
}

void    init_images(t_game *game)
{

	//TODO check if this is right
    // game->texture = malloc(sizeof(t_texture));
    game->texture->Epath = game->cub->EA;
    game->texture->Npath = game->cub->NO;
    game->texture->Wpath = game->cub->WE;
    game->texture->Spath = game->cub->SO;

    game->texture->Eimage = mlx_load_png(game->texture->Epath);
	if (!game->texture->Eimage)
		error_image("NO SUCH TEXTURE\n");
    game->texture->Nimage = mlx_load_png(game->texture->Npath);
	if (!game->texture->Nimage)
		error_image("NO SUCH TEXTURE\n");
    game->texture->Wimage = mlx_load_png(game->texture->Wpath);
	if (!game->texture->Wimage)
		error_image("NO SUCH TEXTURE\n");
    game->texture->Simage = mlx_load_png(game->texture->Spath);
	if (!game->texture->Simage)
		error_image("NO SUCH TEXTURE\n");

	if (game->texture->Simage->width != 64 && game->texture->Simage->height != 64)
		error_image("TEXTURE SIZE MUST BE 64x64\n");

    game->texture->Ccolor = get_rgba(game->cub->c_color[0],game->cub->c_color[1],game->cub->c_color[2],game->cub->c_color[3]);
    game->texture->Fcolor = get_rgba(game->cub->f_color[0],game->cub->f_color[1],game->cub->f_color[2],game->cub->f_color[3]);

    game->texture->Wcolors = malloc(game->texture->Wimage->width * game->texture->Wimage->height * sizeof(int));
    image_load(game->texture->Wimage, game->texture->Wcolors);

    game->texture->Ncolors = malloc(game->texture->Nimage->width * game->texture->Nimage->height * sizeof(int));
    image_load(game->texture->Nimage, game->texture->Ncolors);
    
    game->texture->Scolors = malloc(game->texture->Simage->width * game->texture->Simage->height * sizeof(int));
    image_load(game->texture->Simage, game->texture->Scolors);
    
    game->texture->Ecolors = malloc(game->texture->Eimage->width * game->texture->Eimage->height * sizeof(int));
    image_load(game->texture->Eimage, game->texture->Ecolors);
}
