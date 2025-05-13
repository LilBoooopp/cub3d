/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 17:39:58 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	render(t_cub *cub)
{
	t_img	back;

	back.size = set_vec2(WIN_WIDTH, WIN_HEIGHT);
	back.img = mlx_new_image(cub->mlx, back.size.x, back.size.y);
	back.addr = mlx_get_data_addr(back.img, &back.bpp, &back.len, &back.end);
	mlx_set_img(&back, 0xFFFFFF);
	render_map(cub, &back, &cub->player);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, back.img, 0, 0);
	mlx_destroy_image(cub->mlx, back.img);
	return (0);
}
