/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 22:07:10 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/08 18:44:32 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	put_sign(unsigned long *t, int i, int m)
{
	int		j;
	char	c;

	j = 0;
	while ((t[j] != 255)
		&& ((t[j + i] & (1UL << m)) == 0))
		j += 4;
	if (t[j] == 255)
		c = '.';
	else
		c = 'A' + (j / 4);
	write(1, &c, 1);
}

void		output(unsigned long *t, unsigned short size)
{
	int		i;
	int		j;
	int		m;

	i = 0;
	j = 0;
	m = 63;
	while (i < 4 && j < size)
	{
		while (m >= 0 && j < size)
		{
			if (-((m % 16) - 16) <= size)
			{
				put_sign(t, i, m);
				if (-((m % 16) - 16) == size)
				{
					write(1, "\n", 1);
					j++;
				}
			}
			m--;
		}
		i++;
		m = 63;
	}
}
