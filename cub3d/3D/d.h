/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:32:55 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/23 05:28:01 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_H
# define D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "../Parsing/p.h"
# define TILE_SIZE	64
# define WIN_WIDTH	1500
# define WIN_HEIGHT	1000

typedef struct s_index
{
	double	i;
	double	j;
}	t_index;

typedef struct s_rays
{
	double	col_dist;
	int		flag;
	double	ray_angle;
	int		x;
	int		h_v;
}	t_rays;

typedef struct s_img
{
	void	*img_ptr;
	char	*adrr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_xmp
{
	t_img	img;
	int		width;
	int		height;
}	t_xpm;

typedef struct inf{
	int		f_col;
	int		c_col;
	void	*win_ptr;
	void	*mlx;
	t_img	frame;
	t_xpm	*textures;
	t_index	p;
	t_index	h;
	t_index	v;
	double	fov;
	double	ray;
	t_pd	*pd;
	int		step;
	int		index;
	t_rays	*rays;
	int		flag;
	int		m_h;
	int		w_h;
}	t_inf;

/** hooks **/

void	up_down(int keycode, t_inf *inf, t_index new);
void	left_right(int keycode, t_inf *inf, t_index new);
int		key_hook(int keycode, t_inf *inf);
void	redisplay_view(t_inf *inf, int keycode);
void	redisplay_move(double new_i, double new_j, t_inf *inf);

/** ray casting **/

int		check_points_h(double i, double j, t_pd *pd, t_inf *inf);
int		check_points_v(double i, double j, t_pd *pd, t_inf *inf);
void	get_colors(t_inf *inf, t_pd *pd);
void	cast_all_rays(t_inf *inf, int m);
void	render_3d(t_inf *inf);
void	v_intersections(t_inf *inf);
void	h_intersections(t_inf *inf);
int		check_square(t_inf *inf, int x, int y, t_index i, int m);
int		check_four_squares(t_inf *inf, t_index i, int m);

/** utils **/

void	outside_map(t_inf *inf);
void	put_player(t_inf *inf, t_pd *pd);
int		create_trgb(int t, int r, int g, int b);
double	deg_to_rad(double angle);
void	calc_col_dis(t_inf *inf);
int		xpm_init(t_inf *inf);
void	draw_sma_wlard(t_inf *inf, int i, int j, int x);
void	launch(t_inf *inf);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_pixel(t_inf *inf, int i, int y);
double	min(double a, double b);
int		create_trgb(int t, int r, int g, int b);
int		sign_of(double n);
t_index	check(double i, double j, int max_height);

#endif 