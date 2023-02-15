#ifndef D_H
#define D_H
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include "../p.h"

typedef struct inf{
    void    *win_ptr;
    void    *mlx;
    int     *p_w;
    int     *p_h;
    void    *player;
    double     pi;
    double     pj;
    double  fov; 
    t_pd    *pd;
    int     step;
    double  h_i;
    double  h_j;
    double  v_i;
    double  v_j;
    double  col_dist;
    double  o_col_dist;
    int     flag;
}   t_inf;
void    put_point(t_inf *inf, double i, double j, int m);
void    put_player(t_inf *inf, t_pd *pd, int m);
int	create_trgb(int t, int r, int g, int b);
void    put_lines(t_inf *inf, t_pd pd);
#endif 