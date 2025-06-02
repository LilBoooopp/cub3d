/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/02 11:22:39 by cbopp            ###   ########.fr       */
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
	return (tex_x);
}

void	draw_texture(t_cub *c, t_img *img, t_raycast *ray, int x)
{
	t_img	*tex;
	t_vec2	texv;
	int		y;

	draw_stripe(img, ray, x);
	tex = select_text(ray, c);
	texv.x = compute_tex_x(ray, c, tex);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texv.y = (y - ray->draw_start) * tex->size.y / ray->line_h;
		my_mlx_pixel_put(img, x, y, get_pixel(tex, texv));
		y++;

	}
}
