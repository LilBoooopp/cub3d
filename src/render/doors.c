/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:06:41 by pbuet             #+#    #+#             */
/*   Updated: 2025/06/20 14:25:00 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	near_to_door(t_raycast ray, t_cub *c)
{
	double	door_dist;

	if (c->map->map[ray.map.y][ray.map.x] == '1')
		return ;
	if (ray.side == 0)
		door_dist = (ray.map.x - c->player.pos.x
				+ (1 - ray.step.x) / 2.0f) / ray.ray_dir.x;
	else
		door_dist = (ray.map.y - c->player.pos.y
				+ (1 - ray.step.y) / 2.0f) / ray.ray_dir.y;
	if (door_dist < 1.5)
	{
		c->player.near_door = 1;
		c->player.door_x = ray.map.x;
		c->player.door_y = ray.map.y;
	}
	else
		c->player.near_door = 0;
}
