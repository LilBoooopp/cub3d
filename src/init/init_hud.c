/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:50:53 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 23:15:01 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_anims(t_cub *cub, t_hud *hud)
{
	char	*gun;
	char	*file;
	int		i;
	char	*num;

	i = 1;
	hud->anim_shoot = malloc(sizeof(t_img) * 4);
	hud->anim_reload = malloc(sizeof(t_img) * 9);
	while (i < 15)
	{
		num = ft_itoa(i);
		gun = ft_strjoin("resources/gun/gun_", num);
		file = ft_strjoin(gun, ".xpm");
		free(gun);
		if (i == 1)
			hud->anim_idle = scale_size(cub, setup_xpm(cub, file), 3);
		else if (i < 6)
			hud->anim_shoot[i - 2] = scale_size(cub, setup_xpm(cub, file), 3);
		else
			hud->anim_reload[i - 6] = scale_size(cub, setup_xpm(cub, file), 3);
		free(file);
		free(num);
		i++;
	}
}

void	init_hud(t_cub *cub, t_hud *hud)
{
	hud->anim_state = 0;
	hud->current_frame = 0;
	hud->frame_timer = 0;
	hud->frame_count = 0;
	hud->frame_duration = 0.1;
	load_anims(cub, hud);
}
