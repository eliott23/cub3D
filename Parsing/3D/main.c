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
    if (j >= 299 && j <= 301 && i <= 541 && i >= 539)
        printf("i = %d\nj = %d\n", i, j);
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
int	key_hook(int keycode, t_inf *inf)
{
    printf("keycode %d\n", keycode);
    if (keycode == 125)
    {
        
    }
    if (keycode == 2)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov + inf->step), inf->pd, 1);
        inf->fov += inf->step;
    }
    if (!keycode)
    {
        ray(inf, deg_to_rad(inf->fov), inf->pd, 0);
        ray(inf, deg_to_rad(inf->fov - inf->step), inf->pd, 1);
        inf->fov -= inf->step;
    }
	return (0);
}

void    put_rays()
{
}


int main(int ac, char **av)
{
    t_inf   inf;
    t_pd    pd;

    inf.fov = 0;
    inf.step = 5;
    pd = m_function(ac, av);
    inf.pd = &pd;
    inf.mlx = mlx_init();
    inf.win_ptr = mlx_new_window(inf.mlx, pd.max_width * 60, pd.max_height * 60, "3D");
    m_fill(&inf, pd);
    put_player(&inf, &pd, 0);
    put_lines(&inf, pd);
    ray(&inf, deg_to_rad(inf.fov), &pd, 1);
    printf("pi = %d pj = %d\n", inf.pi, inf.pj);
    // mlx_key_hook(inf.win_ptr, key_hook, &inf);
    mlx_hook(inf.win_ptr, 02, 0, key_hook, &inf);
    mlx_loop(inf.mlx);
}