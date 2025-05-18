/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:43:08 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/18 16:53:54 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map	*init_map(void)
{
	t_map	*map;
	int		i, j;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->sizex = 10;
	map->sizey = 10;
	map->map = malloc(sizeof(char *) * (map->sizey + 1));
	if (!map->map)
		return (free(map), NULL);

	for (i = 0; i < map->sizey; i++)
	{
		map->map[i] = malloc(sizeof(char) * (map->sizex + 1));
		if (!map->map[i])
		{
			while (i-- > 0)
				free(map->map[i]);
			free(map->map);
			free(map);
			return (NULL);
		}
		for (j = 0; j < map->sizex; j++)
		{
			if (i == 0 || i == map->sizey - 1 ||
			    j == 0 || j == map->sizex - 1)
				map->map[i][j] = '1';
			else
				map->map[i][j] = '0';
		}
		map->map[i][map->sizex] = '\0';
	}

	map->map[map->sizey] = NULL;
	return (map);
}

void	init_player(t_player *player)
{
	player->pos = set_vec2(4.5, 4.5);
	player->dir = set_vec2(0, -1);
	player->plane = set_vec2(0.5, 0);
}
double gettime(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ((ts.tv_nsec / 1000000000.0)));
}
int	init(t_cub *cub)
{
	cub->map = init_map();
	cub->mlx = mlx_init();
	cub->frame_time = gettime();
	cub->debug = 1;
	cub->state = STATE_MENU;
	cub->menu_sel = 0;
	cub->keys[key_LEFT] = false;
	init_player(&cub->player);
	cub->mlx_win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	ft_print_chartable(cub->map->map);
	return (1);
}
