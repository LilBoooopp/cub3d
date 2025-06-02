/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:32 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/02 23:30:49 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void	spHex(int rgb, int i, t_tex *texture, int fc)
{
	char digits[] = "0123456789ABCDEF";
	
	if (fc == 0)
	{
		texture->f[i * 2]= digits[(rgb >> 4) & 0xF];
		texture->f[i * 2 + 1]= digits[(rgb) & 0xF];
	}
	else
	{
		texture->c[i * 2]= digits[(rgb >> 4) & 0xF];
		texture->c[i * 2 + 1]= digits[(rgb) & 0xF];
	}
}

int	color(char *s, int fc, t_tex *texture)
{
	int		rgb;
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(s, ',');
	while (i < 3)
	{
		rgb = ft_atoi(tmp[i]);
		if (rgb > 255 || rgb < 0)
			break;
		spHex(rgb, i, texture, fc);
		i ++;
	}
	while(i >= 0)
	{
		free(tmp[i]);
		i --;
	}
	free(tmp);
	if (rgb > 255 || rgb < 0)
		return (1);
	texture->full ++;
	return (0);
}

void	c_point(char *line, t_tex *texture)
{
	line = ft_strtrim(line, "\n");
	if (ft_strncmp(line, "WE", 2) == 0 && !texture->we)
	{
		texture->we = &line[3];
		texture->full++;
	}
	else if (ft_strncmp(line, "NO", 2) == 0 && !texture->n)
	{
		texture->n = &line[3];
		texture->full++;
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && !texture->s)
	{
		texture->s = &line[3];
		texture->full++;
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && !texture->ea)
	{
		texture->ea = &line[3];
		texture->full++;
	}
}

