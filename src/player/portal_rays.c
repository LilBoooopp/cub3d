/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:14:26 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/23 17:14:13 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_portal_hit(t_portal *p, t_raycast *ray, t_cub *cub)
{
	t_vec2	hit;
	double	delta;

	if (!p->active)
		return (false);
	compute_hit_point(cub, ray, &hit);
	if ((int)hit.x != (int)p->pos.x || (int)hit.y != (int)p->pos.y)
		return (false);
	if (p->normal.x != 0)
		delta = fabs(hit.y - p->pos.y);
	else
		delta = fabs(hit.x - p->pos.x);
	if (delta > (0.6 / 2.0))
		return (false);
	return (true);
}

static void	render_recursive_slice(t_cub *cub, t_img *img, int x,
	t_raycast *ray, int depth)
{
	t_img	tmp;
	int		raw_h;
	int		h;
	int		y_off;

	tmp = make_image(cub, set_vec2(1, WIN_HEIGHT), 0);
	cast_rays_portal(cub, &tmp, x, x + 1, depth - 1);
	raw_h = (int)(WIN_HEIGHT / ray->perp_dist * 0.4);
	if (raw_h > WIN_HEIGHT)
		h = WIN_HEIGHT;
	else if (raw_h < 0)
		h = 0;
	else
		h = raw_h;
	y_off = (WIN_HEIGHT - h) / 2;
	if (y_off < 0)
		y_off = 0;
	if (y_off + h > WIN_HEIGHT)
		h = WIN_HEIGHT - y_off;
	draw_pixels(img, set_vec2(x, y_off), set_vec2(1, h), 0);
	draw_image_transparent(&cub->portal_orange, img, set_vec2(x, y_off));
	mlx_destroy_image(cub->mlx, tmp.img);
}

static void	render_wall_slice(t_cub *cub, t_img *img, t_raycast *ray, int x)
{
	if (ray->hit)
		draw_texture(cub, img, ray, x);
}

void	cast_rays_portal(t_cub *c, t_img *img, int x_start, int x_end,
	int depth)
{
	int			x;
	t_raycast	ray;

	if (depth <= 0)
	{
		cast_rays(c, img, x_start, x_end);
		return ;
	}
	x = x_start;
	while (x < x_end)
	{
		ft_bzero(&ray, sizeof(ray));
		init_ray(c, &ray, x);
		perform_dda(&ray, c);
		if (ray.side == 0)
			ray.perp_dist = (ray.map.x - c->player.pos.x +
				(1 - ray.step.x) / 2.0) / ray.ray_dir.x;
		else
			ray.perp_dist = (ray.map.y - c->player.pos.y +
				(1 - ray.step.y) / 2.0) / ray.ray_dir.y;
		if (is_portal_hit(&c->portal_a, &ray, c))
				render_recursive_slice(c, img, x, &ray, depth);
		else if (is_portal_hit(&c->portal_b, &ray, c))
				render_recursive_slice(c, img, x, &ray, depth);
		else
				render_wall_slice(c, img, &ray, x);
		x++;
	}
}
