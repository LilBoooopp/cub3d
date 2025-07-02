/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:43:08 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 15:38:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_false(bool *keys)
{
	keys[KEY_W] = false;
	keys[KEY_A] = false;
	keys[KEY_S] = false;
	keys[KEY_D] = false;
	keys[KEY_LEFT] = false;
	keys[KEY_RIGHT] = false;
}

void	init_player(t_player *player, t_map *map)
{
	player->pos = set_vec2(map->playerx, map->playery);
	if (map->orientation == 'N')
	{
		player->dir = set_vec2(0, -1);
		player->plane = set_vec2(0.65, 0);
	}
	else if (map->orientation == 'E')
	{
		player->dir = set_vec2(1, 0);
		player->plane = set_vec2(0, 0.6);
	}
	else if (map->orientation == 'S')
	{
		player->dir = set_vec2(0, 1);
		player->plane = set_vec2(-0.65, 0);
	}
	else
	{
		player->dir = set_vec2(-1, 0);
		player->plane = set_vec2(0, -0.6);
	}
}

double	gettime(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ((ts.tv_nsec / 1000000000.0)));
}

int	init(t_cub *cub, char **v)
{
	cub->map = ini_map(cub, v);
	if (!cub->map)
		return (1);
	cub->map->screenx = 300;
	cub->map->screeny = 300;
	cub->mlx = NULL;
	cub->mlx = mlx_init();
	cub->frame_time = gettime();
	cub->debug = 1;
	cub->state = STATE_MENU;
	cub->menu_sel = 0;
	cub->ismap = -1;
	cub->player.near_door = 0;
	cub->player.near_c_door = 0;
	if (open_xpm(cub))
		return (free_xpm(cub, 0), 1);
	set_false(cub->keys);
	init_player(&cub->player, cub->map);
	if (init_hud(cub, &cub->hud))
		return (free_xpm(cub, 1), 1);
	cub->mlx_win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	return (0);
}
