/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:28:07 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/19 14:31:54 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2i	pos_to_map(t_cub *c, t_vec2 pos)
{
	t_vec2i	ret;
	t_vec2	ratio;

	ratio.x = c->map->screenx / c->map->sizex;
	ratio.y = c->map->screeny / c->map->sizey;
	ret.x = pos.x * ratio.x;
	ret.y = pos.y * ratio.y;
	return (ret);
}
