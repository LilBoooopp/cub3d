/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/05 14:02:13 by cbopp            ###   ########.fr       */
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

	parse_rgbhex(c->tex.c, &r, &g, &b);
	c->tex.ceiling = (r << 16) | (g << 8) | b;
	draw_pixels(back, set_vec2(WIN_WIDTH / 2, WIN_HEIGHT / 4),
		set_vec2(WIN_WIDTH, WIN_HEIGHT / 2), c->tex.ceiling);
	parse_rgbhex(c->tex.f, &r, &g, &b);
	c->tex.floor = (r << 16) | (g << 8) | b;
	draw_pixels(back, set_vec2(WIN_WIDTH / 2, WIN_HEIGHT * 0.75),
		set_vec2(WIN_WIDTH, WIN_HEIGHT / 2), c->tex.floor);
}

int	render(t_cub *cub)
{
	pthread_t	threads[NUM_THREADS];
	t_thrdata	td[NUM_THREADS];
	t_img	back;
	int		i;
	int		slice;

	if (cub->state == STATE_MENU)
		return (draw_menu(cub), 0);
	back.size = set_vec2i(WIN_WIDTH, WIN_HEIGHT);
	back.img = mlx_new_image(cub->mlx, back.size.x, back.size.y);
	back.addr = mlx_get_data_addr(back.img, &back.bpp, &back.len, &back.end);
	set_bg(&back, cub);
	slice = WIN_HEIGHT / NUM_THREADS;
	if (cub->ismap == 1)
		render_map(cub, &back, &cub->player);
	i = -1;
	while (++i < NUM_THREADS)
	{
		td[i].cub		= cub;
		td[i].img		= &back;
		td[i].x_start	= i * slice;
		if (i == NUM_THREADS - 1)
			td[i].x_end = WIN_WIDTH;
		else
			td[i].x_end = (i + 1) * slice;
		pthread_create(&threads[i], NULL, render_thread, &td[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, back.img, 0, 0);
	if (cub->debug > 0)
		draw_big_fps(cub);
	mlx_destroy_image(cub->mlx, back.img);
	return (0);
}
