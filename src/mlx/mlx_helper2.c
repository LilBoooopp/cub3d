/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:13:56 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 17:34:15 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (color >> 24)
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
