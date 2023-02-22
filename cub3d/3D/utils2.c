/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:34:34 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/22 11:53:56 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

int	check_square(t_inf *inf, int x, int y, t_index i, int m)
{
	if (y < 0 || x < 0 || y >= inf->pd->max_height
		|| x >= ft_len(inf->pd->map[y]))
	{
		inf->flag = -2;
		return (0);
	}
	if ((int)i.i == TILE_SIZE || (int)i.j == TILE_SIZE
		|| inf->pd->map[y][x] == '1' || !inf->pd->map[y][x])
	{
		if (m == 1)
			inf->h = i;
		else
			inf->v = i;
		return (0);
	}
	return (1);
}

int	check_four_squares(t_inf *inf, t_index i, int m)
{
	int	x;
	int	y;

	x = (int)((i.i / TILE_SIZE));
	y = (int)((i.j / TILE_SIZE));
	if (!check_square(inf, x, y, i, m))
		return (0);
	if (!check_square(inf, x - 1, y, i, m))
		return (0);
	if (!check_square(inf, x, y - 1, i, m))
		return (0);
	if (!check_square(inf, x - 1, y - 1, i, m))
		return (0);
	return (1);
}

void	v_intersections(t_inf *inf)
{
	t_index	d;
	t_index	t;

	d = (t_index){0.0, 0.0};
	t = (t_index){0.0, 0.0};
	if ((fmod(inf->p.j, TILE_SIZE)))
	{
		if (sign_of(cos(deg_to_rad(inf->ray))) == -1)
			d.i = fmod(inf->p.i, TILE_SIZE) * (-1);
		else
			d.i = (TILE_SIZE - fmod(inf->p.i, TILE_SIZE));
	}
	else
		d.i = TILE_SIZE * sign_of(cos(deg_to_rad(inf->ray)));
	d.j = d.i * tan(deg_to_rad(inf->ray));
	t.j = (TILE_SIZE * tan(deg_to_rad(inf->ray)))
		* sign_of(cos(deg_to_rad(inf->ray)));
	t.i = TILE_SIZE * (sign_of(cos(deg_to_rad(inf->ray))));
	while (check_points_v(inf->p.i + d.i, inf->p.j + d.j, inf->pd, inf))
	{
		d.j += t.j;
		d.i += t.i;
	}
}

void	h_intersections(t_inf *inf)
{
	t_index	d;
	t_index	t;

	d = (t_index){0.0, 0.0};
	t = (t_index){0.0, 0.0};
	if ((fmod(inf->p.j, TILE_SIZE)))
	{
		if (sign_of(sin(deg_to_rad(inf->ray))) == -1)
			d.j = fmod(inf->p.j, TILE_SIZE) * (-1);
		else
			d.j = (TILE_SIZE - fmod(inf->p.j, TILE_SIZE));
	}
	else
		d.j = TILE_SIZE * sign_of(sin(deg_to_rad(inf->ray)));
	d.i = d.j / tan(deg_to_rad(inf->ray));
	t.i = (TILE_SIZE / tan(deg_to_rad(inf->ray)))
		* sign_of(sin(deg_to_rad(inf->ray)));
	t.j = TILE_SIZE * (sign_of(sin(deg_to_rad(inf->ray))));
	while (check_points_h(inf->p.i + d.i, inf->p.j + d.j, inf->pd, inf))
	{
		d.j += t.j;
		d.i += t.i;
	}
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
