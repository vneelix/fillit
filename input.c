/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:55:02 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/09 15:48:54 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int				check_valid(char *matrix)
{
	int	i;
	int	j;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 16 && sum < 6)
	{
		j = -1;
		while (++j < 4 && sum < 6)
			if (*(matrix + i + j) == '#')
			{
				if (i > 4)
					sum += *(matrix + (i - 5) + j) == '#' ? 1 : 0;
				if (j > 0)
					sum += *(matrix + i + (j - 1)) == '#' ? 1 : 0;
				if (i < 14)
					sum += *(matrix + (i + 5) + j) == '#' ? 1 : 0;
				if (j < 4)
					sum += *(matrix + i + (j + 1)) == '#' ? 1 : 0;
			}
		i += 5;
	}
	return (sum == 6 ? 1 : -1);
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
			t |= (1 << m);
			m--;
			s++;
		}
	}
	return (t);
}

static int				get_flow(int fd, char *bf)
{
	int	i;
	int	j;
	int	sum;

	if ((i = read(fd, bf, 546)) > 545 || i == 0 || (i - 20) % 21 != 0)
		return (-1);
	bf[i] = '\0';
	i = 0;
	j = 1;
	sum = 0;
	while (bf[i] != '\0' || bf[i] == '.' || bf[i] == '#' || bf[i] == '\n')
	{
		if (bf[i] == '\n' && ((i + j) % 5 != 0 && (i + j - 1) % 20 != 0))
			return (-1);
		if ((bf[i] == '\n' && (i + j - 1) % 20 == 0) || (bf[i + 1] == '\0'))
		{
			j--;
			if (check_valid(bf + i - (bf[i + 1] == '\0' ? 19 : 20)) == -1)
				return (-1);
		}
		sum += (unsigned int)(bf[i++]);
	}
	return ((sum - 732) % 742 == 0 ? (sum - 732) / 742 : -1);
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
		tetrom[i] = flow_to_bytes(bf);
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
