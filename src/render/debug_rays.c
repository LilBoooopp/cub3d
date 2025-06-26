/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:08:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/26 19:29:00 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	help_dda(t_raycast *ray)
{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
}

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
