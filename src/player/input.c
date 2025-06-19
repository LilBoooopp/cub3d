/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:28:25 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/19 17:04:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	smooth_input(t_cub *cub)
{
	double	lin;
	double	rot;

	lin = MOVE_SPEED * cub->delta;
	rot = ROT_SPEED * cub->delta;
	if (cub->keys[KEY_ESC])
		close_window(cub);
	if (cub->keys[KEY_W])
		move_forward(&cub->player, cub->map, lin);
	if (cub->keys[KEY_S])
		move_backward(&cub->player, cub->map, lin);
	if (cub->keys[KEY_A])
		move_left(&cub->player, cub->map, lin);
	if (cub->keys[KEY_D])
		move_right(&cub->player, cub->map, lin);
	if (cub->keys[KEY_LEFT])
		rotate(&cub->player, -rot);
	if (cub->keys[KEY_RIGHT])
		rotate(&cub->player, rot);
	// printf("player x: %f, y: %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("player dirx: %f, diry: %f\n", cub->player.dir.x, cub->player.dir.y);
	printf("player planex: %f, planey: %f\n", cub->player.plane.x, 
		cub->player.plane.y);
}

int	handle_keyrelease(int kc, t_cub *cub)
{
	if (kc < 70000)
		cub->keys[kc] = false;
	return (0);
}

void	set_anim_state(t_cub *cub, int state)
{
	if (state == SHOOT)
	{
		cub->hud.anim_state = SHOOT;
		cub->hud.current_frame = 0;
		cub->hud.frame_timer = 0.0;
		cub->hud.frame_count = 4;
		cub->hud.frame_duration = 0.075;
	}
	else if (state == RELOAD)
	{
		cub->hud.anim_state = RELOAD;
		cub->hud.current_frame = 0;
		cub->hud.frame_timer = 0.0;
		cub->hud.frame_count = 9;
		cub->hud.frame_duration = 0.1;
	}
}

int	handle_input(int keycode, t_cub *cub)
{
	if (keycode < 70000)
		cub->keys[keycode] = true;
	if (cub->state == STATE_MENU)
		return (handle_menu(keycode, cub), 0);
	if (cub->keys[KEY_G])
		change_debug(cub);
	if (cub->keys[KEY_M])
		cub->ismap *= -1;
	if (cub->keys[KEY_R])
		if (cub->hud.anim_state == IDLE)
			set_anim_state(cub, RELOAD);
	return (0);
}
