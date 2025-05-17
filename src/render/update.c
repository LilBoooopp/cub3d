/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:38:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/17 20:49:23 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_debug(t_cub *cub)
{
	if (cub->debug == 1)
		cub->debug = 0;
	else
		cub->debug++;
}

void	draw_debug(t_cub *cub)
{
	char	buf[32];
	int		len;

	len = snprintf(buf, sizeof(buf), "FPS: %d", cub->fps);
	if (len >= 0)
		mlx_string_put(cub->mlx, cub->mlx_win, 10, 10, 0x00FF00, buf);
}

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
	render(cub);
	return (0);
}
