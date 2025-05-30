/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/30 14:37:06 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gets and sets the color of the ceiling and floor.
 * @param back Background t_img
 * @param c t_cub struct
 */
void	set_bg(t_img *back, t_cub *c)
{
	int	r;
	int	g;
	int	b;

	parse_rgbhex(c->texture.c, &r, &g, &b);
	c->texture.ceiling = (r << 16) | (g << 8) | b;
	draw_pixels(back, set_vec2(WIN_WIDTH / 2, WIN_HEIGHT / 4),
		set_vec2(WIN_WIDTH, WIN_HEIGHT / 2), c->texture.ceiling);
	parse_rgbhex(c->texture.f, &r, &g, &b);
	c->texture.floor = (r << 16) | (g << 8) | b;
	draw_pixels(back, set_vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.75),
		set_vec2(WIN_WIDTH, WIN_HEIGHT / 2), c->texture.floor);
}

int	render(t_cub *cub)
{
	t_img	back;

	if (cub->state == STATE_MENU)
		return (draw_menu(cub), 0);
	back.size = set_vec2(WIN_WIDTH, WIN_HEIGHT);
	back.img = mlx_new_image(cub->mlx, back.size.x, back.size.y);
	back.addr = mlx_get_data_addr(back.img, &back.bpp, &back.len, &back.end);
	set_bg(&back, cub);
	cast_rays(cub, &back);
	if (cub->ismap == 1)
		render_map(cub, &back, &cub->player);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, back.img, 0, 0);
	if (cub->debug > 0)
		draw_big_fps(cub);
	mlx_destroy_image(cub->mlx, back.img);
	return (0);
}
