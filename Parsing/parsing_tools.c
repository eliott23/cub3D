#include "p.h"

int s_cmp(char  *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (0);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if (!s2[i])
        return (0);
    return (1);
}

int element_id(char *s)
{
    int         i;
    static char *elmnt[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", 0};

    i = 0;
    while (elmnt[i])
    {
        if (s_cmp(elmnt[i], s))
            return (i);
        i++;
    }
    printf("lol |%s|", s);
    f_perror();
    return (-1);
}

void    store_path(t_pd *pd, char *path, int e)
{
    if (e == 0)
        pd->no = path;
    if (e == 1)
        pd->so = path;
    if (e == 2)
        pd->we = path;
    if (e == 3)
        pd->ea = path;
    if (e == 4)
    {
        check_RGB(path);
        pd->floor = ft_split(path, ',');
        free(path);
        valid_RGB(pd->floor);
    }
    if (e == 5)
    {
        check_RGB(path);
        pd->sqef = ft_split(path, ',');
        free(path);
        valid_RGB(pd->sqef);
    }
}

void    s_dup(char *s, t_pd *pd, int e)
{
    int     i;
    int     j;
    char    *path;

    i = 0;
    j = 0;
    while (s[i] && s[i] != '\n')
        i++;
    path = malloc(sizeof(char) * (i + 1));
    if (!path)
        f_perror();
    while (j < i)
    {
        path[j] = s[j];
        j++;
    }
    path[j] = 0;
    store_path(pd, path, e);
}

void    m_parsing(t_pd *pd)
{
    int     e;
    char    *path;

    pd->i = 0;
    e = 0;
    while (pd->i_b[pd->i] && pd->n < 6)
    {
        while (pd->i_b[pd->i] == ' ' || pd->i_b[pd->i] == '\n')
            pd->i++;
        if (pd->i && pd->i_b[pd->i - 1] == ' ')
            f_perror();
        e = element_id((pd->i_b) + pd->i);
        check_elmnt_n(1, pd, e);
        skip_to_next(1, pd);
        s_dup(pd->i_b + pd->i, pd, e);
        pd->n++;
        skip_to_next(0, pd);
    }
    while (pd->i_b[pd->i] == '\n' || pd->i_b[pd->i] == ' ')
    {
        if (pd->i_b[pd->i] == ' ')
        {
            if (!check_empty(&pd->i_b[pd->i]))
                break;
        }
        pd->i++;
    }
    map_p(pd);
}