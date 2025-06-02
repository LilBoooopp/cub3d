/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_veci.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:23:17 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/02 23:46:01 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2i	set_vec2i(int x, int y)
{
	t_vec2i	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2	itovec(t_vec2i veci)
{
	t_vec2	new;

	new.x = (double)veci.x;
	new.y = (double)veci.y;
	return (new);
}
