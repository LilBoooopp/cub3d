/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:28:25 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/14 16:36:02 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	smooth_input(t_cub *cub)
// {
// 	if (cub->keys[key_ESC])
// 		close_window(cub);
// 	if (cub->keys[key_W])
// 		move_forward(&cub->player, cub->map);
// 	if (cub->keys[key_S])
// 		move_backward(&cub->player, cub->map);
// 	if (cub->keys[key_A])
// 		move_left(&cub->player, cub->map);
// 	if (cub->keys[key_D])
// 		move_right(&cub->player, cub->map);
// 	if (cub->keys[key_LEFT])
// 		rotate(&cub->player, -ROT_SPEED);
// 	if (cub->keys[key_RIGHT])
// 		rotate(&cub->player, ROT_SPEED);
// }

// int	handle_keypress(int kc, t_cub *cub)
// {
// 	cub->keys[kc] = true;
// 	return (0);
// }

// int	handle_keyrelease(int kc, t_cub *cub)
// {
// 	cub->keys[kc] = false;
// 	return (0);
// }

int	handle_input(int keycode, t_cub *cub)
{
	if (keycode == key_ESC)
		close_window(cub);
	if (keycode == key_W)
		move_forward(&cub->player, cub->map);
	if (keycode == key_S)
		move_backward(&cub->player, cub->map);
	if (keycode == key_A)
		move_left(&cub->player, cub->map);
	if (keycode == key_D)
		move_right(&cub->player, cub->map);
	if (keycode == key_LEFT)
		rotate(&cub->player, -ROT_SPEED);
	if (keycode == key_RIGHT)
		rotate(&cub->player, ROT_SPEED);
	printf("player x: %f, y: %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("player dirx: %f, diry: %f\n", cub->player.dir.x, cub->player.dir.y);
	return (0);
}
