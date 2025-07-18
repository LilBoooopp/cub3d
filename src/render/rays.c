/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:45:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/03 18:14:22 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_side_dist(t_raycast *ray, t_player player)
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

t_vec2i	set_raydir(t_raycast *ray)
{
	t_vec2i	new;

	if (ray->ray_dir.x > 0)
		new.x = 1;
	else
		new.x = -1;
	if (ray->ray_dir.y > 0)
		new.y = 1;
	else
		new.y = -1;
	return (new);
}

void	perform_dda(t_raycast *ray, t_cub *cub)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (cub->map->map[ray->map.y][ray->map.x] == 'O')
		{
			cub->player.door_x = ray->map.x;
			cub->player.door_y = ray->map.y;
			cub->player.near_c_door = 1;
		}
		help_dda(ray);
		if (ray->map.x < 0 || ray->map.x >= cub->map->sizex
			|| ray->map.y < 0 || ray->map.y >= cub->map->sizey)
		{
			ray->hit = 1;
			break ;
		}
		if (cub->map->map[ray->map.y][ray->map.x] == '1'
			|| cub->map->map[ray->map.y][ray->map.x] == 'P')
			ray->hit = 1;
	}
}

void	draw_stripe(t_raycast *ray)
{
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
}

void	cast_rays(t_cub *cub, t_img *img, int x_start, int x_end)
{
	t_raycast	ray;
	t_player	*p;
	int			x;

	p = &cub->player;
	x = x_start - 1;
	cub->player.near_door = 0;
	cub->player.near_c_door = 0;
	while (++x < x_end)
	{
		ft_bzero(&ray, sizeof(t_raycast));
		init_ray(cub, &ray, x);
		perform_dda(&ray, cub);
		near_to_door(ray, cub);
		if (ray.side == 0)
			ray.perp_dist = ((ray.map.x - p->pos.x + (1 - ray.step.x)
						/ 2.0f) / ray.ray_dir.x);
		else
			ray.perp_dist = ((ray.map.y - p->pos.y + (1 - ray.step.y)
						/ 2.0f) / ray.ray_dir.y);
		if (ray.hit)
			draw_texture(cub, img, &ray, x);
	}
}
