/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:43:08 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 17:18:28 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_map	*init_map(void)
{
	t_map	*map;
	int		i;
	int		j;

	map = malloc(sizeof(t_map));
	i = 0;
	map->sizex = 10;
	map->sizey = 10;
	map->map = malloc(sizeof(int) * map->sizey);
	while (i < map->sizey)
	{
		map->map[i] = malloc(sizeof(int) * map->sizex);
		j = 0;
		while (j < map->sizex)
		{
			if (i == 0 || i == map->sizey - 1 || j == 0 || j == map->sizex - 1)
				map->map[i][j] = 1;
			else
				map->map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (map);
}


int	init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, 1280, 1024, "Cub3D");
	cub->map = init_map();
	ft_print_inttable(cub->map->map, cub->map->sizey, cub->map->sizex);
	printf("debug1");
	return (1);
}
