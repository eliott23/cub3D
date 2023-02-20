#include "d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color, int mode)
{
	int		offset;
	char	*pixel;
	//to get the position of the current pixel
	//bpp is devided by 8 cus its already multiplied by 8 (a pixel is coded on 4 char, those chars worth 8 bits each)
	//(X position * 4 + 4 * Line size * Y position)
	if (mode == 1)
	{
		x /= 6;
		y /= 6;
	}
	offset = y * img->size_line + x * (img->bpp / 8);
	pixel = img->adrr + offset;
	*(unsigned int *)pixel = color;
}

void	draw_sma_wlard(t_inf *inf)
{
	int	i;
	int	j;
	int	max_height;
	int	half_max;
	int sqef = create_trgb(0, ft_atoi(inf->pd->sqef[0]), ft_atoi(inf->pd->sqef[1]), ft_atoi(inf->pd->sqef[2])), floor = create_trgb(0, ft_atoi(inf->pd->floor[0]), ft_atoi(inf->pd->floor[1]), ft_atoi(inf->pd->floor[2]));

	i = 0;
	max_height = inf->pd->max_height * tile_size;
	half_max = max_height / 2;
	while (i < 1501)
	{
		j = 0;
		while (j < max_height)
		{
			my_mlx_pixel_put(&inf->frame, i, j, sqef, 0);
			j++;
		}
		while (j < half_max)
		{
			my_mlx_pixel_put(&inf->frame, i, j, floor, 0);
			j++;
		}
		i++;
	}
}

void    render_3d(t_inf *inf)
{
	int i, j;
	double distanceProjPlane = (1500 / 2) / tan(deg_to_rad(60 / 2));
	// double distanceProjPlane = 200;
	double projectionWallHeight;
	double topPixel;
	double bottomPixel;
	int		color = create_trgb(0, 0, 0, 255);
	int deb_color = create_trgb(0, 255, 0, 0);
	int		max_height = inf->pd->max_height * tile_size;
	i = 0;
	while (i < 1501)
	{
		projectionWallHeight = (tile_size / (inf->rays[i].col_dist)) * distanceProjPlane;
		topPixel = (max_height / 2) - (projectionWallHeight / 2);
		bottomPixel = (max_height / 2) + (projectionWallHeight / 2);
		if (topPixel < 0)
			topPixel = 0;
		if (bottomPixel > max_height)
			bottomPixel = max_height;
		while (topPixel < bottomPixel)
		{
			if (inf->rays[i].h_v == 1)
			{
				my_mlx_pixel_put(&inf->frame, i, topPixel, color, 0);
			}
			else
			{
				my_mlx_pixel_put(&inf->frame, i, topPixel, deb_color, 0);
			}
			topPixel++;
		}
		i++;
	}
}

void    ray(t_inf *inf, double angle, t_pd *pd, int m)
{
	int l = 0;
	int t = inf->p.i;
	int t2 = inf->p.j;
	int lim;

	lim = (int)inf->rays[inf->index].col_dist;
	while (l < lim)
	{
		t =  inf->p.i + (l * cos(angle));
		t2 = inf->p.j + (l * sin(angle));
		// if (t < 0 || t >= pd->max_width * tile_size || t2 >= pd->max_height * tile_size || t2 < 0)
		// 	break ;
		if (m)
			my_mlx_pixel_put(&inf->mini_map, t, t2, create_trgb(50, 255, 0, 0), 1);
		// else if ((t % tile_size) && (t2 % tile_size))
			// my_mlx_pixel_put(inf, t, t2, create_trgb(0, 192, 192, 192));
		else
			my_mlx_pixel_put(&inf->mini_map, t, t2, create_trgb(0, 192, 192, 192), 1);
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
				my_mlx_pixel_put(&inf->mini_map, i, j, create_trgb(0, 192, 192, 192), 1);
			else if (pd.map[j / tile_size][i / tile_size] == '1')
				my_mlx_pixel_put(&inf->mini_map, i, j, create_trgb(0, 32, 32, 32), 1);
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
	if ((int)round(i) == tile_size || (int)round(j) == tile_size || inf->pd->map[y][x] == '1' || !inf->pd->map[y][x])//check spaces
	{
		if (m == 1)
			inf->h = (t_index) {i, j};
		else
			inf->v = (t_index) {i, j};
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
	int    dir;
	double r;
	int y;
	int x;

	x = (int)((round(i) / tile_size));
	dir = sign_of(sin(deg_to_rad(inf->ray)));
	if (dir < 0)
		y = (int)(round(j) / tile_size) - 1;
	else
		y = (int)(round(j) / tile_size);
	if (y < 0 || x < 0 || y > pd->max_height ||\
	x > ft_len(pd->map[y]))
	{
		inf->flag = -2; //check description in the check_point_v() function;
		return (0);
	}
	if ((int)round(i) == tile_size || (int)round(j) == tile_size || pd->map[y][x] == '1' || pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		// put_point(inf, i, j, 1);
		inf->h = (t_index) {i, j};
		return (0);
	}
	if (!fmod(round(i), tile_size) && !fmod(round(j), tile_size))
	{ 
		inf->h.flag = -1;
		return (checK_four_squares(inf, i, j, 1));
	}
	return (1);
}

int check_points_v(double i, double j, t_pd *pd, t_inf *inf)
{
	int    dir;
	double r;
	int x;

	int y = (int)((round(j) / tile_size));

	dir = sign_of(cos(deg_to_rad(inf->ray)));
	if (dir < 0)
		x = (int)(round(i) / tile_size) - 1;
	else
		x = (int)(round(i) / tile_size);
	if (y < 0 || x < 0 || y > pd->max_height ||\
	x > ft_len(pd->map[y]) )
	{
		inf->flag = -1; //kandiro hadafor flaging a point that is outside the map\
						so that we could ignore the distance of this collision later (-1 for vertical and -2 for horiizontal);
						//then ofc reset the flag to 0 after every time we check it;
		return (0);
	}
	if ((int)round(i) == tile_size || (int)round(j) == tile_size || pd->map[y][x] == '1' || pd->map[y][x] == ' ' || !pd->map[y][x])
	{
		// put_point(inf, i, j, 2);
		inf->v = (t_index) {i, j};
		return (0);
	}
	if (!fmod(round(i), tile_size) && !fmod(round(j), tile_size))
	{
		inf->v.flag = -1;
		return (checK_four_squares(inf, i, j, 2));
	}
	return (1);
}

void v_intersections(t_inf *inf)
{
	t_index	d;
	t_index	t;

	d = (t_index) {0.0, 0.0};
	t = (t_index) {0.0, 0.0};
	if ((fmod(inf->p.j, tile_size)))
	{
		if (sign_of(cos(deg_to_rad(inf->ray))) == -1)
			d.i = fmod(inf->p.i, tile_size) * (-1);
		else
			d.i = (tile_size - fmod(inf->p.i, tile_size));
	}
	else
		d.i = tile_size * sign_of(cos(deg_to_rad(inf->ray)));

	d.j = d.i * tan(deg_to_rad(inf->ray));

	t.j = (tile_size * tan(deg_to_rad(inf->ray))) * sign_of(cos(deg_to_rad(inf->ray)));
	t.i = tile_size * (sign_of(cos(deg_to_rad(inf->ray))));

	while (check_points_v(inf->p.i + d.i, inf->p.j + d.j, inf->pd, inf))
	{
		d.j += t.j;
		d.i += t.i;
	} 
}

void h_intersections(t_inf *inf)
{
	t_index	d;
	t_index	t;

	d = (t_index) {0.0, 0.0};
	t = (t_index) {0.0, 0.0};
	if ((fmod(inf->p.j, tile_size)))
	{
		if (sign_of(sin(deg_to_rad(inf->ray))) == -1)
			d.j = fmod(inf->p.j, tile_size) * (-1);
		else
			d.j = (tile_size - fmod(inf->p.j, tile_size));
	}
	else
		d.j = tile_size * sign_of(sin(deg_to_rad(inf->ray)));

	d.i = d.j / tan(deg_to_rad(inf->ray));

	t.i = (tile_size / tan(deg_to_rad(inf->ray))) * sign_of(sin(deg_to_rad(inf->ray)));
	t.j = tile_size * (sign_of(sin(deg_to_rad(inf->ray))));

	while (check_points_h(inf->p.i + d.i, inf->p.j + d.j, inf->pd, inf))
	{
		d.j += t.j;
		d.i += t.i;
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

	inf->rays[inf->index].h_v = 0;
	if (inf->flag == -2 || inf->flag == -1)
	{
		if (inf->flag == -2)
		{
			inf->rays[inf->index].col_dist = ((inf->v.i - inf->p.i) * (inf->v.i - inf->p.i)) + ((inf->v.j - inf->p.j) * (inf->v.j - inf->p.j));
			inf->rays[inf->index].col_dist = sqrt(inf->rays[inf->index].col_dist);
			inf->flag = 0;
			inf->rays[inf->index].h_v = 2;
			// inf->rays[inf->index].hitV = 0;
		}
		else
		{
			inf->rays[inf->index].col_dist = ((inf->h.i - inf->p.i) * (inf->h.i - inf->p.i)) + ((inf->h.j - inf->p.j) * (inf->h.j - inf->p.j));
			inf->rays[inf->index].col_dist = sqrt(inf->rays[inf->index].col_dist);
			inf->rays[inf->index].h_v = 1;
			// inf->rays[inf->index].hitH = 0;
			inf->flag = 0;
		}
	}
	else
	{
	// printf("this is the v_flag !!= %d\n", inf->v.flag);
		d_h = ((inf->h.i - inf->p.i) * (inf->h.i - inf->p.i)) + ((inf->h.j - inf->p.j) * (inf->h.j - inf->p.j));
		d_h = sqrt(d_h);
		d_v = ((inf->v.i - inf->p.i) * (inf->v.i - inf->p.i)) + ((inf->v.j - inf->p.j) * (inf->v.j - inf->p.j));
		d_v = sqrt(d_v);
		inf->rays[inf->index].col_dist = min(d_h, d_v);
		// printf("%d\n", (int)inf->rays[inf->index].col_dist);
		if (inf->rays[inf->index].col_dist == d_h)
			inf->rays[inf->index].h_v = 1;
		else
		{
			printf("went here\n");
			inf->rays[inf->index].h_v = 2;
		}
	}
}

int	key_hook(int keycode, t_inf *inf)
{
	double  new_i;
	double  new_j;

	if (keycode == 126)
	{
		new_i = inf->p.i + (8 * cos(deg_to_rad(inf->fov)));
		new_j = inf->p.j + (8 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new_j / tile_size)][(int)(inf->p.i / tile_size)] != '1' &&\
		inf->pd->map[(int)(inf->p.j / tile_size)][(int)(new_i / tile_size)] != 1 && \
		inf->pd->map[(int)(new_j / tile_size)][(int)(new_i / tile_size)] != '1')
			redisplay_move(new_i, new_j, inf, keycode);
	}
	if (keycode == 125)
	{
		new_i = inf->p.i - (8 * cos(deg_to_rad(inf->fov)));
		new_j = inf->p.j - (8 * sin(deg_to_rad(inf->fov)));
		if (inf->pd->map[(int)(new_j / tile_size)][(int)(inf->p.i / tile_size)] != '1' &&\
		inf->pd->map[(int)(inf->p.j / tile_size)][(int)(new_i / tile_size)] != 1 && \
		inf->pd->map[(int)(new_j / tile_size)][(int)(new_i / tile_size)] != '1')
			redisplay_move(new_i, new_j, inf, keycode);
		
	}
	if (keycode == 2)
		redisplay_view(inf, keycode);
	if (!keycode)
		redisplay_view(inf, keycode);
	return (0);
}

void    redisplay_view(t_inf *inf, int keycode)
{
	mlx_clear_window(inf->mlx, inf->win_ptr);
	castAllRays(inf, 0);
	if (keycode == 2)
		inf->fov += inf->step;
	else
		inf->fov -= inf->step;
	castAllRays(inf, 1);
	draw_sma_wlard(inf);
	render_3d(inf);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->frame.img_ptr, 0, 0);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->mini_map.img_ptr, 0, 0);
}

void    redisplay_move(double new_i, double new_j, t_inf *inf, int keycode)
{

	mlx_clear_window(inf->mlx, inf->win_ptr);
	castAllRays(inf, 0);
	inf->p.i = new_i;
	inf->p.j = new_j;
	castAllRays(inf, 1);
	draw_sma_wlard(inf);
	render_3d(inf);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->frame.img_ptr, 0, 0);
	mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->mini_map.img_ptr, 0, 0);
}

int main(int ac, char **av)
{
	t_inf   *inf;
	t_pd    pd;

	inf = malloc(sizeof(t_inf));
	pd = m_function(ac, av);
	inf->pd = &pd;
	inf->step = 5;
	inf->flag = 0;
	inf->rays = malloc(sizeof(t_rays) * (1501));
	// printf("this is the number of rays %d\n", (pd.max_height * tile_size) + 1);
	// exit(0);
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window(inf->mlx, 1501, pd.max_height * tile_size, "cub3d");
	inf->mini_map.img_ptr = mlx_new_image(inf->mlx, (pd.max_width * tile_size) / 6, (pd.max_height * tile_size) / 6); // minimap dimensions and drawing conditions to be checked later
	inf->mini_map.adrr = mlx_get_data_addr(inf->mini_map.img_ptr, &inf->mini_map.bpp, &inf->mini_map.size_line, &inf->mini_map.endian);
	inf->frame.img_ptr = mlx_new_image(inf->mlx, 1501, pd.max_height * tile_size);
	inf->frame.adrr = mlx_get_data_addr(inf->frame.img_ptr, &inf->frame.bpp, &inf->frame.size_line, &inf->frame.endian);
	launch(inf);
	mlx_hook(inf->win_ptr, 2, 0, key_hook, inf);
	mlx_loop(inf->mlx);
}

