#include "d.h"

int calc_cord(double angle, int l, int j, int i, t_pd *pd)
{
    if (!pd->map[j / 60])
        return (0);
    // if (pd->map[j / 60][i / 60] == '1' || pd->map[j / 60][(i + 1) / 60] == '1')
    //     return (0);
    if (pd->map[j / 60][i / 60] == '1')
        return (0);
    return (1);
}

void    ray(t_inf *inf, double angle, t_pd *pd, int m)
{
    int l = 0;
    int t = inf->pi;
    int t2 = inf->pj;

    while (calc_cord(angle, l, t2, t, pd))
    {
        t =  inf->pi + (l * cos(angle));
        t2 = inf->pj + (l * sin(angle));
        if (m)
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(50, 255, 0, 0));
        else if ((t % 60) && (t2 % 60)) 
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(0, 192, 192, 192));
        else
            mlx_pixel_put(inf->mlx, inf->win_ptr, t, t2, create_trgb(100, 32, 32, 32));
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
    while (j < pd.max_height * 60)
    {
        i = 0;
        while (i < pd.max_width * 60)
        {
            if (!pd.map[j / 60][i / 60])
                break;
            if (pd.map[j / 60][i / 60] == '0' || pd.map[j / 60][i / 60] == 'N') //check later;
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 192, 192, 192));
            else
                mlx_pixel_put(inf->mlx, inf->win_ptr, i, j, create_trgb(0, 32, 32, 32));
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

int check_points_h(double i, double j, t_pd *pd, t_inf *inf)
{
    double unit;
    int    dir;
    double r;
    int y;
    int x;

    unit = 60;
    x = (int)((round(i) / unit));
    if (!fmod(round(i), 60) && sign_of(cos(deg_to_rad(inf->fov))) == -1)
    {
        x -= 1;
        printf("yep\n");
    }
    dir = sign_of(sin(deg_to_rad(inf->fov)));
    if (dir < 0)
        y = (int)(round(j) / unit) - 1;
    else
        y = (int)(round(j) / unit);
    // printf("i = %f=%d\n j = %f=%d\n", i, x, j ,y);
    if (y < 0 || x < 0 || y > pd->max_height ||\
    x > ft_len(pd->map[y]) )
    {
        // printf("i = %f=%d\n j = %f=%d\n", i, x, j ,y);
        // printf("went here\n");
        return (0);
    }
    if (i == unit || j == unit || pd->map[y][x] == '1' || !pd->map[y][x])
    {
    // printf(" int the collision :\
    // \ni = %f=%d\n j = %f=%d\n", i,x, j ,y);
    // printf("j / unit = %f\n", j / unit);
    //     printf("went here 2\n");
        put_point(inf, i, j, 1);
        return (0);
    }
    printf("i = %f=%d\n j = %f=%d\n", i,x, j ,y);
    printf("j / unit = %f\n", j / unit);
        printf("went here 2\n");
    return (1);
}

int check_points_v(double i, double j, t_pd *pd, t_inf *inf)
{
    double unit;
    int    dir;
    double r;
    int x;

    unit = 60;
    int y = (int)((round(j) / unit));
//    if (!fmod(round(j), 60) && sign_of(sin(deg_to_rad(inf->fov))) == -1)
//     {
//         y -= 1;
//         printf("yep\n");
//     }
    dir = sign_of(cos(deg_to_rad(inf->fov)));
    if (dir < 0)
        x = (int)(round(i) / unit) - 1;
    else
        x = (int)(round(i) / unit);
    // printf("i = %f=%d\n j = %f=%d\n", i, x, j ,y);
    if (y < 0 || x < 0 || y > pd->max_height ||\
    x > ft_len(pd->map[y]) )
    {
        // printf("i = %f=%d\n j = %f=%d\n", i, x, j ,y);
        // printf("went here\n");
        return (0);
    }
    if (i == unit || j == unit || pd->map[y][x] == '1' || !pd->map[y][x])
    {
    // printf(" int the collision :\
    // \ni = %f=%d\n j = %f=%d\n", i,x, j ,y);
    // printf("j / unit = %f\n", j / unit);
    //     printf("went here 2\n");
        put_point(inf, i, j, 2);
        return (0);
    }
    // printf("i = %f=%d\n j = %f=%d\n", i,x, j ,y);
    // printf("j / unit = %f\n", j / unit);
    //     printf("went here 2\n");
    return (1);
}

void v_intersections(t_inf *inf)
{
    double di = 0;
    double dj = 0;
    double ti = 0;
    double tj = 0;
 
    if ((fmod(inf->pj, 60)))
    {
        if (sign_of(cos(deg_to_rad(inf->fov))) == -1)
            di = fmod(inf->pi, 60) * (-1);
        else
            di = (60 - fmod(inf->pi, 60));
    }
    else
        di = 60 * sign_of(cos(deg_to_rad(inf->fov)));

    dj = di * tan(deg_to_rad(inf->fov));

    tj = (60 * tan(deg_to_rad(inf->fov))) * sign_of(cos(deg_to_rad(inf->fov)));
    ti = 60 * (sign_of(cos(deg_to_rad(inf->fov))));

    // int i = 0;
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
 
    if ((fmod(inf->pj, 60)))
    {
        if (sign_of(sin(deg_to_rad(inf->fov))) == -1)
            dj = fmod(inf->pj, 60) * (-1);
        else
            dj = (60 - fmod(inf->pj, 60));
    }
    else
        dj = 60 * sign_of(sin(deg_to_rad(inf->fov)));

    di = dj / tan(deg_to_rad(inf->fov));

    ti = (60 / tan(deg_to_rad(inf->fov))) * sign_of(sin(deg_to_rad(inf->fov)));
    tj = 60 * (sign_of(sin(deg_to_rad(inf->fov))));

    while (check_points_h(inf->pi + di, inf->pj + dj, inf->pd, inf))
    {
        dj += tj;
        di += ti;
    } 
}

int	key_hook(int keycode, t_inf *inf)
{
    int t2;
    int t1;

    if (keycode == 126)
    {
        t1 = inf->pi;
        t2 = inf->pj;
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        inf->pi += (8 * cos(deg_to_rad(inf->fov)));
        inf->pj += (8 * sin(deg_to_rad(inf->fov)));
        ray(inf, deg_to_rad(inf->fov), inf->pd, 1);
        h_intersections(inf);
        v_intersections(inf);
    }
    if (keycode == 125)
    {
        t1 = inf->pi;
        t2 = inf->pj;
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        inf->pi -= ( 8 * cos(deg_to_rad(inf->fov)));
        inf->pj -= ( 8 * sin(deg_to_rad(inf->fov)));
        ray(inf, deg_to_rad(inf->fov), inf->pd, 1);
        h_intersections(inf);
        v_intersections(inf);
    }
    if (keycode == 2)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov + inf->step), inf->pd, 1);
        inf->fov += inf->step;
        h_intersections(inf);
        v_intersections(inf);
    }
    if (!keycode)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov - inf->step), inf->pd, 1);
        inf->fov -= inf->step;
        h_intersections(inf);
        v_intersections(inf);
    }
	return (0);
}

void    put_rays(t_inf *inf, int m)
{
    double i;

    i = inf->fov - 10;
        while (i <= inf->fov + 10)
        {
            ray(inf, deg_to_rad(i), inf->pd, !m);
            i++;
        }
}

int main(int ac, char **av)
{
    t_inf   inf;
    t_pd    pd;

    inf.fov = 135;
    inf.step = 3;
    pd = m_function(ac, av);
    printf("max width = %d\nmax_height = %d\n", pd.max_width, pd.max_height);
    inf.pd = &pd;
    inf.mlx = mlx_init();
    inf.win_ptr = mlx_new_window(inf.mlx, pd.max_width * 60, pd.max_height * 60, "3D");
    m_fill(&inf, pd);
    put_player(&inf, &pd, 1);
    put_lines(&inf, pd);
    ray(&inf, deg_to_rad(inf.fov), inf.pd, 1);
    h_intersections(&inf);
    v_intersections(&inf);
    mlx_hook(inf.win_ptr, 2, 0, key_hook, &inf);
    mlx_loop(inf.mlx);
}