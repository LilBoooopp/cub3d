/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:35:28 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/20 19:56:31 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	set_vec2(double x, double y)
{
	t_vec2	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec3	set_vec3(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec4	set_vec4(int r, int g, int b, int a)
{
	t_vec4	new;

	new.r = r;
	new.g = g;
	new.b = b;
	new.a = a;
	return (new);
}

int	is_in_bounds(t_img *img, t_vec2 point)
{
	if (point.x >= 0 && point.x < img->size.x && point.y >= 0
		&& point.y < img->size.y)
		return (1);
	return (0);
}
