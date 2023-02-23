/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:37:57 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 05:38:22 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

void	set_fov(char player, t_inf *inf)
{
	if (player == 'N')
		inf->fov = 90;
	else if (player == 'S')
		inf->fov = 270;
	else if (player == 'E')
		inf->fov = 360;
	else if (player == 'W')
		inf->fov = 180;
}

void	cast_all_rays(t_inf *inf, int m)
{
	inf->ray = inf->fov - 30;
	inf->index = 0;
	while (inf->ray <= inf->fov + 30)
	{
		if (m)
		{
			h_intersections(inf);
			v_intersections(inf);
			calc_col_dis(inf);
		}
		inf->rays[inf->index].ray_angle = inf->ray;
		inf->ray += 0.04;
		inf->index++;
	}
}

void	launch(t_inf *inf)
{
	put_player(inf, inf->pd);
	inf->p.i += TILE_SIZE / 2;
	inf->p.j += TILE_SIZE / 2;
	cast_all_rays(inf, 1);
	render_3d(inf);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->frame.img_ptr, 0, 0);
}

void	put_player(t_inf *inf, t_pd *pd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pd->map[j])
	{
		i = 0;
		while (pd->map[j][i])
		{
			if (is_player(pd->map[j][i]))
			{
				set_fov(pd->map[j][i], inf);
				i = i * TILE_SIZE;
				inf->p.i = i;
				j = j * TILE_SIZE;
				inf->p.j = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

void	get_colors(t_inf *inf, t_pd *pd)
{
	inf->f_col = create_trgb(0, ft_atoi(pd->floor[0]), ft_atoi(pd->floor[1]),
			ft_atoi(pd->floor[2]));
	inf->c_col = create_trgb(0, ft_atoi(pd->sqef[0]), ft_atoi(pd->sqef[1]),
			ft_atoi(pd->sqef[2]));
}
