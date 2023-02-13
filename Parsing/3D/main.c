#include "d.h"

int check_obs(t_pd *pd, int i, int j)
{
    if (pd->map[j / 60][i / 60] == '1')
        return (1);
    return (0);
}

int calc_cord(double angle, int l, int j, int i, t_pd *pd)
{
    if (!pd->map[j / 60])
        return (0);
    if (pd->map[j / 60][i / 60] == '1' || pd->map[j / 60][(i + 1) / 60] == '1')
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
    {
        printf("sin is positive\n");
        return (1);
    }
    else
    {
        printf("sin is negative\n");
        return (-1);
    }
}

void check_point(t_inf *inf)
{
    double di = 0;
    double dj = 0;
 
    if ((fmod(inf->pj, 60)))
    {
        if (sign_of(sin(deg_to_rad(inf->fov))) == -1)
            dj = fmod(inf->pj, 60) * (-1);
        else
            dj = (60 - fmod(inf->pj, 60));
        printf("this is dj = %f\n", dj);
        printf("this is inf->pj = %f\n", inf->pj);
        printf("this is fmod = %f\n", fmod(inf->pj, 60));
    }
    else
    {
        dj = 60 * sign_of(sin(deg_to_rad(inf->fov)));
    }
    di = dj / tan(deg_to_rad(inf->fov));
    printf("this is di %f\n", di);
    printf("rx =%f\nrj = %f\n", inf->pi + di, inf->pj + dj);
    put_point(inf, inf->pi + di, inf->pj + dj);
}

int	key_hook(int keycode, t_inf *inf)
{
    int t2;
    int t1;

    printf("keycode %d\n", keycode);
    if (keycode == 126)
    {
        t1 = inf->pi;
        t2 = inf->pj;
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        inf->pi += (8 * cos(deg_to_rad(inf->fov)));
        inf->pj += (8 * sin(deg_to_rad(inf->fov)));
        printf("fov = %f\n", inf->fov);
        printf("forward -> pi : %f\n", inf->pi - t1);
        printf("forward -> pj : %f\n", inf->pj- t2);
        ray(inf, deg_to_rad(inf->fov), inf->pd, 1);
        check_point(inf);
    }
    if (keycode == 125)
    {
        t1 = inf->pi;
        t2 = inf->pj;
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        inf->pi -= ( 8 * cos(deg_to_rad(inf->fov)));
        inf->pj -= ( 8 * sin(deg_to_rad(inf->fov)));
        printf("fov = %f\n", inf->fov);
        printf("backward -> pi : %f\n", inf->pi - t1);
        printf("backward -> pj : %f\n", inf->pj- t2);
        ray(inf, deg_to_rad(inf->fov), inf->pd, 1);
        check_point(inf);
    }
    if (keycode == 2)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov + inf->step), inf->pd, 1);
        inf->fov += inf->step;
        check_point(inf);
    }
    if (!keycode)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov - inf->step), inf->pd, 1);
        inf->fov -= inf->step;
        check_point(inf);
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

    inf.fov = 225;
    inf.step = 4;
    pd = m_function(ac, av);
    inf.pd = &pd;
    inf.mlx = mlx_init();
    inf.win_ptr = mlx_new_window(inf.mlx, pd.max_width * 60, pd.max_height * 60, "3D");
    m_fill(&inf, pd);
    put_player(&inf, &pd, 1);
    put_lines(&inf, pd);
    ray(&inf, deg_to_rad(inf.fov), inf.pd, 1);
    // put_rays(&inf, 0);
    printf("pi = %f pj = %f\n", inf.pi, inf.pj);
    check_point(&inf);
    mlx_hook(inf.win_ptr, 2, 0, key_hook, &inf);
    mlx_loop(inf.mlx);
}