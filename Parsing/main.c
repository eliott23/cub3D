#include "p.h"

void    fill(char *s)
{
    int i = 0;
    if (s)
    {
        while (s[i])
        {
            s[i] = 0;
            i ++;
        }    
    }
}

char    *m_read(char *name)
{
    int     i;
    int     fd;
    char    *str = NULL;
    char    *temp = NULL;
    char    *temp2 = NULL;

    fd = open(name, O_RDONLY);
    check_fd(fd);
    i = 0;
    str = NULL;
    temp = ft_calloc(sizeof(char) * 100);
    while (read(fd, temp, 100))
    {
        temp2 = ft_strdup(str);
        if (str)
            free(str);
        str = ft_strjoin(temp2, temp);
        if (temp2)
            free(temp2);
        fill(temp);
        i++;
    }
    free(temp);
    return (str);
}

int    check_empty_string(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

void    mesure_dimensions(t_pd *pd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    pd->max_width = 0;
    while (pd->map[i])
    {
        j = 0;
        while (pd->map[i][j] && !check_empty_string(&pd->map[i][j]))
            j++;
        if (j > pd->max_width)
            pd->max_width = j;
        i++;
    }
    pd->max_height = i;
}

t_pd    m_function(int ac, char **av)
{
    t_pd    pd;
    int     fd;

    if (ac != 2)
        f_perror();
    pd.i_b = m_read(av[1]);
    if (!pd.i_b)
        f_perror();
    check_elmnt_n(0, &pd, 0);
    m_parsing(&pd);
    mesure_dimensions(&pd);
/* THIS SECTION WAS COMMENTED TO SILENCE ERRORS ABOUT NON-EXISTING FILES
    fd = open(pd.no, O_RDONLY);
    if (fd == -1)
        f_perror();
    close(fd);
    fd = open(pd.so, O_RDONLY);
    if (fd == -1)
        f_perror();
    close(fd);
    fd = open(pd.ea, O_RDONLY);
    if (fd == -1)
        f_perror();
    close(fd);
    fd = open(pd.we, O_RDONLY);
    if (fd == -1)
        f_perror();
    close(fd);
*/
    return (pd);
    // printf("NO:%s\n", pd.no);
    // printf("SO:%s\n", pd.so);
    // printf("WE:%s\n", pd.we);
    // printf("EA:%s\n", pd.ea);
    // printf("n:%d\n", pd.n);
    // sleep(100);
}