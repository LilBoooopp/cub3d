/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:58:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 19:31:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	mlx_set_img(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->size.y)
	{
		x = 0;
		while (x < img->size.x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->size.x || y >= data->size.y)
		return ;
	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixels(t_img *img, t_vec2 pos, t_vec2 size, int color)
{
	t_vec2	p;

	p = set_vec2(0, 0);
	while (p.y < size.y)
	{
		p.x = 0;
		while (p.x < size.x)
		{
			my_mlx_pixel_put(img, p.x + pos.x, p.y + pos.y, color);
			p.x++;
		}
		p.y++;
	}
}
