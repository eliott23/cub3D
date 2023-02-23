/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:42:38 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 23:02:50 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d.h"

void	render_3d(t_inf *inf)
{
	double	dis_pp;
	double	w_h;
	t_index	i;
	t_index	pixel;
	int		m_h;

	i.i = 0.0;
	dis_pp = (WIN_WIDTH / 2) / tan(deg_to_rad(60 / 2));
	m_h = WIN_HEIGHT;
	while (i.i < WIN_WIDTH)
	{
		w_h = (TILE_SIZE / (inf->rays[(int)i.i].col_dist
					* cos(deg_to_rad(inf->rays[(int)i.i].ray_angle - inf->fov)))
				) * dis_pp;
		pixel = check((m_h / 2) - (w_h / 2),
				(m_h / 2) + (w_h / 2), m_h);
		draw_sma_wlard(inf, -1, pixel.i, i.i);
		i.j = pixel.i - 1;
		while (++i.j < pixel.j)
			my_mlx_pixel_put(&inf->frame, i.i, i.j,
				get_pixel(inf, i.i, (int)(((i.j + (w_h / 2)
								- (m_h / 2)) * TILE_SIZE) / w_h)));
		draw_sma_wlard(inf, pixel.j - 1, m_h, i.i);
		i.i++;
	}
}

int	check_points_h(double i, double j, t_pd *pd, t_inf *inf)
{
	int		dir;
	int		y;
	int		x;

	x = (int)((i / TILE_SIZE));
	dir = sign_of(sin(deg_to_rad(inf->ray)));
	y = (int)(j / TILE_SIZE);
	if (dir < 0)
		y = (int)(j / TILE_SIZE) - 1;
	if (y < 0 || x < 0 || y >= pd->max_height
		|| x >= ft_len(pd->map[y]))
	{
		inf->flag = -2;
		return (0);
	}
	if ((int)round(j) == TILE_SIZE || pd->map[y][x] == '1'
		|| pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		inf->h = (t_index){i, j};
		return (0);
	}
	if (!fmod(i, TILE_SIZE) && !fmod(j, TILE_SIZE))
		return (check_four_squares(inf, (t_index){i, j}, 1));
	return (1);
}

int	check_points_v(double i, double j, t_pd *pd, t_inf *inf)
{
	int	dir;
	int	x;
	int	y;

	y = (int)((j / TILE_SIZE));
	dir = sign_of(cos(deg_to_rad(inf->ray)));
	x = (int)(i / TILE_SIZE);
	if (dir < 0)
		x = (int)(i / TILE_SIZE) - 1;
	if (y < 0 || x < 0 || y >= pd->max_height
		|| x >= ft_len(pd->map[y]))
	{
		inf->flag = -1;
		return (0);
	}
	if ((int)round(i) == TILE_SIZE || pd->map[y][x] == '1'
		|| pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		inf->v = (t_index){i, j};
		return (0);
	}
	if (!fmod(i, TILE_SIZE) && !fmod(j, TILE_SIZE))
		return (check_four_squares(inf, (t_index){i, j}, 2));
	return (1);
}

// d.i is d_h and d.j is d_v
void	calc_col_dis(t_inf *inf)
{
	t_index	d;

	inf->rays[inf->index].h_v = 0;
	if (inf->flag == -2 || inf->flag == -1)
		outside_map(inf);
	else
	{
		d.i = ((inf->h.i - inf->p.i) * (inf->h.i - inf->p.i))
			+ ((inf->h.j - inf->p.j) * (inf->h.j - inf->p.j));
		d.i = sqrt(d.i);
		d.j = ((inf->v.i - inf->p.i) * (inf->v.i - inf->p.i))
			+ ((inf->v.j - inf->p.j) * (inf->v.j - inf->p.j));
		d.j = sqrt(d.j);
		inf->rays[inf->index].col_dist = min(d.i, d.j);
		if (inf->rays[inf->index].col_dist == d.i)
		{
			inf->rays[inf->index].x = fmod(inf->h.i, TILE_SIZE);
			inf->rays[inf->index].h_v = 1;
		}
		else
		{
			inf->rays[inf->index].x = fmod(inf->v.j, TILE_SIZE);
			inf->rays[inf->index].h_v = 2;
		}
	}
}

int	main(int ac, char **av)
{
	t_inf	*inf;
	t_pd	pd;

	pd = m_function(ac, av);
	inf = malloc(sizeof(t_inf));
	inf->pd = &pd;
	get_colors(inf, &pd);
	inf->step = 5;
	inf->flag = 0;
	inf->rays = malloc(sizeof(t_rays) * (WIN_WIDTH + 1));
	inf->textures = malloc(sizeof(t_xpm) * 4);
	inf->mlx = mlx_init();
	if (!inf->mlx || !xpm_init(inf))
		exit (1);
	inf->win_ptr = mlx_new_window(inf->mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3d");
	inf->frame.img_ptr = mlx_new_image(inf->mlx,
			WIN_WIDTH, WIN_HEIGHT);
	inf->frame.adrr = mlx_get_data_addr(inf->frame.img_ptr, &inf->frame.bpp,
			&inf->frame.size_line, &inf->frame.endian);
	launch(inf);
	mlx_hook(inf->win_ptr, 2, 0, key_hook, inf);
	mlx_hook(inf->win_ptr, 17, 0, exit_game, NULL);
	mlx_loop(inf->mlx);
}
