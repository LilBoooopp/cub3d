/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:32 by plbuet            #+#    #+#             */
/*   Updated: 2025/07/02 21:07:00 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ini_texture(t_tex *texture)
{
	texture->full = 0;
	texture->c = NULL;
	texture->f = NULL;
	texture->n = NULL;
	texture->s = NULL;
	texture->we = NULL;
	texture->ea = NULL;
}

void	c_point(t_tex *texture, char *tmp, char *line)
{
	if (ft_strncmp(line, "WE", 2) == 0 && !texture->we)
	{
		texture->we = ft_strdup(tmp);
		texture->full++;
	}
	else if (ft_strncmp(line, "NO", 2) == 0 && !texture->n)
	{
		texture->n = ft_strdup(tmp);
		texture->full++;
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && !texture->s)
	{
		texture->s = ft_strdup(tmp);
		texture->full++;
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && !texture->ea)
	{
		texture->ea = ft_strdup(tmp);
		texture->full++;
	}
	else
		texture->full = -1;
}
