/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:28:25 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/05 01:24:45 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	smooth_input(t_cub *cub)
{
	double	lin;
	double	rot;

	lin = MOVE_SPEED * cub->delta;
	rot = ROT_SPEED * cub->delta;
	if (cub->keys[key_ESC])
		close_window(cub);
	if (cub->keys[key_W])
		move_forward(&cub->player, cub->map, lin);
	if (cub->keys[key_S])
		move_backward(&cub->player, cub->map, lin);
	if (cub->keys[key_A])
		move_left(&cub->player, cub->map, lin);
	if (cub->keys[key_D])
		move_right(&cub->player, cub->map, lin);
	if (cub->keys[key_LEFT])
		rotate(&cub->player, -rot);
	if (cub->keys[key_RIGHT])
		rotate(&cub->player, rot);
}

int	handle_keyrelease(int kc, t_cub *cub)
{
	if (kc < 70000)
		cub->keys[kc] = false;
	return (0);
}

int	handle_input(int keycode, t_cub *cub)
{
	if (keycode < 70000)
		cub->keys[keycode] = true;
	if (cub->state == STATE_MENU)
		return (handle_menu(keycode, cub), 0);
	if (cub->keys[key_G])
		change_debug(cub);
	if (cub->keys[key_M])
		cub->ismap *= -1;
	return (0);
}
// printf("player x: %f, y: %f\n", cub->player.pos.x, cub->player.pos.y);
// printf("player dirx: %f, diry: %f\n", cub->player.dir.x, cub->player.dir.y);
// printf("player planex: %f, planey: %f\n", cub->player.plane.x, 
//cub->player.plane.y);
