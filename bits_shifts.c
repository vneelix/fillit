/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits_shifts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 12:54:50 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/08 17:17:30 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		move_xl(unsigned long *t)
{
	int m;

	m = 63;
	while (m > 0)
	{
		if (((t[0] & (1UL << m)) | (t[1] & (1UL << m))
			| (t[2] & (1UL << m)) | (t[3] & (1UL << m))) != 0)
			return (-1);
		m -= 16;
	}
	m = 0;
	while (m < 4)
		t[m++] <<= 1;
	return (0);
}

int		move_xr(unsigned long *t)
{
	int m;

	m = 48;
	while (m >= 0)
	{
		if (((t[0] & (1UL << m)) | (t[1] & (1UL << m))
			| (t[2] & (1UL << m)) | (t[3] & (1UL << m))) != 0)
			return (-1);
		m -= 16;
	}
	m = 0;
	while (m < 4)
		t[m++] >>= 1;
	return (0);
}

int		move_yu(unsigned long *t)
{
	int			m;

	m = 3;
	while (t[m] == 0)
		m--;
	if (m == 0 && (t[m] >= (1UL << 48)))
		return (-1);
	if (m != 0)
	{
		t[m - 1] <<= 16;
		t[m - 1] |= *((unsigned short*)(t + m) + 3);
		*((unsigned short*)(t + m) + 3) = 0;
	}
	t[m] <<= 16;
	return (0);
}

int		move_yd(unsigned long *t)
{
	int m;

	m = 0;
	while (t[m] == 0)
		m++;
	if (m == 3 && (t[m] & 65535UL) != 0)
		return (-1);
	if (m != 3)
	{
		t[m + 1] >>= 16;
		*((unsigned short*)(t + m + 1) + 3) |= *((unsigned short*)(t + m));
		*((unsigned short*)(t + m)) = 0;
	}
	t[m] >>= 16;
	return (0);
}

void	zero_position(unsigned long *t)
{
	int i;

	i = 4;
	while (i != -1)
		i = move_xl(t);
	i = 0;
	while (i != -1)
		i = move_yu(t);
}
