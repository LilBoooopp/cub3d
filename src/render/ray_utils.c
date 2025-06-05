/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:45:49 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/05 18:11:30 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_back_buffer(t_cub *cub, t_img *back)
// {
// 	back->size = set_vec2i(WIN_WIDTH, WIN_HEIGHT);
// 	back->img = mlx_new_image(cub->mlx, back->size.x, back->size.y);
// 	back->addr = mlx_get_data_addr(back->img, &back->bpp, &back->len,
// 			&back->end);
// 	set_bg(back, cub);
// }

void	*render_thread(void *arg)
{
	t_thrdata	*td;
	t_cub		*cub;
	t_img		*img;

	td = (t_thrdata *)arg;
	cub = td->cub;
	img = td->img;
	cast_rays(cub, img, td->x_start, td->x_end);
	return (NULL);
}

// void	create_map_thread(t_cub *cub, t_img *back, pthread_t *thread)
// {
// 	static t_mapdata	md;

// 	md.cub = cub;
// 	md.img = back;
// 	pthread_create(thread, NULL, render_map, &md);
// }

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
