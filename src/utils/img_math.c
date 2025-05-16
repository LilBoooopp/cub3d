/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:32:42 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/14 15:46:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec2	fix_pos(t_cub *cub, t_img *dst, t_vec2 pos)
{
	t_vec2	new;
	double	x;
	double	y;

	x = dst->size.x / cub->map->sizex;
	y = dst->size.y / cub->map->sizey;
	new = set_vec2((pos.x * (x - 1)) + (x / 2), (pos.y * (y - 1)) + (y / 2));
	return (new);
}

t_vec2	get_center(t_img *img)
{
	t_vec2	ret;

	ret.x = img->size.x / 2;
	ret.y = img->size.y / 2;
	return (ret);
}
