/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:23:03 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 08:29:37 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

void	up_down(int keycode, t_inf *inf, t_index new)
{
	if (keycode == 13)
	{
		new.i = inf->p.i + (7.7 * cos(deg_to_rad(inf->fov)));
		new.j = inf->p.j + (7.7 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(inf->p.i
			/ TILE_SIZE)] != '1' && inf->pd->map[(int)(inf->p.j
				/ TILE_SIZE)][(int)(new.i / TILE_SIZE)] != 1
					&& inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(new.i
						/ TILE_SIZE)] != '1')
			redisplay_move(new.i, new.j, inf);
	}
	if (keycode == 1)
	{
		new.i = inf->p.i - (7.7 * cos(deg_to_rad(inf->fov)));
		new.j = inf->p.j - (7.7 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(inf->p.i
			/ TILE_SIZE)] != '1' && inf->pd->map[(int)(inf->p.j
			/ TILE_SIZE)][(int)(new.i / TILE_SIZE)] != 1
			&& inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(new.i
				/ TILE_SIZE)] != '1')
			redisplay_move(new.i, new.j, inf);
	}
}

void	left_right(int keycode, t_inf *inf, t_index new)
{
	if (keycode == 2)
	{
		new.i = inf->p.i + (7.7 * cos(deg_to_rad(inf->fov + 90)));
		new.j = inf->p.j + (7.7 * sin(deg_to_rad(inf->fov + 90)));
		if (inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(inf->p.i
			/ TILE_SIZE)] != '1' && inf->pd->map[(int)(inf->p.j
			/ TILE_SIZE)][(int)(new.i / TILE_SIZE)] != 1 &&
		inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(new.i / TILE_SIZE)] != '1')
			redisplay_move(new.i, new.j, inf);
	}
	if (keycode == 0)
	{
		new.i = inf->p.i - (7.7 * cos(deg_to_rad(inf->fov + 90)));
		new.j = inf->p.j - (7.7 * sin(deg_to_rad(inf->fov + 90)));
		if (inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(inf->p.i
			/ TILE_SIZE)] != '1' && inf->pd->map[(int)(inf->p.j
			/ TILE_SIZE)][(int)(new.i / TILE_SIZE)] != 1 &&
		inf->pd->map[(int)(new.j / TILE_SIZE)][(int)(new.i / TILE_SIZE)] != '1')
			redisplay_move(new.i, new.j, inf);
	}
}

int	key_hook(int keycode, t_inf *inf)
{
	if (keycode == 1 || keycode == 13)
		up_down(keycode, inf, (t_index){0, 0});
	else if (keycode == 2 || keycode == 0)
		left_right(keycode, inf, (t_index){0, 0});
	else if (keycode == 123 || keycode == 124)
		redisplay_view(inf, keycode);
	else if (keycode == 53)
		exit(0);
	return (0);
}

void	redisplay_view(t_inf *inf, int keycode)
{
	cast_all_rays(inf, 0);
	if (keycode == 124)
		inf->fov += inf->step;
	else if (keycode == 123)
		inf->fov -= inf->step;
	cast_all_rays(inf, 1);
	render_3d(inf);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->frame.img_ptr, 0, 0);
}

void	redisplay_move(double new_i, double new_j, t_inf *inf)
{
	cast_all_rays(inf, 0);
	inf->p.i = new_i;
	inf->p.j = new_j;
	cast_all_rays(inf, 1);
	render_3d(inf);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->frame.img_ptr, 0, 0);
}
