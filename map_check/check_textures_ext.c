/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_ext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:59:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:57:14 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	f(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	game->cub->F = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	c(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 1, ft_strlen(str));
	game->cub->C = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}
