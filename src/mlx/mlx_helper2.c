/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:13:56 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 23:02:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	scale_size(t_cub *cub, t_img src, double scale)
{
	t_img	new;
	t_vec2	idx;
	t_vec2	src_p;
	int		color;

	new = make_image(cub, set_vec2(src.size.x * scale, src.size.y * scale), 0x00000000);
	idx.y = 0;
	while (idx.y < new.size.y)
	{
		idx.x = 0;
		while (idx.x < new.size.x)
		{
			src_p.x = idx.x / scale;
			src_p.y = idx.y / scale;
			color = get_pixel(&src, set_vec2(src_p.x, src_p.y));
			my_mlx_pixel_put(&new, idx.x, idx.y, color);
			idx.x++;
		}
		idx.y++;
	}
	return (new);
}

static void	copy_trans_row(t_img *src, t_img *dst, t_vec2 pos, int y)
{
	int				sbpp;
	int				slen;
	int				x;
	char			*sp;
	unsigned int	color;

	sbpp = src->bpp;
	slen = src->len;
	sp = src->addr;
	x = -1;
	while (++x < src->size.x)
	{
		color = *(unsigned int *)(sp
				+ y * slen
				+ x * (sbpp / 8));
		if ((color && 0xFF000000) != 0x00000000)
		{
			*(unsigned int *)(dst->addr
					+ ((int)pos.y + y) * dst->len
					+ ((int)pos.x + x) * (dst->bpp / 8)) = color;
		}
	}
}

void	draw_image_transparent(t_img *src, t_img *dst, t_vec2 pos)
{
	int	y;

	y = -1;
	while (++y < src->size.y)
		copy_trans_row(src, dst, pos, y);
}

t_img	setup_xpm(t_cub *c, char *xpm)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(c->mlx, xpm, &img.size.x, &img.size.y);
	if (!img.img)
	{
		img.img = NULL;
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.end);
	return (img);
}
