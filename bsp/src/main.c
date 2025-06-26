/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:09:13 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/26 15:56:46 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"bsp.h"

void clear_node(t_bsp *node)
{
	if (!node)
		return;
	clear_node(node->left);
	clear_node(node->right);
	if (node->room)
		free(node->room);
	free(node);
}
int bsp_max_depth(int map_w, int map_h, int min_room_size) {
    int leaf_min = min_room_size + 2;
    double ratio = (double)fmin(map_w, map_h) / leaf_min;
    if (ratio < 2.0) return 0;  
    return (int)floor(log2(ratio));
}

int main(int argc, char **argv) {
	int width;
	int height;
	int min_size;
	t_bsp	*root;

	min_size = 4;
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	if (argc != 3)
		return(1);
	srand(time(NULL)); // initialise le générateur aléatoire
	root = new_node(0, 0, width, height);
	bsp_split(root, min_size, 0, bsp_max_depth(width, height, min_size));
	bsp_room(root, min_size);
	char **map = create_empty_map(height, width);
	map_draw_rooms(root, map);
	find_line_map(root, map);
	map[root->rmidle_y][root->rmidle_x] = 'S';
	ft_print_chartable(map);
	clear_node(root);

	return 0;
}
