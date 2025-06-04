/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:33:13 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/05 00:49:31 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	find_char(t_map *map, int x, int y)
{
	if (map->map[y][x] == '\0')
		return (0);
	if (ft_strchr("NSEW", map->map[y][x]))
	{
		map->playerx = x + 0.5f;
		map->playery = y + 0.5f;
		map->orientation = map->map[y][x];
		map->map[y][x] = '0';
		return (1);
	}
	else if (map->map[y][x] != '0' && map->map[y][x] != '1' && map->map[y][x] != ' ')
	{
		printf("%c\n", map->map[y][x]);
		perror("Error invalide char\n");
		return (2);
	}
	return (0);
}

int	search_player(t_map *map)
{
	int	y;
	int	x;
	int	find;

	x = 0;
	y = 0;
	find = 0;
	while (y < map->sizey)
	{
		x = 0;
		while(x < map->sizex)
		{
			if (find_char(map, x, y))
				find++;
			
			x++;
		}
		y++;
	}
	if (find != 1)
		return (-1);
	return (0);
}
char **create_empty_map(int height, int width)
{
	char **map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	for (int y = 0; y < height; y++)
	{
		map[y] = malloc(width + 1);
		if (!map[y])
			return (NULL); // à compléter avec libération en cas d'erreur
		ft_memset(map[y], ' ', width);
		map[y][width] = '\0';
	}
	map[height] = NULL;
	return (map);
}

int	ft_size(t_node *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_node	*ft_new(char *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

