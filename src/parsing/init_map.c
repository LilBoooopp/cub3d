/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:47:45 by pbuet             #+#    #+#             */
/*   Updated: 2025/06/19 15:10:38 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"
int	free_node(t_node *lst_map)
{
	t_node	*last;
	while (lst_map->next != NULL)
	{
		last = lst_map;
		lst_map = lst_map->next;
		free(last->content);
		free(last);
	}
	return(1);
}
int	node_map(t_map *map, int max_width, t_node *lst_map, int size)
{
	t_node	*last;
	int 	len;
	int		i;

	i = 0;
	while (i < size)
	{
		map->map[i] = malloc(sizeof(char) * (max_width + 1));
		if (!map->map[i])
		{
			ft_free_chartable(map->map);
			return(free_node(lst_map));
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
