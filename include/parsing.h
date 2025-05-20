/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:15 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/20 15:19:54 by plbuet           ###   ########.fr       */
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

void	spHex(int rgb, int i, t_texture *texture, int fc);
int		color(char *s, int fc, t_texture *texture);
void	c_point(char *line, t_texture *texture);
t_node	*ft_new(char *content);
t_map	*read_map(int fd, char *line);
t_node	*ft_new(char *content);
int		ft_size(t_node *lst);
char	**create_empty_map(int height, int width);

#endif
