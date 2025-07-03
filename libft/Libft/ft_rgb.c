/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:32:33 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/03 13:09:18 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	parse_rgb_component(const char **rgb, int *val)
{
	int	res;

	res = 0;
	while (**rgb == ' ')
		(*rgb)++;
	if (**rgb == '-' || **rgb == '\0')
		return (1);
	if (**rgb < '0' || **rgb > '9')
		return (1);
	while (**rgb >= '0' && **rgb <= '9')
	{
		res = res * 10 + (**rgb - '0');
		(*rgb)++;
	}
	while (**rgb == ' ')
		(*rgb)++;
	*val = res;
	return (0);
}

int	parse_rgbint(const char *rgb, int *r, int *g, int *b)
{
	int	i;
	int	rgb_vals[3];

	i = 0;
	while (i < 3)
	{
		if (parse_rgb_component(&rgb, &rgb_vals[i]))
			return (1);
		if (i < 2)
		{
			if (*rgb != ',')
				return (1);
			rgb++;
		}
		i++;
	}
	while (*rgb == ' ')
		rgb++;
	if (*rgb != '\0')
		return (1);
	*r = rgb_vals[0];
	*g = rgb_vals[1];
	*b = rgb_vals[2];
	return (0);
}

void	parse_rgbhex(const char *rgb, int *r, int *g, int *b)
{
	*r = ft_ishex(rgb[0]) * 16 + ft_ishex(rgb[1]);
	*g = ft_ishex(rgb[2]) * 16 + ft_ishex(rgb[3]);
	*b = ft_ishex(rgb[4]) * 16 + ft_ishex(rgb[5]);
}
