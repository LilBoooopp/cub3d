/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:45:49 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/05 21:45:00 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_back_buffer(t_cub *cub, t_img *back)
{
	back->size = set_vec2i(WIN_WIDTH, WIN_HEIGHT);
	back->img = mlx_new_image(cub->mlx, back->size.x, back->size.y);
	back->addr = mlx_get_data_addr(back->img, &back->bpp, &back->len,
			&back->end);
	set_bg(back, cub);
}

void	finalize_back_buffer(t_cub *cub, t_img *back)
{
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, back->img, 0, 0);
	if (cub->debug > 0)
		draw_big_fps(cub);
	mlx_destroy_image(cub->mlx, back->img);
}

void	join_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	create_map_thread(t_cub *cub, pthread_t *thread, t_mapdata *md)
{
	md->cub = cub;
	pthread_create(thread, NULL, render_map_thread, md);
}

void	init_ray(t_cub *cub, t_raycast *ray, int x)
{
	ray->cam_x = 2.0f * x / (double)WIN_WIDTH - 1.0f;
	ray->ray_dir = vec2_add(cub->player.dir, set_vec2(cub->player.plane.x
				* ray->cam_x, cub->player.plane.y * ray->cam_x));
	ray->map = vecdtoi(cub->player.pos);
	ray->delta_dist = set_vec2(
			fabs(1.0 / ray->ray_dir.x), fabs(1.0 / ray->ray_dir.y));
	ray->step = set_raydir(ray);
	set_side_dist(ray, cub->player);
}
