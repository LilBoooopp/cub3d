/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:43:08 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 18:48:01 by cbopp            ###   ########.fr       */
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
	map->map = malloc(sizeof(int *) * (map->sizey));
	while (i < map->sizey)
	{
		map->map[i] = malloc(sizeof(int) * (map->sizex));
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

void	init_player(t_player *player)
{
	player->pos = set_vec2(4, 4);
	player->facing = set_vec2(0, 0);
	player->fov = 120;
}


int	init(t_cub *cub)
{
	cub->map = init_map();
	cub->mlx = mlx_init();
	init_player(&cub->player);
	cub->mlx_win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	ft_print_inttable(cub->map->map, cub->map->sizey, cub->map->sizex);
	printf("debug1");
	return (1);
}
