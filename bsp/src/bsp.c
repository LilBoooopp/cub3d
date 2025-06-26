/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:18:31 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/26 16:05:45 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp.h"

int	random_int(int min, int max) {
	if (min > max)
		return (min);
	return rand() % (max - min + 1) + min;
}

t_bsp	*new_node(int x, int y,int width, int height)
{
	t_bsp	*new;

	new = malloc(sizeof(t_bsp));
	if (!new)
		return(NULL);
	new->x = x;
	new->y = y;
	new->height = height;
	new->width = width;
	new->rmidle_x = 0;
	new->rmidle_y = 0;
	new->left = NULL;
	new->right = NULL;
	new->room = NULL;
	return(new);
}

void	bsp_room(t_bsp *node, int min_size)
{
	if (node->left == NULL  && node->right == NULL)
	{
		node->room = malloc(sizeof(t_room));
		node->room->width = random_int(min_size, node->width - 4);
		node->room->height = random_int(min_size, node->height - 4);
		node->room->x = node->x + random_int(0, node->width - node->room->width);
		node->room->y = node->y + random_int(0, node->height - node->room->height);
	}
	else
	{
		if (node->left)
			bsp_room(node->left, min_size);
		if (node->right)
			bsp_room(node->right, min_size);
	}
}

void	bsp_split(t_bsp *node, int min_size, int max, int stop)
{
	int	split;

	if (max >= stop)
		return;
	if (node->width < 2 * min_size && node->height < 2 * min_size)
        return;
	if (node->height > node->width)
	{
		split = random_int(min_size, node->height - min_size);
		node->left = new_node(node->x, node->y, node->width, split);
		node->right = new_node(node->x, node->y + split, node->width, node->height - split);
	}
	else
	{
		split = random_int(min_size, node->width - min_size);
		node->left = new_node(node->x, node->y, split, node->height);
		node->right = new_node(node->x + split, node->y, node->width - split, node->height);
	}
	bsp_split(node->left, min_size, max + 1, stop);
	bsp_split(node->right, min_size, max + 1, stop);
}
