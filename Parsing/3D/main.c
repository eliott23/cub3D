#include "d.h"


void	my_mlx_pixel_put(t_inf *inf, int x, int y, int color, int m)
{
	int		offset;
	char	*pixel;
	if (!m)
	{
		x = x / 6;
		y = y / 6;
		offset = y * inf->img.size_line + x * (inf->img.bpp / 8);
		pixel = inf->img.adrr + offset;
		*(unsigned int *)pixel = color;
	}
	else
	{
		offset = y * inf->g_img.size_line + x * (inf->g_img.bpp / 8);
		pixel = inf->g_img.adrr + offset;
		*(unsigned int *)pixel = color;
	}
	//to get the position of the current pixel
	//bpp is devided by 8 cus its already multiplied by 8 (a pixel is coded on 4 char, those chars worth 8 bits each)
	//(X position * 4 + 4 * Line size * Y position)
}

int calc_cord(double angle, int l, int j, int i, t_pd *pd)
{
	if (!pd->map[j / tile_size])
		return (0);
	// if (pd->map[j / tile_size][i / tile_size] == '1' || pd->map[j / tile_size][(i + 1) / tile_size] == '1')
	//     return (0);
	if (pd->map[j / tile_size][i / tile_size] == '1')
		return (0);
	return (1);
}

void    ray(t_inf *inf, double angle, t_pd *pd, int m)
{
	int l = 0;
	int t = inf->pi;
	int t2 = inf->pj;
	int lim;

	lim = (int)inf->col_dist[inf->index];
	while (l < lim)
	{
		t =  inf->pi + (l * cos(angle));
		t2 = inf->pj + (l * sin(angle));
		if (t < 0 || t >= pd->max_width * tile_size || t2 >= pd->max_height * tile_size || t2 < 0)
			break ;
		if (m)
			my_mlx_pixel_put(inf, t, t2, create_trgb(50, 255, 0, 0), 0);
		// else if ((t % tile_size) && (t2 % tile_size))
			// my_mlx_pixel_put(inf, t, t2, create_trgb(0, 192, 192, 192));
		else
			my_mlx_pixel_put(inf, t, t2, create_trgb(0, 192, 192, 192), 0);
		// else
			// my_mlx_pixel_put(inf, t, t2, create_trgb(100, 32, 32, 32));
		l++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void    m_fill(t_inf *inf, t_pd pd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < pd.max_height * tile_size)
	{
		i = 0;
		while (i < pd.max_width * tile_size)
		{
			if (!pd.map[j / tile_size][i / tile_size])
				break;
			if (pd.map[j / tile_size][i / tile_size] == '0' || is_player(pd.map[j / tile_size][i / tile_size])) //check later;
				my_mlx_pixel_put(inf, i, j, create_trgb(0, 192, 192, 192), 0);
			else if (pd.map[j / tile_size][i / tile_size] == '1')
				my_mlx_pixel_put(inf, i, j, create_trgb(0, 32, 32, 32), 0);
			i++;
		}
		j++;
	}
}

double  deg_to_rad(double angle)
{
	angle = angle * (M_PI / 180);
	return (angle);
}

int sign_of(double n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}

int check_square(t_inf *inf, int x, int y, double i, double j, int m)
{
	if (y < 0 || x < 0 || y > inf->pd->max_height ||\
	x > ft_len(inf->pd->map[y]) )
	{
		inf->flag = -2; //check description in the check_point_v() function;
		return (0);
	}
	if (i == tile_size || j == tile_size || inf->pd->map[y][x] == '1' || !inf->pd->map[y][x]) //might wanna round the i and j;
	{
		// printf("went here\n");
		if (m == 1)
		{
			inf->h_i = i;
			inf->h_j = j;
		}
		else
		{
			inf->v_i = i;
			inf->v_j = j;
		}
		return (0);
	}
	return (1);
}

int checK_four_squares(t_inf *inf , double i, double j, int m)
{
	int x;
	int y;

	x = (int)((round(i) / tile_size));
	y = (int)((round(j) / tile_size));
	if (!check_square(inf, x, y, i, j, m))
		return (0);
	if (!check_square(inf, x - 1, y, i, j, m))
		return (0);
	if (!check_square(inf, x, y - 1, i, j, m))
		return (0);
	if (!check_square(inf, x - 1, y - 1, i, j, m))
		return (0);
	return (1);
}

int check_points_h(double i, double j, t_pd *pd, t_inf *inf)
{
	double unit;
	int    dir;
	double r;
	int y;
	int x;

	unit = tile_size;
	x = (int)((round(i) / unit));
	dir = sign_of(sin(deg_to_rad(inf->ray)));
	if (dir < 0)
		y = (int)(round(j) / unit) - 1;
	else
		y = (int)(round(j) / unit);
	if (y < 0 || x < 0 || y > pd->max_height ||\
	x > ft_len(pd->map[y]) )
	{
		inf->flag = -2; //check description in the check_point_v() function;
		return (0);
	}
	if (i == unit || j == unit || pd->map[y][x] == '1' || pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		// printf("went here h\n");
		// put_point(inf, i, j, 1);
		inf->h_i = i;
		inf->h_j = j;
		return (0);
	}
	if (!fmod(round(i), tile_size) && !fmod(round(j), tile_size))
		return (checK_four_squares(inf, i, j, 1));
	return (1);
}

int check_points_v(double i, double j, t_pd *pd, t_inf *inf)
{
	double unit;
	int    dir;
	double r;
	int x;

	unit = tile_size;
	int y = (int)((round(j) / unit));

	dir = sign_of(cos(deg_to_rad(inf->ray)));
	if (dir < 0)
		x = (int)(round(i) / unit) - 1;
	else
		x = (int)(round(i) / unit);
	if (y < 0 || x < 0 || y > pd->max_height ||\
	x > ft_len(pd->map[y]) )
	{
		inf->flag = -1; //kandiro hadafor flaging a point that is outside the map\
						so that we could ignore the distance of this collision later (-1 for vertical and -2 for horiizontal);
						//then ofc reset the flag to 0 after every time we check it;
		return (0);
	}
	if (i == unit || j == unit || pd->map[y][x] == '1' || pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		// printf("went here v\n");
		// put_point(inf, i, j, 2);
		inf->v_i = i;
		inf->v_j = j;
		return (0);
	}
	if (!fmod(round(i), tile_size) && !fmod(round(j), tile_size))
		return (checK_four_squares(inf, i, j, 2));
	return (1);
}

void v_intersections(t_inf *inf)
{
	double di = 0;
	double dj = 0;
	double ti = 0;
	double tj = 0;
 
	if ((fmod(inf->pj, tile_size)))
	{
		if (sign_of(cos(deg_to_rad(inf->ray))) == -1)
			di = fmod(inf->pi, tile_size) * (-1);
		else
			di = (tile_size - fmod(inf->pi, tile_size));
	}
	else
		di = tile_size * sign_of(cos(deg_to_rad(inf->ray)));

	dj = di * tan(deg_to_rad(inf->ray));

	tj = (tile_size * tan(deg_to_rad(inf->ray))) * sign_of(cos(deg_to_rad(inf->ray)));
	ti = tile_size * (sign_of(cos(deg_to_rad(inf->ray))));

	while (check_points_v(inf->pi + di, inf->pj + dj, inf->pd, inf))
	{
		dj += tj;
		di += ti;
	} 
}

void h_intersections(t_inf *inf)
{
	double di = 0;
	double dj = 0;
	double ti = 0;
	double tj = 0;
 
	if ((fmod(inf->pj, tile_size)))
	{
		if (sign_of(sin(deg_to_rad(inf->ray))) == -1)
			dj = fmod(inf->pj, tile_size) * (-1);
		else
			dj = (tile_size - fmod(inf->pj, tile_size));
	}
	else
		dj = tile_size * sign_of(sin(deg_to_rad(inf->ray)));

	di = dj / tan(deg_to_rad(inf->ray));

	ti = (tile_size / tan(deg_to_rad(inf->ray))) * sign_of(sin(deg_to_rad(inf->ray)));
	tj = tile_size * (sign_of(sin(deg_to_rad(inf->ray))));

	while (check_points_h(inf->pi + di, inf->pj + dj, inf->pd, inf))
	{
		dj += tj;
		di += ti;
	} 
}

double  min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

void    calc_col_dis(t_inf *inf)
{
	double  d_h;
	double  d_v;

	if (inf->flag == -2 || inf->flag == -1)
	{
		if (inf->flag == -2)
		{
			inf->col_dist[inf->index] = ((inf->v_i - inf->pi) * (inf->v_i - inf->pi)) + ((inf->v_j - inf->pj) * (inf->v_j - inf->pj));
			inf->col_dist[inf->index] = sqrt(inf->col_dist[inf->index]);
			inf->flag = 0;
		}
		else
		{
			inf->col_dist[inf->index] = ((inf->h_i - inf->pi) * (inf->h_i - inf->pi)) + ((inf->h_j - inf->pj) * (inf->h_j - inf->pj));
			inf->col_dist[inf->index] = sqrt(inf->col_dist[inf->index]);
			inf->flag = 0;
		}
	}
	else
	{
		d_h = ((inf->h_i - inf->pi) * (inf->h_i - inf->pi)) + ((inf->h_j - inf->pj) * (inf->h_j - inf->pj));
		d_h = sqrt(d_h);
		d_v = ((inf->v_i - inf->pi) * (inf->v_i - inf->pi)) + ((inf->v_j - inf->pj) * (inf->v_j - inf->pj));
		d_v = sqrt(d_v);
		inf->col_dist[inf->index] = min(d_h, d_v);
	}
}

int	key_hook(int keycode, t_inf *inf)
{
	double  new_i;
	double  new_j;

	if (keycode == 126)
	{
		new_i = inf->pi + (8 * cos(deg_to_rad(inf->fov)));
		new_j = inf->pj + (8 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new_j / tile_size)][(int)(inf->pi / tile_size)] != '1' &&\
		inf->pd->map[(int)(inf->pj / tile_size)][(int)(new_i / tile_size)] != 1 && \
		inf->pd->map[(int)(new_j / tile_size)][(int)(new_i / tile_size)] != '1')
			redisplay_move(new_i, new_j, inf, keycode);
	}
	if (keycode == 125)
	{
		new_i = inf->pi - (8 * cos(deg_to_rad(inf->fov)));
		new_j = inf->pj - (8 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new_j / tile_size)][(int)(inf->pi / tile_size)] != '1' &&\
		inf->pd->map[(int)(inf->pj / tile_size)][(int)(new_i / tile_size)] != 1 && \
		inf->pd->map[(int)(new_j / tile_size)][(int)(new_i / tile_size)] != '1')
			redisplay_move(new_i, new_j, inf, keycode);
		
	}
	if (keycode == 2 || !keycode)
		redisplay_view(inf, keycode);
	return (0);
}

void    redisplay_view(t_inf *inf, int keycode)
{
	mlx_clear_window(inf->mlx, inf->win_ptr);
	inf->ray = inf->fov - 30;
	inf->index = 0;
	while (inf->ray <= inf->fov + 30)
	{
		ray(inf, deg_to_rad(inf->ray), inf->pd, 0);
		inf->ray += 0.04;
		inf->index++;
	}
	if (keycode == 2)
		inf->fov += inf->step;
	else
		inf->fov -= inf->step;
	inf->ray = inf->fov - 30;
	inf->index = 0;
	while (inf->ray <= inf->fov + 30)
	{
		h_intersections(inf);
		v_intersections(inf);
		calc_col_dis(inf);
		ray(inf, deg_to_rad(inf->ray), inf->pd, 1);
		inf->ray += 0.04;
		inf->index++;
	}
		// mlx_destroy_image(inf->mlx, inf->g_img.img_ptr);
		// inf->g_img.img_ptr = mlx_new_image(inf->mlx, 1501, inf->pd->max_height * tile_size);
		// inf->g_img.adrr = mlx_get_data_addr(inf->g_img.img_ptr, &inf->g_img.bpp, &inf->g_img.size_line, &inf->g_img.endian);
		draw_sma_wlard(inf);
		render_3d(inf);
		mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->g_img.img_ptr, 0, 0);
		mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->img.img_ptr, 0, 0);
}

void    redisplay_move(double new_i, double new_j, t_inf *inf, int keycode)
{
		inf->index = 0;
		inf->ray = inf->fov - 30;
		mlx_clear_window(inf->mlx, inf->win_ptr);
		while (inf->ray <= inf->fov + 30)
		{
			ray(inf, deg_to_rad(inf->ray), inf->pd, 0);
			inf->ray += 0.04;
			inf->index++;
		}
		inf->index = 0;
		inf->ray = inf->fov - 30;
		inf->pi = new_i;
		inf->pj = new_j;
		while (inf->ray <= inf->fov + 30)
		{
			h_intersections(inf);
			v_intersections(inf);
			calc_col_dis(inf);
			ray(inf, deg_to_rad(inf->ray), inf->pd, 1);
			inf->ray += 0.04;
			inf->index++;
		}
		// mlx_destroy_image(inf->mlx, inf->g_img.img_ptr);
		// inf->g_img.img_ptr = mlx_new_image(inf->mlx, 1501, inf->pd->max_height * tile_size);
		// inf->g_img.adrr = mlx_get_data_addr(inf->g_img.img_ptr, &inf->g_img.bpp, &inf->g_img.size_line, &inf->g_img.endian);
		draw_sma_wlard(inf);
		render_3d(inf);
		mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->g_img.img_ptr, 0, 0);
		mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->img.img_ptr, 0, 0);
}

int main(int ac, char **av)
{
	t_inf   inf;
	t_pd    pd;

	inf.step = 8;
	inf.flag = 0;
	inf.col_dist = malloc(sizeof(double) * 1501);
	pd = m_function(ac, av);
	inf.pd = &pd;
	inf.mlx = mlx_init();
	inf.win_ptr = mlx_new_window(inf.mlx, 1501, pd.max_height * 60, "3D");
	printf("width = %d\nheight = %d\n", 1501 , pd.max_height * 60);
	inf.img.img_ptr = mlx_new_image(inf.mlx, pd.max_width * 10, pd.max_height * 10); //check later;
	// inf.img.img_ptr = mlx_new_image(inf.mlx, pd.max_width * tile_size, pd.max_height * tile_size); //check later;
	inf.img.adrr = mlx_get_data_addr(inf.img.img_ptr, &inf.img.bpp, &inf.img.size_line, &inf.img.endian);
	inf.g_img.img_ptr = mlx_new_image(inf.mlx, 1501, pd.max_height * tile_size);
	inf.g_img.adrr = mlx_get_data_addr(inf.g_img.img_ptr, &inf.g_img.bpp, &inf.g_img.size_line, &inf.g_img.endian);
	m_fill(&inf, pd);
	put_player(&inf, &pd, 1);
	// inf.fov = 5;
	// inf.fov = 0;
	inf.ray = inf.fov - 30;
	inf.index = 0;
	// inf.fov = 0;
	while (inf.ray <= inf.fov + 30)
	{
		h_intersections(&inf);
		v_intersections(&inf);
		calc_col_dis(&inf);
		ray(&inf, deg_to_rad(inf.ray), inf.pd, 1);
		inf.ray += 0.04;
		inf.index++;
		// printf("index =%d\n", inf.index);

	}
	draw_sma_wlard(&inf);
	render_3d(&inf);
	mlx_put_image_to_window(inf.mlx, inf.win_ptr, inf.g_img.img_ptr, 0, 0);
	mlx_put_image_to_window(inf.mlx, inf.win_ptr, inf.img.img_ptr, 0, 0);
	mlx_hook(inf.win_ptr, 2, 0, key_hook, &inf);
	mlx_loop(inf.mlx);
}
