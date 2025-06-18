/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:38:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 18:56:09 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	update_jump(t_player *p, double delta)
// {
// 	if (p->is_jumping)
// 	{
// 		p->z_pos += p->z_vel * delta;
// 		p->z_vel -= GRAVITY * delta;
// 		if (p->z_pos <= 0.0)
// 		{
// 			p->z_pos = 0.0;
// 			p->is_jumping = 0;
// 		}
// 	}
// }

int	update(t_cub *cub)
{
	double	now;

	now = gettime();
	cub->delta = now - cub->frame_time;
	cub->frame_time = now;
	if (cub->delta > 0.0)
		cub->fps = (int)(1.0 / cub->delta);
	else
		cub->fps = 0;
	smooth_input(cub);
	render(cub);
	return (0);
}
