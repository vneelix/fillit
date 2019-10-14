/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:54:45 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/09 20:24:47 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned long	*convert(unsigned short *tab)
{
	int				i;
	unsigned long	*t;

	i = 0;
	while (tab[i] != 0)
		i++;
	if ((t = (unsigned long*)malloc((32 * i) + 8)) == NULL)
		return (NULL);
	i = 0;
	while (*tab != 0)
	{
		t[i] = 0;
		t[i] |= (unsigned long)(*tab) & (15UL);
		t[i] |= ((unsigned long)(*tab) & (15UL << 4)) << 12;
		t[i] |= ((unsigned long)(*tab) & (15UL << 8)) << 24;
		t[i] |= ((unsigned long)(*tab) & (15UL << 12)) << 36;
		t[i + 1] = 0;
		t[i + 2] = 0;
		t[i + 3] = 0;
		zero_position(&(t[i]));
		tab++;
		i += 4;
	}
	t[i] = 255;
	return (t);
}

static unsigned short	sqr_size(unsigned long *t)
{
	unsigned short i;
	unsigned short j;

	i = 0;
	while (t[i] != 255)
		i += 4;
	j = 3;
	while ((j * j) < i)
		j++;
	if (*(t + 4) == 255)
		if (*t == 13835269161514696704UL)
			return (2);
	if (j < 4)
		while (*t != 255)
		{
			if (*t == 17293822569102704640UL
				|| *t == 9223512776490647552UL)
				return (4);
			t += 4;
		}
	return (j);
}

int						main(int argc, char **argv)
{
	unsigned short	*tetr;
	unsigned long	*t;

	if (argc != 2)
	{
		write(1, "usage: ./fillit file_name\n", 26);
		return (0);
	}
	if ((tetr = get_tetromino(argv[1])) == NULL)
	{
		write(1, "error\n", 6);
		return (0);
	}
	t = convert(tetr);
	fillit(t, sqr_size(t));
	free(tetr);
	free(t);
	return (0);
}
