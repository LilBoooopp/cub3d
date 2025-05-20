/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:13:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/20 15:03:50 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_dir(t_player *p, t_vec2 map_pos, t_img *map)
{
	t_vec2	end;

	end.x = map_pos.x + p->dir.x * 100;
	end.y = map_pos.y + p->dir.y * 100;
	draw_line(map, map_pos, end, 0x0000FFFF);
}

void	draw_player(t_cub *cub, t_player *player, t_img *map)
{
	t_img	box;
	double	angle;
	t_vec2	map_pos;

	map_pos = fix_pos(cub, map, player->pos);
	if (cub->debug >= 2)
		draw_debug_rays(cub, map, map_pos);
	box = make_image(cub, set_vec2(12, 12), 0xFF000000);
	draw_pixels(&box, get_center(&box), box.size, 0xFFFF0000);
	angle = atan2(player->dir.y, player->dir.x);
	draw_rotated_image(map, &box, map_pos, angle);
	mlx_destroy_image(cub->mlx, box.img);
	if (cub->ismap && cub->debug > 1)
		draw_dir(player, map_pos, map);
}

void	init_minimap(t_map *m, t_img *map)
{
	t_vec2	idx;

	m->tile_size = set_vec2(m->screenx / m->sizex, m->screeny / m->sizey);
	idx.y = 0;
	while (idx.y < m->sizey)
	{
		idx.x = 0;
		while (idx.x < m->sizex)
		{
			if (m->map[(int)idx.y][(int)idx.x] == '1')
				draw_pixels(map, vec2_add(vec2_mult(idx, m->tile_size),
					vec2_div(m->tile_size, set_vec2(2, 2))),
					m->tile_size, 0xa58b77);
			if (m->map[(int)idx.y][(int)idx.x] == '0')
				draw_pixels(map, vec2_add(vec2_mult(idx, m->tile_size),
					vec2_div(m->tile_size, set_vec2(2, 2))),
					m->tile_size, 0xa55aFF);
			idx.x += 1;
		}
		idx.y += 1;
	}
}

void	render_map(t_cub *cub, t_img *img, t_player *player)
{
	t_img	map;

	map = make_image(cub, set_vec2(cub->map->screenx,
			cub->map->screeny), 0xa55a77);
	init_minimap(cub->map, &map);
	draw_player(cub, player, &map);
	drawtoimg(&map, img, set_vec2(980, 0));
	mlx_destroy_image(cub->mlx, map.img);
}
