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
    color = malloc(image->width * image->height * sizeof(int));

    int i = 0;
    int j = 0;
    while (i < image->width * image->height * image->bytes_per_pixel)
    {
        // int get_rgba(int r, int g, int b, int a)
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

    // game->texture->Eimage = mlx_load_png(game->texture->Epath);
    // game->texture->Nimage = mlx_load_png(game->texture->Npath);
    // game->texture->Wimage = mlx_load_png(game->texture->Wpath);
    // game->texture->Simage = mlx_load_png(game->texture->Spath);

    // image_load(game->texture->Wimage, game->texture->Wcolors);
    // image_load(game->texture->Nimage, game->texture->Ncolors);
    // image_load(game->texture->Simage, game->texture->Scolors);
    // image_load(game->texture->Eimage, game->texture->Ecolors);

    
    //void mlx_delete_texture(mlx_texture_t* texture);
}
