/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 19:38:07 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_player(t_img *img, t_player *player)
{
	const t_vec2	size = (t_vec2){100, 100};

	draw_pixels(img, player->pos, size, 0xFF0000);
}

int	render(t_cub *cub)
{
	t_img	img;

	img.size = set_vec2(WIN_WIDTH, WIN_HEIGHT);
	img.img = mlx_new_image(cub->mlx, img.size.x, img.size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len,
			&img.end);
	mlx_set_img(&img, 0xFFFFFF);
	render_player(&img, &cub->player);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, img.img, 0, 0);
	mlx_destroy_image(cub->mlx, img.img);
	return (0);
}
