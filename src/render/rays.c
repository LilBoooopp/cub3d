/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:45:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 16:33:56 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setSideDist(t_raycast *ray, t_player player)
{
	if (ray->step.x == 1)
		ray->side_dist.x = (ray->map.x + 1 - player.pos.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (player.pos.x - ray->map.x) * ray->delta_dist.x;
	if (ray->step.y == 1)
		ray->side_dist.y = (ray->map.y + 1 - player.pos.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (player.pos.y - ray->map.y) * ray->delta_dist.y;
}

t_vec2i	set_raydir(t_raycast ray)
{
	t_vec2i	new;

	if (ray.ray_dir.x > 0)
		new.x = 1;
	else
		new.x = -1;
	if (ray.ray_dir.y > 0)
		new.y = 1;
	else
		new.y = -1;
	return (new);
}

void	cast_rays(t_cub *cub)
{
	t_raycast	ray;
	t_player	*player;
	int			x;

	x = 0;
	player = &cub->player;
	while (x < WIN_WIDTH)
	{
		ray.cam_x = 2 * x / (double)WIN_WIDTH - 1;
		ray.ray_dir = vec2_add(player->dir, set_vec2(player->plane.x
					* ray.cam_x, player->plane.y * ray.cam_x));
		ray.map = vecdtoi(player->pos);
		ray.delta_dist = set_vec2(fabs(1.0 / ray.ray_dir.x),
				fabs(1.0 / ray.ray_dir.y));
		ray.step = set_raydir(ray);
		setSideDist(&ray, cub->player);
		x++;
	}
}
