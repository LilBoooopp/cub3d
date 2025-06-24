/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/24 15:47:46 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	apply_vert_offset(t_cub *c, t_raycast *ray)
// {
// 	int	orig_start;
// 	int	off;

// 	orig_start = ray->draw_start;
// 	off = (int)(c->player.z_pos * (WIN_HEIGHT / 2.0) / MAX_HEIGHT
// 			* JUMP_VIEW_SCALE);
// 	ray->draw_start = orig_start + off;
// 	if (ray->draw_start >= WIN_HEIGHT)
// 		ray->draw_start = WIN_HEIGHT - 1;
// 	ray->draw_end = ray->draw_end + off;
// 	if (ray->draw_end >= WIN_HEIGHT)
// 		ray->draw_end = WIN_HEIGHT - 1;
// 	return (orig_start);
// }

t_img	*select_text(t_raycast *ray, t_cub *c)
{
	if (ray->side == 0 && ray->ray_dir.x > 0)
		return (&c->east);
	else if (ray->side == 0)
		return (&c->west);
	else if (ray->side == 1 && ray->ray_dir.y > 0)
		return (&c->south);
	else
		return (&c->north);
}

int	compute_tex_x(t_raycast *ray, t_cub *c, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = c->player.pos.y + ray->perp_dist * ray->ray_dir.y;
	else
		wall_x = c->player.pos.x + ray->perp_dist * ray->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->size.x);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y > 0))
		tex_x = tex->size.x - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	t_img	*tex;
	t_vec2i	texv;
	int		orig_start;
	double	pos;

	orig_start = ray->draw_start;
	near_to_door(*ray, c);
	if (c->map->map[ray->map.y][ray->map.x] == '1')
		tex = select_text(ray, c);
	else
		tex = &c->doors;
	texv.x = compute_tex_x(ray, c, tex);
	pos = (orig_start - WIN_HEIGHT / 2.0 + ray->line_h / 2.0)
		* ((double)tex->size.y / ray->line_h);
	while (ray->draw_start < ray->draw_end)
	{
		texv.y = (int)pos;
		pos += (double)tex->size.y / ray->line_h;
		my_mlx_pixel_put(img, x, ray->draw_start,
			get_pixel(tex, itovec(texv)));
		ray->draw_start++;
	}
}

static int	get_portal_index(t_cub *c, t_raycast *ray)
{
	int			i;
	double		hx;
	t_player	*p;

	p = &c->player;
	i = 0;
	while (i < 2)
	{
		if (c->portals[i].active
			&& ray->map.x == c->portals[i].map.x
			&& ray->map.x == c->portals[i].map.y
			&& ray->side == c->portals[i].side)
		{
			if (ray->side == 0)
				hx = p->pos.y + ray->perp_dist * ray->ray_dir.y;
			else
				hx = p->pos.x + ray->perp_dist * ray->ray_dir.x;
			hx -= floor(hx);
			if (fabs(hx - c->portals[i].offset) <= PORTAL_SPAN / 2.0)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	draw_texture(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	int	pidx;

	draw_stripe(ray);
	near_to_door(*ray, c);
	pidx = get_portal_index(c, ray);
	if (pidx == 0)
		draw_portal_blue(c, img, ray, x);
	else if (pidx == 1)
		draw_portal_orange(c, img, ray, x);
	else
		draw_wall(c, img, ray, x);
}
