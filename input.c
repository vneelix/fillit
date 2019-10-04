/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:55:02 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/01 14:23:39 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned short	tetromino_valid(unsigned short t)
{
	unsigned short m;
	unsigned short i;

	i = 0;
	m = 15;
	while (i < 3)
	{
		while ((t & (1 << m)) == 0)
			m--;
		while ((t & (1 << m)) > 0 && i != 3)
		{
			if ((t & (1 << (m - 4))) == 0)
				if ((t & (1 << (m - 1))) == 0)
					if ((t & (1 << (m + 1))) == 0)
						return (0);
			i++;
			m--;
		}
	}
	return (t);
}

static unsigned short	flow_to_bytes(char *s)
{
	unsigned short m;
	unsigned short t;

	t = 0;
	m = 15;
	while (*s != '\0')
	{
		while (*s != '#' && *s != '\0')
		{
			if (*s != '\n')
				m--;
			s++;
		}
		while (*s == '#')
		{
			t = t | (1 << m);
			m--;
			s++;
		}
	}
	return (t);
}

static int				get_flow(int fd, char *bf)
{
	int		i;
	int		j;

	if ((i = read(fd, bf, 546)) > 545 || i == 0 || (i - 20) % 21 != 0)
		return (-1);
	bf[i] = '\0';
	i = 4;
	j = 0;
	while (bf[i] != '\0')
	{
		if (bf[i] != '\n')
			return (-1);
		if ((j++) == 3)
		{
			i++;
			j = -1;
		}
		else
			i += 5;
	}
	i = 0;
	j = 0;
	while (bf[i] != '\0')
		j += (unsigned int)(bf[i++]);
	return ((j - 732) % 742 == 0 ? (j - 732) / 742 : -1);
}

static	unsigned short	*inputf(int c, char *bf)
{
	int				i;
	unsigned short	*tetrom;

	if ((tetrom =
		(unsigned short*)malloc(sizeof(unsigned short) * (c + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < c)
	{
		*(bf + 20) = '\0';
		if ((tetrom[i] = tetromino_valid(flow_to_bytes(bf))) == 0)
		{
			free(tetrom);
			return (NULL);
		}
		bf += 21;
		i++;
	}
	tetrom[c] = 0;
	return (tetrom);
}

unsigned short			*get_tetromino(char *file_name)
{
	int				i;
	int				fd;
	char			*bf;
	unsigned short	*tetrom;

	if ((fd = open(file_name, O_RDONLY)) == -1
		|| (bf = (char*)malloc(sizeof(char) * 546)) == NULL)
		return (NULL);
	if ((i = get_flow(fd, bf)) == -1)
	{
		free(bf);
		return (NULL);
	}
	tetrom = inputf(i + 1, bf);
	free(bf);
	return (tetrom);
}
