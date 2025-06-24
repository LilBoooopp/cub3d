/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_place.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:09:54 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/23 17:08:57 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_hit_point(t_cub *cub, t_raycast *ray, t_vec2 *hit)
{
	hit->x = cub->player.pos.x + ray->perp_dist * ray->ray_dir.x;
	hit->y = cub->player.pos.y + ray->perp_dist * ray->ray_dir.y;
}

static void	set_portal_properties(t_cub *cub, t_portal *portal, t_vec2 hit,
	t_raycast *ray)
{
	portal->pos = hit;
	if (ray->side == 0)
	{
		portal->normal.y = 0;
		if (ray->ray_dir.x > 0)
			portal->normal.x = -1;
		else
			portal->normal.x = 1;
	}
	else
	{
		portal->normal.x = 0;
		if (ray->ray_dir.y > 0)
			portal->normal.y = -1;
		else
			portal->normal.y = 1;
	}
	if (portal == &cub->portal_a)
		portal->texture = &cub->portal_orange;
	else
		portal->texture = &cub->portal_blue;
}

static void	compute_perp_dist(t_raycast *ray, t_cub *cub)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map.x - cub->player.pos.x +
			(1 - ray->step.x) / 2.0) / ray->ray_dir.x;
	else
		ray->perp_dist = (ray->map.y - cub->player.pos.y +
			(1 - ray->step.y) / 2.0) / ray->ray_dir.y;
}

/**
 * @brief Shoot a ray form camera center, place 'portal' at hit
 */
void	place_portal_at_center(t_cub *cub, t_portal *p)
{
	t_raycast	ray;
	t_vec2		hit;

	ft_bzero(&ray, sizeof(ray));
	init_ray(cub, &ray, WIN_WIDTH / 2);
	perform_dda(&ray, cub);
	compute_perp_dist(&ray, cub);
	compute_hit_point(cub, &ray, &hit);
	set_portal_properties(cub, p, hit, &ray);
}
