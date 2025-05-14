/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:45:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/14 16:38:07 by cbopp            ###   ########.fr       */
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

static void	perform_dda(t_raycast *ray, t_cub *cub)
{
	ray->hit = 0;
	while (!ray->hit)
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
		if (ray->map.x < 0 || ray->map.x >= cub->map->sizex
			|| ray->map.y < 0 || ray->map.y >= cub->map->sizey)
		{
			ray->hit = 1;
			break ;
		}
		if (cub->map->map[ray->map.y][ray->map.x] > 0)
			ray->hit = 1;
	}
}

static void	draw_stripe(t_img *img, t_raycast *ray, int x)
{
	int	y;

	ray->line_h = (int)(WIN_HEIGHT / ray->perp_dist);
	ray->draw_start = -ray->line_h / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side)
		ray->color = 0x008ea832;
	else
		ray->color = 0x00323ea8;
	y = ray->draw_start;
	while (y < ray->draw_end)
		my_mlx_pixel_put(img, x, y++, ray->color);
}

void	cast_rays(t_cub *cub, t_img *img)
{
	t_raycast	ray;
	t_player	*p;
	int			x;

	x = -1;
	p = &cub->player;
	while (++x < WIN_WIDTH)
	{
		ray.cam_x = 2 * x / (double)WIN_WIDTH - 1;
		ray.ray_dir = vec2_add(p->dir, set_vec2(p->plane.x
					* ray.cam_x, p->plane.y * ray.cam_x));
		ray.map = vecdtoi(p->pos);
		ray.delta_dist = set_vec2(fabs(1.0 / ray.ray_dir.x),
				fabs(1.0 / ray.ray_dir.y));
		ray.step = set_raydir(ray);
		setSideDist(&ray, cub->player);
		perform_dda(&ray, cub);
		if (ray.side == 0)
			ray.perp_dist = ((ray.map.x - p->pos.x + (1 - ray.step.x)
					/ 2) / ray.ray_dir.x) * TILE_SIZE;
		else
			ray.perp_dist = ((ray.map.y - p->pos.y + (1 - ray.step.y)
					/ 2) / ray.ray_dir.y) * TILE_SIZE;
		draw_stripe(img, &ray, x);
	}
}
