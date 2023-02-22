/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_err.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-che <zait-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:41:51 by zait-che          #+#    #+#             */
/*   Updated: 2023/02/22 06:42:46 by zait-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

void	check_elmnt_n(int i, t_pd *pd, int n)
{
	if (i == 0)
	{
		while (i < 7)
		{
			pd->elem[i] = 0;
			i++;
		}
	}
	else
	{
		if (pd->elem[n] == n + 1)
			f_perror();
		pd->elem[n] = n + 1;
	}
}

void	check_fd(int fd)
{
	if (fd == -1)
	{
		printf("Error\n");
		exit(0);
	}
}

void	skip_to_next(int m, t_pd *pd)
{
	if (!pd->i_b)
		f_perror();
	while (pd->i_b[pd->i] && pd->i_b[pd->i] != ' ' && pd->i_b[pd->i] != '\n')
		pd->i++;
	if (pd->i_b[pd->i] == '\n' && m)
		f_perror();
	while (pd->i_b[pd->i] == ' ' && m)
		pd->i++;
	if (m)
	{
		if (!pd->i_b[pd->i] || pd->i_b[pd->i] == '\n'\
		|| pd->i_b[pd->i] == ' ')
			f_perror();
	}
	else
	{
		if (!check_empty(&pd->i_b[pd->i]))
			f_perror();
		while (pd->i_b[pd->i] && pd->i_b[pd->i] != '\n')
			pd->i++;
		if (pd->i_b[pd->i])
			pd->i++;
	}
}
