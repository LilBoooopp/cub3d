/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:23:19 by pbuet             #+#    #+#             */
/*   Updated: 2025/06/18 19:46:18 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void	free_texture(t_cub *c)
{
	free(c->tex.we);
	free(c->tex.n);
	free(c->tex.s);
	free(c->tex.ea);
}

void	close_gnl(char *line, int fd)
{
	free(line);
	while((line = get_next_line(fd)))
	{
		free(line);
	}
	free(line);
}