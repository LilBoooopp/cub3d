/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:45:49 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/16 16:12:35 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_cub *cub, t_raycast *ray, int x)
{
	ray->cam_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir = vec2_add(cub->player.dir, set_vec2(cub->player.plane.x
				* ray->cam_x, cub->player.plane.y * ray->cam_x));
	ray->map = vecdtoi(cub->player.pos);
	ray->delta_dist = set_vec2(
			fabs(1.0 / ray->ray_dir.x), fabs(1.0 / ray->ray_dir.y));
	ray->step = set_raydir(ray);
	set_side_dist(ray, cub->player);
}
