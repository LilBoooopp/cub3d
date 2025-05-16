/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:33:43 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/16 16:44:05 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *img, t_vec2 start, t_vec2 end, int color)
{
	t_vec2	d;
	int		steps;
	t_vec2	inc;
	t_vec2	pos;
	int		i;

	d = set_vec2(end.x - start.x, end.y - start.y);
	steps = fmax(fabs(d.x), fabs(d.y));
	inc = set_vec2(d.x / steps, d.y / steps);
	pos = set_vec2(start.x, start.y);
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(img, (int)pos.x, (int)pos.y, color);
		pos.x += inc.x;
		pos.y += inc.y;
		i++;
	}
}

t_vec2	rotate_point(t_vec2 rel, double angle)
{
	t_vec2	result;

	result.x = rel.x * cos(angle) - rel.y * sin(angle);
	result.y = rel.x * sin(angle) + rel.y * cos(angle);
	return (result);
}

t_vec2	get_rotated_position(t_vec2 center, t_vec2 local, double angle)
{
	t_vec2	relative;
	t_vec2	rotated;

	relative = set_vec2(local.x - center.x, local.y - center.y);
	rotated = rotate_point(relative, angle);
	return (rotated);
}

void	draw_rotated_image(t_img *t, t_img *s, t_vec2 pos,
		double ang)
{
	int		x;
	int		y;
	int		col;
	t_vec2	center;
	t_vec2	srcp;

	center = get_center(s);
	y = -(int)s->size.x;
	while (y <= (int)s->size.x)
	{
		x = -(int)s->size.x;
		while (x <= (int)s->size.x)
		{
			srcp = rotate_point(set_vec2(x, y), -ang);
			srcp.x += center.x;
			srcp.y += center.y;
			col = get_pixel(s, srcp);
			if (is_in_bounds(s, srcp)
				&& (unsigned int)col != 0xFF000000)
				my_mlx_pixel_put(t, pos.x + x, pos.y + y, col);
			x++;
		}
		y++;
	}
}

void	drawtoimg(t_img *src, t_img *dst, t_vec2 pos)
{
	t_vec2	idx;
	int		col;

	idx.y = 0;
	while (idx.y < src->size.y && idx.y < dst->size.y)
	{
		idx.x = 0;
		while (idx.x < src->size.x && idx.x < dst->size.y)
		{
			col = get_pixel(src, idx);
			if (is_in_bounds(src, idx)
				&& (unsigned int)col != 0xFF000000)
				my_mlx_pixel_put(dst, pos.x + idx.x, pos.y + idx.y, col);
			idx.x++;
		}
		idx.y++;
	}
}
