#include "../p.h"
#include "d.h"

void    put_lines(t_inf *inf, t_pd pd)
{
	int i;
	int j;

	i = tile_size;
	j = tile_size;
	while (i < tile_size * pd.max_width)
	{
		j = tile_size;
		while (j < tile_size * pd.max_height)
		{
			if (!(j % tile_size) || !(i % tile_size))
				my_mlx_pixel_put(inf, i, j, create_trgb(100, 32, 32, 32), 0);
			j++;
		}
		i++;
	}
}

void    set_fov(char player, t_inf *inf)
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

void    put_player(t_inf *inf, t_pd *pd, int m)
{
	int i;
	int j;
	int f;
	int t;
	int t2;

	i = 0;
	j = 0;
	f = 0;
	while (pd->map[j])
	{
		i = 0;
		while (pd->map[j][i])
		{
			if (is_player(pd->map[j][i])) // check later;
			{
				set_fov(pd->map[j][i], inf);
				i = i * tile_size;
				inf->pi = i;
				j = j * tile_size;
				inf->pj = j;
				f = 1;
				break;
			}
			i++;
		}
		if (f)
			break;
		j++;
	}
	t = inf->pi;
	t2 = inf->pj;
	while (j < pd->max_height * tile_size && j < t2 + 5)
	{
		i = t;
		while (i < pd->max_width * tile_size && i < t + 5)
		{
			if (m)
				my_mlx_pixel_put(inf, i, j, create_trgb(0, 255, 0, 0), 0);
			else
				my_mlx_pixel_put(inf, i, j, create_trgb(0, 192, 192, 192), 0);
			i++;
		}
		j++;
	}
}

void    put_point(t_inf *inf, double i, double j, int m)
{
	int x;
	int y;

	x = i - 3;
	y = j - 3;
	if (x < 0)
		x = 0;
	while (x < i + 3)
	{
		y = j;
		if (y < 0)
			y = 0;
		while (y < j + 3)
		{
			if (m == 1)
				my_mlx_pixel_put(inf, x, y, create_trgb(0, 0, 255, 0), 0);
			else
				my_mlx_pixel_put(inf, x, y, create_trgb(0, 255, 0, 0), 0);
			y++;
		}
		x++;
	}
}

void	castAllRays(t_inf *inf, int m)
{
	int		i;
	double	fov;

	i = -1;
	fov = inf->fov - 30;
	while (++i < inf->pd->max_width)
	{
		ray(inf, fov, inf->pd, m);
		fov += 0.0333;
	}
}