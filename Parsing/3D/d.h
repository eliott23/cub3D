#ifndef D_H
#define D_H
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "../p.h"

# define tile_size 64
# define Black 	        0x000000
# define White          0xFFFFFF
# define Green          0x008000
# define Purple         0x800080
# define Red            0xFF0000
# define LemonChiffon   0xFFFACD
# define HotPink        0xFF69B4
# define FireBrick      0xB22222
# define Coral          0xFF7F50
# define AliceBlue      0xF0F8FF

typedef struct s_img
{
	void	*img_ptr;
	char	*adrr;
	int		bpp; //bits per pixel
	int		size_line;
	int		endian;
} t_img;

typedef struct inf{
	void    *win_ptr;
	void    *mlx;
	t_img   mini_map;
	t_img   frame;
	int     *p_w;
	int     *p_h;
	double  pi;
	double  pj;
	double  fov;
	double  ray;
	t_pd    *pd;
	int     step;
	double  h_i;
	double  h_j;
	double  v_i;
	double  v_j;
	int     index;
	double  *col_dist;
	int     flag;
}   t_inf;

void    put_point(t_inf *inf, double i, double j, int m);
void    put_player(t_inf *inf, t_pd *pd, int m);
int	    create_trgb(int t, int r, int g, int b);
void    put_lines(t_inf *inf, t_pd pd);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color, int mode);
void    redisplay_view(t_inf *inf, int keycode);
void    redisplay_move(double new_i, double new_j, t_inf *inf, int keycode);
void    ray(t_inf *inf, double angle, t_pd *pd, int m);
void	castAllRays(t_inf *inf, int m);
void    render_3d(t_inf *inf);
void	launch(t_inf *inf);
int     calc_cord(double angle, int l, int j, int i, t_pd *pd);
void    m_fill(t_inf *inf, t_pd pd);
void    v_intersections(t_inf *inf);
void    h_intersections(t_inf *inf);
double  deg_to_rad(double angle);
void    calc_col_dis(t_inf *inf);
void	Background(t_inf *data, int color);
#endif 