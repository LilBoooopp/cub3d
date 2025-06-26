/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:32:33 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/30 12:21:21 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	parse_rgbint(const char *rgb, int *r, int *g, int *b)
{
	int	i;
	int	vals[3];

	i = 0;
	while (i < 3)
	{
		vals[i] = 0;
		while (*rgb >= '0' && *rgb <= '9')
			vals[i] = vals[i] * 10 + (*rgb++ - '0');
		if (*rgb == ',' || *rgb == ' ')
			rgb++;
		i++;		
	}
	*r = vals[0];
	*g = vals[1];
	*b = vals[2];
}

void	parse_rgbhex(const char *rgb, int *r, int *g, int *b)
{
	*r = ft_ishex(rgb[0]) * 16 + ft_ishex(rgb[1]);
	*g = ft_ishex(rgb[2]) * 16 + ft_ishex(rgb[3]);
	*b = ft_ishex(rgb[4]) * 16 + ft_ishex(rgb[5]);
}
