/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:28:03 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/01 14:57:26 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	no(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 2, ft_strlen(str));
	game->cub->NO = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	so(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 2, ft_strlen(str));
	game->cub->SO = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	we(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 2, ft_strlen(str));
	game->cub->WE = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

void	ea(char *str, t_game *game)
{
	char	*sub;

	sub = ft_substr(str, 2, ft_strlen(str));
	game->cub->EA = ft_strtrim(sub, " \n");
	free(sub);
	game->cub->check_tex++;
}

int	check_for_map(char *s, t_cub *cub, t_game *game)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (str[0] == 'N' && str[1] == 'O' && (str[2] == 32))
		no(str, game);
	else if (str[0] == 'S' && str[1] == 'O' && (str[2] == 32))
		so(str, game);
	else if (str[0] == 'W' && str[1] == 'E' && (str[2] == 32))
		we(str, game);
	else if (str[0] == 'E' && str[1] == 'A' && (str[2] == 32))
		ea(str, game);
	else if (str[0] == 'F' && str[1] == 32)
		f(str, game);
	else if (str[0] == 'C' && str[1] == 32)
		c(str, game);
	else if (ft_isalnum(str[0]))
	{
		free(str);
		error("UNKNOWN ASSET\n", game);
	}
	free(str);
	if (cub->check_tex == 6)
		return (0);
	return (1);
}
