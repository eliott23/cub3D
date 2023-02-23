/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:06:43 by aababach          #+#    #+#             */
/*   Updated: 2023/02/23 23:35:07 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

long long int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	long long int	rslt;

	rslt = 0;
	s = 1;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - 48;
		i++;
	}
	if (!i)
		return (-1);
	return (rslt * s);
}

void	check_xpm(t_pd *pd)
{
	if (!check_filename(pd->no, ".xpm") || !check_filename(pd->so, ".xpm")
		|| !check_filename(pd->we, ".xpm") || !check_filename(pd->ea, ".xpm"))
		f_perror();
}
