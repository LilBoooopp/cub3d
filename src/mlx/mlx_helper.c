/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:58:22 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/02 23:44:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_img *img, t_vec2 pos)
{
	char	*src_px;
	int		color;

	if (!img || !img->addr || !is_in_bounds(img, pos))
		return (0xFF000000);
	src_px = img->addr + ((int)pos.y * img->len + (int)pos.x * (img->bpp / 8));
	color = *(unsigned int *)src_px;
	return (color);
}

void	mlx_set_img(t_img *img, unsigned int color)
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

	p.y = -size.y / 2;
	while (p.y <= size.y / 2)
	{
		p.x = -size.x / 2;
		while (p.x <= size.x / 2)
		{
			my_mlx_pixel_put(img, p.x + pos.x, p.y + pos.y, color);
			p.x++;
		}
		p.y++;
	}
}

t_img	make_image(t_cub *cub, t_vec2 size, int color)
{
	t_img	new;

	new.size = vecdtoi(size);
	new.img = mlx_new_image(cub->mlx, new.size.x, new.size.y);
	new.addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.end);
	mlx_set_img(&new, color);
	return (new);
}
