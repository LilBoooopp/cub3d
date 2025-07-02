/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:30:40 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 19:39:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *reason)
{
	printf("Error\n");
	perror(reason);
}

void	free_map(t_cub *cub)
{
	int	y;

	ft_free_chartable(cub->map->map);
	y = -1;
	while (++y < cub->map->sizey)
		free(cub->map->explored[y]);
	free(cub->map->explored);
	free(cub->map);
}
