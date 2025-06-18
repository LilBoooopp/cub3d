/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:55:03 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 21:40:54 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	compute_mouse_angle(int x, int center)
{
	double	sensitivity;
	double	delta_x;

	sensitivity = 0.002;
	delta_x = x - center;
	return (delta_x * sensitivity);
}

static void	center_mouse(t_cub *cub)
{
	int	center_x;
	int	center_y;

	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	mlx_mouse_move(cub->mlx, cub->mlx_win, center_x, center_y);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	int	center_x;

	(void)y;
	center_x = WIN_WIDTH / 2;
	if (x != center_x)
	{
		rotate(&cub->player, compute_mouse_angle(x, center_x));
		center_mouse(cub);
	}
	return (0);
}

int	mouse_press_handler(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void)x;
	(void)y;
	cub = (t_cub *)param;
	if (button == key_LEFT_CLICK)
		if (cub->hud.anim_state == IDLE)
			set_anim_state(cub, SHOOT);
	return (0);
}
