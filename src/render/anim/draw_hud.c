/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:30:57 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 22:10:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	get_current_frame(t_hud *hud)
{
	if (hud->anim_state == SHOOT)
		return (hud->anim_shoot[hud->current_frame]);
	if (hud->anim_state == RELOAD)
		return (hud->anim_reload[hud->current_frame]);
	return (hud->anim_idle);
}

static void	advance_anim_frame(t_hud *hud, double now)
{
	if (now - hud->frame_timer >= hud->frame_duration)
	{
		hud->current_frame++;
		hud->frame_timer = now;
	}
	if (hud->anim_state != IDLE && hud->current_frame >= hud->frame_count)
	{
		hud->anim_state = IDLE;
		hud->current_frame = 0;
	}
}

static t_img	anim_handler(t_cub *c, t_img *dst)
{
	double	now;

	(void)dst;
	now = gettime();
	advance_anim_frame(&c->hud, now);
	return (get_current_frame(&c->hud));
}

void	draw_hud(t_cub *cub, t_img *dst)
{
	t_img	img;
	t_vec2	pos;

	img = anim_handler(cub, dst);
	pos = set_vec2(WIN_WIDTH - img.size.x, WIN_HEIGHT - img.size.y);
	draw_image_transparent(&img, dst, pos);
}
