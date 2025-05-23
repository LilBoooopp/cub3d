/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:38:14 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/20 17:58:56 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
