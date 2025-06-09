/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 16:40:16 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		y;
	double	step;
	double	tex_pos;

	draw_stripe(ray);
	tex = select_text(ray, c);
	texv.x = compute_tex_x(ray, c, tex);
	y = ray->draw_start;
	step = (double)tex->size.y / (double)ray->line_h;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2.0 + ray->line_h / 2.0) * step;
	while (y < ray->draw_end)
	{
		texv.y = (int)tex_pos;
		tex_pos += step;
		my_mlx_pixel_put(img, x, y, get_pixel(tex, itovec(texv)));
		y++;
	}
}
