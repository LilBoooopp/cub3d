/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 16:32:27 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec2	vec2_add(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	return (new);
}

t_vec2	vec2_sub(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	return (new);
}

t_vec2	vec2_mult(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	return (new);
}

t_vec2	vec2_div(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	new;

	new.x = vec1.x / vec2.x;
	new.y = vec1.y / vec2.y;
	return (new);
}

t_vec2i	vecdtoi(t_vec2 vec2)
{
	t_vec2i	new;

	new.x = (int)vec2.x;
	new.y = (int)vec2.y;
	return (new);
}
