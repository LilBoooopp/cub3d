/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:32:42 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 17:36:58 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec2	fix_pos(t_img *src, t_img *dst, t_vec2 pos)
{
	t_vec2	new;
	double	x;
	double	y;

	x = src->size.x / dst->size.x;
	y = src->size.y / dst->size.y;
	new = vec2_div(pos, set_vec2(x, y));
	return (new);
}

t_vec2	get_center(t_img *img)
{
	t_vec2	ret;

	ret.x = img->size.x / 2;
	ret.y = img->size.y / 2;
	return (ret);
}
