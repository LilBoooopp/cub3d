/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 15:05:13 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_map(t_cub *cub, t_img *img, t_player *player)
{
	t_vec2			end;
	t_img			box;
	double			angle;

	box.size = set_vec2(50, 50);
	box.img = mlx_new_image(cub->mlx, box.size.x, box.size.y);
	box.addr = mlx_get_data_addr(box.img, &box.bpp, &box.len, &box.end);
	mlx_set_img(&box, 0xFF000000);
	draw_pixels(&box, get_center(&box), box.size, 0x00FF0000);
	end.x = player->pos.x + player->dir.x * 100;
	end.y = player->pos.y + player->dir.y * 100;
	angle = atan2(player->dir.y, player->dir.x);
	draw_rotated_image(img, &box, player->pos, angle);
	mlx_destroy_image(cub->mlx, box.img);
	draw_line(img, player->pos, end, 0x0000FFFF);
}

int	render(t_cub *cub)
{
	t_img	img;

	img.size = set_vec2(WIN_WIDTH, WIN_HEIGHT);
	img.img = mlx_new_image(cub->mlx, img.size.x, img.size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.end);
	mlx_set_img(&img, 0xFFFFFF);
	render_map(cub, &img, &cub->player);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, img.img, 0, 0);
	mlx_destroy_image(cub->mlx, img.img);
	return (0);
}
