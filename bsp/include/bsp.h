#ifndef BSP_H
# define BSP_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>
# include <time.h>
# include "../libft/libft.h"

typedef struct s_room
{
	int x;
	int y;
	int width;
	int height;
}	t_room;

typedef struct s_bsp
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	id;
	int	rmidle_x;
	int	rmidle_y;
	struct s_bsp	*left;
	struct s_bsp	*right;
	t_room	*room;
}	t_bsp;

void	map_draw_rooms(t_bsp *node, char **map);
char	**create_empty_map(int height, int width);

int		random_int(int min, int max);
t_bsp	*new_node(int x, int y,int width, int height);
void	bsp_room(t_bsp *node, int min_size);
void	bsp_split(t_bsp *node, int min_size, int max, int stop);
void	find_line_map(t_bsp *node, char **map);
#endif