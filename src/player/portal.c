/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:45:15 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/23 16:36:47 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize portal textures and state
 * @param cub t_cub struct
 */
void	init_portals(t_cub *cub)
{
	cub->portal_a.active = false;
	cub->portal_b.active = false;
	cub->portal_a.linked = &cub->portal_b;
	cub->portal_b.linked = &cub->portal_a;
	cub->portal_orange = setup_xpm(cub, "resources/portal_orange.xpm");
	cub->portal_blue = setup_xpm(cub, "resources/portal_blue.xpm");
	cub->portal_a.texture = &cub->portal_orange;
	cub->portal_b.texture = &cub->portal_blue;
}

/**
 * @brief Handle Q/E key presses for portal placement
 */
void	handle_portal_input(int keycode, t_cub *cub)
{
	double		now;
	t_portal	*p;

	now = gettime();
	if (keycode != KEY_Q && keycode != KEY_E)
		return ;
	if (keycode == KEY_Q)
		p = &cub->portal_a;
	else if (keycode == KEY_E)
		p = &cub->portal_b;
	if (now - p->last_time < PORTAL_COOLDOWN)
		return ;
	if (p->active == false)
		p->active = true;
	place_portal_at_center(cub, p);
	p->last_time = now;
	if (p->linked->active && p->linked->last_time < p->last_time)
		p->linked->active = false;
}
