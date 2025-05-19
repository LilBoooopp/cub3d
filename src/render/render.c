/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/19 14:42:36 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_cub *cub)
{
	t_img	back;

	if (cub->state == STATE_MENU)
		return (draw_menu(cub), 0);
	back.size = set_vec2(WIN_WIDTH, WIN_HEIGHT);
	back.img = mlx_new_image(cub->mlx, back.size.x, back.size.y);
	back.addr = mlx_get_data_addr(back.img, &back.bpp, &back.len, &back.end);
	mlx_set_img(&back, 0xFFFFFF);
	cast_rays(cub, &back);
	if (cub->ismap == 1)
		render_map(cub, &back, &cub->player);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, back.img, 0, 0);
	if (cub->debug > 0)
		draw_big_fps(cub);
	mlx_destroy_image(cub->mlx, back.img);
	return (0);
}
