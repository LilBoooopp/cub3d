/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:13:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/15 16:23:13 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	box = make_image(cub, set_vec2(25, 25), 0xFF000000);
	draw_pixels(&box, get_center(&box), box.size, 0x00FF0000);
	angle = atan2(player->dir.y, player->dir.x);
	draw_rotated_image(map, &box, map_pos, angle);
	mlx_destroy_image(cub->mlx, box.img);
	draw_dir(player, map_pos, map);
}

void	render_map(t_cub *cub, t_img *img, t_player *player)
{
	t_img	map;

	map = make_image(cub, set_vec2(300, 300), 0xa55a77);
	draw_player(cub, player, &map);
	drawtoimg(&map, img, set_vec2(980, 0));
}
