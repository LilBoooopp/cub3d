/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 18:55:55 by cbopp            ###   ########.fr       */
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

static t_img	*select_text(t_raycast *ray, t_cub *c)
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

static int	compute_tex_x(t_raycast *ray, t_cub *c, t_img *tex)
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
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		tex_x = tex->size.x - tex_x - 1;
	return (tex_x);
}

void	draw_texture(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	t_img	*tex;
	t_vec2i	texv;
	int		orig_start;
	double	pos;

	draw_stripe(ray);
	orig_start = ray->draw_start;
	tex = select_text(ray, c);
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
