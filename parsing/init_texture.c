/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:32 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/16 15:46:06 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void color(char *s, int where, t_texture *texture)
{
	int		rgb;
	int		i;
	char	**tmp;
	char	color[7];

	i = 0;
	s = skip_space(&s);
	tmp = ft_split(s, ',');
	while (i < 3)
	{
		rgb = ft_atoi(tmp[i])
		if(where == 'f')
			texture.
	}
}