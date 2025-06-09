/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:01:04 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 18:41:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_spawn_args	setup_args(t_cub *c, t_img *back, pthread_t *threads,
	t_thrdata *td)
{
	t_spawn_args	arg;

	arg.cub = c;
	arg.back = back;
	arg.threads = threads;
	arg.td = td;
	return (arg);
}

void	draw_big_fps(t_cub *cub)
{
	char	buf[16];
	int		i;
	int		scale;
	int		x;

	scale = 3;
	snprintf(buf, sizeof(buf), "%03d", cub->fps);
	x = 10;
	i = 0;
	while (buf[i])
	{
		draw_digit(cub, buf[i], set_vec2i(x, 10), scale);
		x += 6 * scale;
		i++;
	}
}

void	change_debug(t_cub *cub)
{
	if (cub->debug == 2)
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
