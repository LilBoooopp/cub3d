/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:33:13 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/20 15:48:57 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

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
		ft_memset(map[y], '1', width);
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

