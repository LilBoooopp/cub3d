/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 17:19:21 by cbopp            ###   ########.fr       */
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

void	spawn_rays(t_cub *cub, t_img *back, int slice, pthread_t *threads,
		t_thrdata *td)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		td[i].cub = cub;
		td[i].img = back;
		td[i].x_start = i * slice;
		if (i == NUM_THREADS - 1)
			td[i].x_end = WIN_WIDTH;
		else
			td[i].x_end = (i + 1) * slice;
		pthread_create(&threads[i + 1], NULL, render_thread, &td[i]);
		i++;
	}
}

void	*render_map_thread(void *arg)
{
	t_mapdata	*md;
	t_img		*mb;

	md = (t_mapdata *)arg;
	mb = &md->img;
	init_minimap(md->cub->map, mb);
	draw_player(md->cub, &md->cub->player, mb);
	return (NULL);
}

void	*render_thread(void *arg)
{
	t_thrdata	*td;

	td = (t_thrdata *)arg;
	cast_rays(td->cub, td->img, td->x_start, td->x_end);
	return (NULL);
}

int	render(t_cub *cub)
{
	pthread_t	threads[NUM_THREADS + 1];
	t_thrdata	td[NUM_THREADS];
	t_mapdata	md;
	t_img		back;
	int			slice;

	if (cub->state == STATE_MENU)
		return (draw_menu(cub), 0);
	init_back_buffer(cub, &back);
	md.cub = cub;
	md.img = make_image(cub,
			set_vec2(cub->map->screenx, cub->map->screeny), 0x00000000);
	slice = WIN_WIDTH / NUM_THREADS;
	create_map_thread(cub, &threads[0], &md);
	spawn_rays(cub, &back, slice, threads, td);
	join_threads(threads, NUM_THREADS + 1);
	draw_image_transparent(&md.img, &back,
		set_vec2((double)WIN_WIDTH - md.img.size.x, 0));
	mlx_destroy_image(cub->mlx, &md.img);
	finalize_back_buffer(cub, &back);
	return (0);
}
