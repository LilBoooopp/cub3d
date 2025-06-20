/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:32 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/20 14:05:52 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void	ini_texture(t_tex *texture)
{
	texture->full = 0;
	texture->c[0] = '\0';
	texture->f[0] = '\0';
	texture->n = NULL;
	texture->s = NULL;
	texture->we = NULL;
	texture->ea = NULL;
}

void	sphex(int rgb, int i, t_tex *texture, int fc)
{
	char	*digits;

	digits = "123456789ABCDEF";
	if (fc == 0)
	{
		texture->f[i * 2] = digits[(rgb >> 4) & 0xF];
		texture->f[i * 2 + 1] = digits[(rgb) & 0xF];
	}
	else
	{
		texture->c[i * 2] = digits[(rgb >> 4) & 0xF];
		texture->c[i * 2 + 1] = digits[(rgb) & 0xF];
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
			break ;
		sphex(rgb, i, texture, fc);
		i++;
	}
	while (i >= 0)
	{
		free(tmp[i]);
		i--;
	}
	free(tmp);
	if (rgb > 255 || rgb < 0)
		return (1);
	texture->full++;
	free(s);
	return (0);
}

void	c_point(char *line, t_tex *texture)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n");
	if (ft_strncmp(tmp, "WE", 2) == 0 && !texture->we)
	{
		texture->we = ft_strdup(&tmp[3]);
		texture->full++;
	}
	else if (ft_strncmp(tmp, "NO", 2) == 0 && !texture->n)
	{
		texture->n = ft_strdup(&tmp[3]);
		texture->full++;
	}
	else if (ft_strncmp(tmp, "SO", 2) == 0 && !texture->s)
	{
		texture->s = ft_strdup(&tmp[3]);
		texture->full++;
	}
	else if (ft_strncmp(tmp, "EA", 2) == 0 && !texture->ea)
	{
		texture->ea = ft_strdup(&tmp[3]);
		texture->full++;
	}
	free(tmp);
}
