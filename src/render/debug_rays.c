/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:08:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/20 17:30:51 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_debug_rays(t_cub *c, t_img *m, t_vec2 pos)
{
	t_raycast	r;
	t_vec2		start;
	t_vec2		dir;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(c, &r, x);
		set_side_dist(&r, c->player);
		perform_dda(&r, c);
		if (r.side == 0)
			r.perp_dist = ((r.map.x - c->player.pos.x
				+ (1 - r.step.x) / 2) / r.ray_dir.x) * TILE_SIZE;
		else
			r.perp_dist = ((r.map.y - c->player.pos.y
				+ (1 - r.step.y) / 2) / r.ray_dir.y) * TILE_SIZE;
		start = set_vec2(pos.x * TILE_SIZE,
				pos.y * TILE_SIZE);
		dir = set_vec2(r.ray_dir.x * r.perp_dist * TILE_SIZE * 20,
				r.ray_dir.y * r.perp_dist * TILE_SIZE * 20);
		draw_line(m, start, vec2_add(start, dir), 0xFF00FF00);
		x += 50;
	}
}
