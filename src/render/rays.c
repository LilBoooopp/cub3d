/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:45:41 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 01:11:14 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cast_rays(t_cub *cub, t_img *img)
{
	t_raycast	ray;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray.cam_x = 2 * x / (double)WIN_WIDTH - 1;
		x++;
	}
}
