/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:00:55 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/09 20:14:09 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		shift_restrictor_x(unsigned long *t, unsigned short size)
{
	unsigned short	m;

	m = 64;
	while (m >= 16)
	{
		if (((t[0] & (1UL << (m - size))) | (t[1] & (1UL << (m - size)))
			| (t[2] & (1UL << (m - size))) | (t[3] & (1UL << (m - size)))) != 0)
			return (-1);
		m -= 16;
	}
	return (0);
}

static int		shift_restrictor_y(unsigned long *t, unsigned short size)
{
	unsigned short	i;
	unsigned long	*t1;

	if (size <= 4)
		i = 0;
	else if (size >= 5 && size <= 8)
		i = 1;
	else if (size >= 9 && size <= 12)
		i = 2;
	else
		i = 3;
	t1 = t + i;
	if (((unsigned short*)(t + i))[4 - (size % 4 == 0 ? 4 : size % 4)] != 0)
		return (-1);
	return (0);
}

static int		next_position(unsigned long *t, int size)
{
	if (shift_restrictor_x(t, size) != 0)
	{
		if (shift_restrictor_y(t, size) != 0)
			return (-1);
		if (move_yd(t) == -1)
			return (-1);
		while (move_xl(t) == 0)
			;
	}
	else
	{
		if (move_xr(t) == -1)
			return (-1);
	}
	return (0);
}

static int		func(unsigned long m[4], unsigned long *t, unsigned short size)
{
	if (*t == 255)
		return (0);
	while (1)
	{
		if (((m[0] & t[0]) | (m[1] & t[1])
			| (m[2] & t[2]) | (m[3] & t[3])) == 0)
		{
			m[0] |= t[0];
			m[1] |= t[1];
			m[2] |= t[2];
			m[3] |= t[3];
			if (func(m, (t + 4), size) == 0)
				return (0);
			m[0] -= t[0];
			m[1] -= t[1];
			m[2] -= t[2];
			m[3] -= t[3];
		}
		if (next_position(t, size) != 0)
		{
			zero_position(t);
			return (-1);
		}
	}
}

int				fillit(unsigned long *t, unsigned short size)
{
	unsigned long	m[4];

	while (1)
	{
		m[0] = t[0];
		m[1] = t[1];
		m[2] = t[2];
		m[3] = t[3];
		if (func(m, (t + 4), size) == 0)
			break ;
		if (next_position(t, size) != 0)
		{
			zero_position(t);
			if (size == 16)
				return (-1);
			size++;
		}
	}
	output(t, size);
	return (0);
}
