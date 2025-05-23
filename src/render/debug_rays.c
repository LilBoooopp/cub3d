/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:08:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/23 01:10:50 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_one_ray(t_cub *c, t_img *map, t_vec2 map_pos, int x)
{
	t_raycast	r;
	t_vec2		hit;
	double		pd;

	init_ray(c, &r, x);
	set_side_dist(&r, c->player);
	perform_dda(&r, c);
	if (r.side == 0)
		pd = ((r.map.x - c->player.pos.x
					+ (1 - r.step.x) / 2) / r.ray_dir.x);
	else
		pd = ((r.map.y - c->player.pos.y
					+ (1 - r.step.y) / 2) / r.ray_dir.y);
	hit.x = c->player.pos.x + r.ray_dir.x * pd;
	hit.y = c->player.pos.y + r.ray_dir.y * pd;
	hit.x *= c->map->t_size.x;
	hit.y *= c->map->t_size.y;
	draw_line(map, map_pos, hit, 0xFF00FF00);
}

void	draw_debug_rays(t_cub *c, t_img *m, t_vec2 pos)
{
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		draw_one_ray(c, m, pos, x);
		x += 50;
	}
}
