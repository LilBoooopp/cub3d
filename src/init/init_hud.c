/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:50:53 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 16:40:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_some_anim(t_cub *cub, t_hud *hud, int i)
{
	while (i > 5)
	{
		mlx_destroy_image(cub->mlx, hud->anim_reload[i - 6].img);
		i--;
	}
	while (i > 1)
	{
		mlx_destroy_image(cub->mlx, hud->anim_shoot[i - 2].img);
		i--;
	}
	if (i == 1)
		mlx_destroy_image(cub->mlx, hud->anim_idle.img);
}

static int	pick_sprite_anim(t_cub *cub, t_hud *hud, char *file, int i)
{
	t_img	tmp;
	int		error;

	error = setup_xpm(cub, &tmp, file);
	if (error)
		return (free_some_anim(cub, hud, i - 1), 1);
	if (i == 1)
		hud->anim_idle = scale_size(cub, tmp, 3);
	else if (i < 6)
		hud->anim_shoot[i - 2] = scale_size(cub, tmp, 3);
	else
		hud->anim_reload[i - 6] = scale_size(cub, tmp, 3);
	return (0);
}

static int	load_anims(t_cub *cub, t_hud *hud)
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
		if (pick_sprite_anim(cub, hud, file, i))
			return (free(file), free(num), 1);
		free(file);
		free(num);
		i++;
	}
	return (0);
}

int	init_hud(t_cub *cub, t_hud *hud)
{
	hud->anim_state = 0;
	hud->current_frame = 0;
	hud->frame_timer = 0;
	hud->frame_count = 0;
	hud->frame_duration = 0.1;
	return (load_anims(cub, hud));
}
