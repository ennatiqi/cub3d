/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:22:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/07/21 23:28:35 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "MLX/mlx.h"

typedef struct s_cub
{
	int	maplines;
	int	i;
	int	j;
}	t_cub;


//map_check
void	check_the_path(char **map, t_cub *cub);
void	check_the_path_2(char **map, t_cub *cub);
int		name_check(char *name);
int		exiter(void);

//map_reader
int		maplines(char *mapber);
char	**mapreader(char *mapber);

#endif