/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:47:45 by pbuet             #+#    #+#             */
/*   Updated: 2025/08/19 18:52:43 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	free_node(t_node *lst_map)
{
	t_node	*last;

	if (lst_map == NULL)
		return (0);
	while (lst_map->next != NULL)
	{
		last = lst_map;
		lst_map = lst_map->next;
		free(last->content);
		free(last);
	}
	free(lst_map->content);
	free(lst_map);
	return (1);
}

int	node_map(t_map *map, int max_width, t_node *lst_map, int size)
{
	t_node	*last;
	int		len;
	int		i;

	i = 0;
	while (i < size)
	{
		map->map[i] = malloc(sizeof(char) * (max_width + 1));
		if (!map->map[i])
		{
			ft_free_chartable(map->map);
			return (free_node(lst_map));
		}
		len = ft_strlen(lst_map->content);
		ft_memcpy(map->map[i], lst_map->content, len);
		ft_memset(map->map[i] + (len - 1), ' ', max_width - len);
		map->map[i][max_width - 1] = '\0';
		last = lst_map;
		lst_map = lst_map->next;
		free(last->content);
		free(last);
		i++;
	}
	map->map[i] = NULL;
	return (0);
}

int	create_directions(t_directions	*dir)
{
	dir->dx = malloc(sizeof(int) * 8);
	dir->dy = malloc(sizeof(int) * 8);
	if (!dir->dx || !dir->dy)
		return (1);
	dir->dx[0] = 1;
	dir->dy[0] = 0;
	dir->dx[1] = -1;
	dir->dy[1] = 0;
	dir->dx[2] = 0;
	dir->dy[2] = 1;
	dir->dx[3] = 0;
	dir->dy[3] = -1;
	dir->dx[4] = 1;
	dir->dy[4] = 1;
	dir->dx[5] = 1;
	dir->dy[5] = -1;
	dir->dx[6] = -1;
	dir->dy[6] = 1;
	dir->dx[7] = -1;
	dir->dy[7] = -1;
	return (0);
}
