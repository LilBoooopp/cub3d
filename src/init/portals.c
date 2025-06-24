/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:12:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/24 15:48:16 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_portals(t_cub *cub)
{
	cub->portal_blue = setup_xpm(cub, "resources/portal_blue.xpm");
	cub->portal_orange = setup_xpm(cub, "resources/portal_orange.xpm");
	cub->portals[0].active = false;
	cub->portals[1].active = false;
}

void	shoot_portals(t_cub *cub, int idx)
{
	t_raycast	ray;
	t_player	*p;
	double		hit_x;

	p = &cub->player;
	init_ray(cub, &ray, WIN_WIDTH / 2);
	perform_dda(&ray, cub);
	if (!ray.hit)
		return ;
	if (ray.side == 0)
		ray.perp_dist = (ray.map.x - p->pos.x + (1 - ray.step.x) / 2.0)
			/ ray.ray_dir.x;
	else
		ray.perp_dist = (ray.map.y - p->pos.y + (1 - ray.step.y) / 2.0)
			/ ray.ray_dir.y;
	if (ray.side == 0)
		hit_x = p->pos.y + ray.perp_dist * ray.ray_dir.y;
	else
		hit_x = p->pos.x + ray.perp_dist * ray.ray_dir.x;
	hit_x -= floor(hit_x);
	cub->portals[idx].active = true;
	cub->portals[idx].map.x = ray.map.x;
	cub->portals[idx].map.y = ray.map.y;
	cub->portals[idx].side = ray.side;
	cub->portals[idx].offset = hit_x;
}

void	draw_portal_blue(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	t_img			*ptex;
	t_vec2i			texv;
	int				start;
	double			pos;
	unsigned int	col;

	ptex = &c->portal_blue;
	start = ray->draw_start;
	texv.x = compute_tex_x(ray, c, ptex);
	pos = (start - WIN_HEIGHT / 2.0 + ray->line_h / 2.0)
		* ((double)ptex->size.y / ray->line_h);
	while (ray->draw_start < ray->draw_end)
	{
		texv.y = (int)pos;
		pos += (double)ptex->size.y / ray->line_h;
		col = get_pixel(ptex, itovec(texv));
		if ((col & 0xFF000000) != 0x00000000)
			my_mlx_pixel_put(img, x, ray->draw_start, col);
		else
			my_mlx_pixel_put(img, x, ray->draw_start,
				get_pixel(select_text(ray, c), itovec(texv)));
		ray->draw_start++;
	}
}

void	draw_portal_orange(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	t_img			*ptex;
	t_vec2i			texv;
	int				start;
	double			pos;
	unsigned int	col;

	ptex = &c->portal_orange;
	start = ray->draw_start;
	texv.x = compute_tex_x(ray, c, ptex);
	pos = (start - WIN_HEIGHT / 2.0 + ray->line_h / 2.0)
		* ((double)ptex->size.y / ray->line_h);
	while (ray->draw_start < ray->draw_end)
	{
		texv.y = (int)pos;
		pos += (double)ptex->size.y / ray->line_h;
		col = get_pixel(ptex, itovec(texv));
		if ((col & 0xFF000000) != 0x00000000)
			my_mlx_pixel_put(img, x, ray->draw_start, col);
		else
			my_mlx_pixel_put(img, x, ray->draw_start,
				get_pixel(select_text(ray, c), itovec(texv)));
		ray->draw_start++;
	}
}
