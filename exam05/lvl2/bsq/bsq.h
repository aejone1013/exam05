#ifndef BSQ_H
# define BSQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_bsq
{
	int		height;
	int		width;
	char	empty;
	char	full;
	char	obstacle;
	char**	map;
}	t_bsq;

#endif
