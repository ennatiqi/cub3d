/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:59:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:00:20 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	F(char *str, t_game *game)
{
	char *sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	game->cub->F = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	C(char *str, t_game *game)
{
	char *sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	game->cub->C = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}
