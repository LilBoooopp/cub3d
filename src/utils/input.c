/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:28:25 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/14 15:34:45 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_input(int keycode, t_cub *cub)
{
	if (keycode == key_ESC)
		close_window(cub);
	else if (keycode == key_W)
		move_forward(&cub->player);
	else if (keycode == key_S)
		move_backward(&cub->player);
	else if (keycode == key_D)
		move_right(&cub->player);
	else if (keycode == key_A)
		move_left(&cub->player);
	else if (keycode == key_LEFT)
		rotate(&cub->player, -ROT_SPEED);
	else if (keycode == key_RIGHT)
		rotate(&cub->player, ROT_SPEED);
	printf("player x: %f, y: %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("player dirx: %f, diry: %f\n", cub->player.dir.x, cub->player.dir.y);
	return (0);
}
