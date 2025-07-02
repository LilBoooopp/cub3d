/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:10 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 17:07:43 by cbopp            ###   ########.fr       */
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

void	spawn_rays(t_spawn_args *args)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		args->td[i].cub = args->cub;
		args->td[i].img = args->back;
		args->td[i].x_start = i * args->slice;
		if (i == NUM_THREADS - 1)
			args->td[i].x_end = WIN_WIDTH;
		else
			args->td[i].x_end = (i + 1) * args->slice;
		pthread_create(&args->threads[i + 1], NULL, render_thread,
			&args->td[i]);
		i++;
	}
}

void	*render_map_thread(void *arg)
{
	t_mapdata	*md;
	t_img		*mb;

	md = (t_mapdata *)arg;
	mb = &md->img;
	init_minimap(md->cub, md->cub->map, mb);
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
	pthread_t		threads[NUM_THREADS + IS_MAP];
	t_thrdata		td[NUM_THREADS];
	t_mapdata		md;
	t_img			back;
	t_spawn_args	args;

	if (cub->state == STATE_MENU)
		return (draw_menu(cub), 0);
	init_back_buffer(cub, &back);
	md.cub = cub;
	md.img = make_image(cub,
			set_vec2(cub->map->screenx, cub->map->screeny), 0x00000000);
	if (IS_MAP)
		create_map_thread(cub, &threads[0], &md);
	args = setup_args(cub, &back, threads, td);
	args.slice = WIN_WIDTH / NUM_THREADS;
	spawn_rays(&args);
	join_threads(args.threads, NUM_THREADS + IS_MAP);
	draw_image_transparent(&md.img, &back,
		set_vec2((double)WIN_WIDTH - md.img.size.x, 0));
	mlx_destroy_image(cub->mlx, md.img.img);
	if (IS_HUD)
		draw_hud(cub, &back);
	finalize_back_buffer(cub, &back);
	return (0);
}
