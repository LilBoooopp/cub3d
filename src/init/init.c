/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:43:08 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/22 17:33:59 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_false(bool *keys)
{
	keys[key_W] = false;
	keys[key_A] = false;
	keys[key_S] = false;
	keys[key_D] = false;
	keys[key_LEFT] = false;
	keys[key_RIGHT] = false;
}

void	init_player(t_player *player, t_map *map)
{
	(void)map;
	player->pos = set_vec2(map->playerx, map->playery);
	player->dir = set_vec2(0, -1);
	player->plane = set_vec2(0.8, 0);
}
double gettime(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ((ts.tv_nsec / 1000000000.0)));
}
int	init(t_cub *cub, char ** v)
{
	cub->map = ini_map(cub, v);
	if (!cub->map)
		return (1);
	cub->map->screenx = 300;
	cub->map->screeny = 300;
	cub->mlx = mlx_init();
	cub->frame_time = gettime();
	cub->debug = 1;
	cub->state = STATE_MENU;
	cub->menu_sel = 0;
	cub->ismap = -1;
	set_false(cub->keys);
	init_player(&cub->player, cub->map);
	cub->mlx_win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	return (0);
}
