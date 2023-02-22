/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:10:04 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/22 11:22:01 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

void	draw_sma_wlard(t_inf *inf, int i, int j, int x)
{
	int	color;

	color = inf->f_col;
	if (i < 0)
		color = inf->c_col;
	while (++i < j)
		my_mlx_pixel_put(&inf->frame, x, i, color);
}

t_index	check(double i, double j, int max_height)
{
	t_index	pixel;

	pixel = (t_index){i, j};
	if (pixel.i < 0)
		pixel.i = 0;
	if (pixel.j > max_height)
		pixel.j = max_height;
	return (pixel);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	deg_to_rad(double angle)
{
	angle = angle * (M_PI / 180);
	return (angle);
}

int	sign_of(double n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}
