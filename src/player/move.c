/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:41:35 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 22:51:08 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_forward(t_player *p)
{
	p->pos.x += p->dir.x * MOVE_SPEED;
	p->pos.y += p->dir.y * MOVE_SPEED;
}

void	move_backward(t_player *p)
{
	p->pos.x -= p->dir.x * MOVE_SPEED;
	p->pos.y -= p->dir.y * MOVE_SPEED;
}

void	move_right(t_player *p)
{
	p->pos.x -= p->dir.y * MOVE_SPEED;
	p->pos.y += p->dir.x * MOVE_SPEED;
}

void	move_left(t_player *p)
{
	p->pos.x += p->dir.y * MOVE_SPEED;
	p->pos.y -= p->dir.x * MOVE_SPEED;
}

void	rotate(t_player *p, double angle)
{
	double	old_dir;
	double	old_plane;

	old_dir = p->dir.x;
	old_plane = p->plane.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane * sin(angle) + p->plane.y * cos(angle);
}
