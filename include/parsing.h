/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:15 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/19 16:18:20 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"../include/cub3d.h"

typedef struct s_node
{
	char	*content;
	struct s_node	*next;
}t_node;

void	spHex(int rgb, int i, t_tex *texture, int fc);
int		color(char *s, int fc, t_tex *texture);
void	c_point(char *line, t_tex *texture);
t_node	*ft_new(char *content);
t_map	*read_map(int fd, char *line);
t_node	*ft_new(char *content);
int		ft_size(t_node *lst);
char	**create_empty_map(int height, int width);
int		search_player(t_map *map, int end);
char	**rescale(t_map *strmap);
void 	free_texture(t_cub *cub);
void	close_gnl(char *line, int fd);
int		node_map(t_map *map, int max_width, t_node *lst_map, int size);
#endif
