/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:13:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/20 11:08:51 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_dir(t_player *p, t_vec2 map_pos, t_img *map)
{
	t_vec2	end;

	end.x = map_pos.x + p->dir.x * 100;
	end.y = map_pos.y + p->dir.y * 100;
	draw_line(map, map_pos, end, 0xFF00FFFF);
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
	draw_pixels(&box, get_center(&box), itovec(box.size), 0xFFFF0000);
	angle = atan2(player->dir.y, player->dir.x);
	draw_rotated_image(map, &box, map_pos, angle);
	mlx_destroy_image(cub->mlx, box.img);
	if (cub->ismap && cub->debug > 1)
		draw_dir(player, map_pos, map);
}

static void	draw_tile(t_cub *c, t_map *m, t_img *map, t_vec2i idx)
{
	int		col;
	bool	visible;

	visible = is_tile_visible(m, c->player.pos, idx);
	if (!m->explored[idx.y][idx.x] && !visible)
		return ;
	if (m->map[idx.y][idx.x] == '1' || m->map[idx.y][idx.x] == 'P')
		col = MAP_WALL;
	else if (m->map[idx.y][idx.x] == '0')
		col = MAP_EMPTY;
	else
		return ;
	if (!visible)
		col = col & 0x44FFFFFF;
	draw_rect(map, set_vec2(idx.x * m->t_size.x, idx.y * m->t_size.y),
		set_vec2(m->t_size.x, m->t_size.y), col);
}

void	init_minimap(t_cub *c, t_map *m, t_img *map)
{
	t_vec2i	idx;

	m->t_size = set_vec2(0.0 + m->screenx / m->sizex,
			0.0 + m->screeny / m->sizey);
	idx.y = -1;
	while (++idx.y < m->sizey)
	{
		idx.x = -1;
		while (++idx.x < m->sizex)
		{
			draw_tile(c, m, map, idx);
		}
	}
}

void	*render_map(t_cub *cub, t_img *img, t_player *player)
{
	init_minimap(cub, cub->map, img);
	draw_player(cub, player, img);
	return (NULL);
}
