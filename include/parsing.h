/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:15 by plbuet            #+#    #+#             */
/*   Updated: 2025/08/20 17:35:55 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../include/cub3d.h"

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_directions
{
	int	*dx;
	int	*dy;
}	t_directions;

int		rgb_check(t_tex *texture);
void	c_point(t_tex *texture, char *tmp, char *line);
t_node	*ft_new(char *content);
t_map	*read_map(int fd, char *line, int len, int max_width);
t_node	*ft_new(char *content);
int		ft_size(t_node *lst);
char	**create_empty_map(int height, int width);
int		search_player(t_map *map, int end);
char	**rescale(t_map *strmap);
void	free_texture(t_cub *cub);
void	close_gnl(char *line, int fd);
int		node_map(t_map *map, int max_width, t_node *lst_map, int size);
void	ini_texture(t_tex *texture);
int		texture_check(t_tex *texture, int fd, char *temp);
int		check_file(char *name_files, char *extension, size_t size, int clos);
int		create_directions(t_directions	*dir);
int		free_node(t_node *lst_map);
int		checkline(char *line);

#endif
