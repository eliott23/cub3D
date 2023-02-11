#include "p.h"

void	check_RGB(char *path)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!path)
		f_perror();
	while (path[i] && path[i] != '\n')
	{
		if (path[i] != ' ' && (path[i] < '0' || path[i] > '9') && path[i] != ',')
			f_perror();
		if (path[i] == ',')
			c++;
		i++;
	}
	if (c != 2)
		f_perror();
}

void	valid_RGB(char **rgb)
{
	int	i;
	
	i = 0;
	while (i < 3)
	{
		if (!rgb[i] || ft_atoi(rgb[i]) > 255)
			f_perror();
		i++;
	}
	if (i != 3 || rgb[i])
		f_perror();
}

void    check_position(int i, int j, char **map)
{
	char    *temp;
	int     t;

	temp = map[i];
	if (!temp[j + 1] || temp[j + 1] == ' ' || temp[j + 1] == '\n')
		f_perror();
	if (!j || temp[j - 1] == ' ' || temp[j - 1] == '\n')
		f_perror();
	t = ft_len(map[i + 1]) - 1;
	if (!map[i + 1] || t < j || map[i + 1][j] == ' ' || map[i + 1][j] == '\n')
		f_perror();
	if (!i)
		f_perror();
	t = ft_len(map[i - 1]) - 1;
	if (t < j || map[i - 1][j] == ' ' || map[i - 1][j] == '\n')
		f_perror();
}
//check the RGB values;