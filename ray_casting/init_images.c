/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:39:14 by rennatiq          #+#    #+#             */
/*   Updated: 2023/10/21 09:45:57 by rennatiq         ###   ########.fr       */
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

void    init_images(t_game *game)
{
    game->texture = malloc(sizeof(t_texture));
    game->texture->Epath = "./textures/E.png";
    game->texture->Npath = "./textures/N.png";
    game->texture->Wpath = "./textures/W.png";
    game->texture->Spath = "./textures/S.png";

    game->texture->Eimage = mlx_load_png(game->texture->Epath);
    game->texture->Nimage = mlx_load_png(game->texture->Npath);
    game->texture->Wimage = mlx_load_png(game->texture->Wpath);
    game->texture->Simage = mlx_load_png(game->texture->Spath);

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
