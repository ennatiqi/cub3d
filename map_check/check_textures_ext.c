/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:59:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/02 20:56:26 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	f(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	if (!game->cub->f)
		game->cub->f = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	c(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	if (!game->cub->c)
		game->cub->c = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}
