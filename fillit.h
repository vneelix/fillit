/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:35:51 by vneelix           #+#    #+#             */
/*   Updated: 2019/10/08 15:57:35 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/*
** input
*/
unsigned short			*get_tetromino(char *file_name);

/*
** fill
*/
int						fillit(unsigned long *t, unsigned short size);

/*
** output
*/
void					output(unsigned long *t, unsigned short size);

/*
** bits_shifts
*/
int						move_xl(unsigned long *t);
int						move_xr(unsigned long *t);
int						move_yu(unsigned long *t);
int						move_yd(unsigned long *t);
void					zero_position(unsigned long *t);

#endif
