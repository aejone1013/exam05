#include "bsq.h"

void	free_map(t_bsq *bsq)
{
	for (int i = 0; i < bsq->height; i++)
	{
		if (bsq->map[i])
			free(bsq->map[i]);
	}
	free(bsq->map);
}

void	print_map(t_bsq *bsq)
{
	for (int i = 0; i < bsq->height; i++)
		fprintf(stdout, "%s\n", bsq->map[i]);
}

int ft_strlen(char* s)
{
	int i = 0;
	while(s[i])
		i++;
	return (i);
}

int ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

char**	get_map(t_bsq *bsq, char* filename)
{
	char **map;
	FILE *file;
	size_t len = 0;
	ssize_t read = 0;
	char* line = NULL;
	
	file = filename ? fopen(filename, "r") : stdin;
	if (!file)
		return (NULL);
	// 첫 줄에서 높이와 빈칸/장애물/채움 문자를 읽는다.
	if (fscanf(file, "%d%c%c%c\n", &bsq->height, &bsq->empty, &bsq->obstacle, &bsq->full) != 4)
	{
		if (filename)
			fclose(file);
		return (NULL);
	}
	if (bsq->height <= 0)
	{
		if (filename)
			fclose(file);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (bsq->height + 1));
	if (!map)
	{
		if (filename)
			fclose(file);
		return (NULL);
	}
	for (int i = 0; i < bsq->height; i++)
	{
		line = NULL;
		read = getline(&line, &len, file);
		if (read == -1)
		{
			for (int k = 0; k < i; k++)
				free(map[k]);
			free(map);
			if (filename)
				fclose(file);
			return (NULL);
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		// 줄은 일단 그대로 저장하고, 형식 검사는 뒤에서 한다.
		map[i] = line;
	}
	bsq->width = ft_strlen(map[0]);
	map[bsq->height] = NULL;
	if (filename)
		fclose(file);
	return (map);
}

int	check_map(t_bsq *bsq)
{	
	if (!bsq->map)
		return(0);
	if (bsq->height < 1 || bsq->width < 1)
		return (0);
	if (!ft_isprint(bsq->empty) || !ft_isprint(bsq->full) || !ft_isprint(bsq->obstacle))
		return (0);
	if (bsq->empty == bsq->full || bsq->empty == bsq->obstacle || bsq->full == bsq->obstacle)
		return (0);
	for (int i = 0; i < bsq->height; i++)
	{
		int j = 0;
		while (bsq->map[i][j])
		{
			// 각 칸은 헤더에서 정의한 문자만 써야 한다.
			if (bsq->map[i][j] != bsq->empty && bsq->map[i][j] != bsq->full && bsq->map[i][j] != bsq->obstacle)
				return (0);
			j++;
		}
		if (j != bsq->width)
			return (0);
	}
	return (1);
}

int	min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

int	bsq_solver(t_bsq *bsq)
{
	int	max_i = 0;
	int max_j = 0;
	int max_size = 0;
	int* int_map = malloc(sizeof(int) * bsq->height * bsq->width);
	if (!int_map)
		return (1);
	for (int i = 0; i < bsq->height; i++)
	{
		for (int j = 0; j < bsq->width; j++)
		{
			int idx = i * bsq->width + j;
			if (bsq->map[i][j] == bsq->obstacle)
				int_map[idx] = 0;
			else if (i == 0 || j == 0)
				int_map[idx] = 1;
			else
				// (i, j)를 오른쪽 아래로 하는 최대 정사각형 크기
				int_map[idx] = 1 + min(int_map[(i - 1) * bsq->width + (j - 1)], 
									int_map[(i - 1) * bsq->width + j],
									int_map[i * bsq->width + (j - 1)]);
			if (int_map[idx] > max_size)
			{
				max_i = i;
				max_j = j;
				max_size = int_map[idx];
			}
		}
	}
	for (int i = max_i - max_size + 1; i <= max_i; i++)
	{
		for (int j = max_j - max_size + 1; j <= max_j; j++)
			// 최적 정사각형의 오른쪽 아래 좌표를 기준으로 채운다.
			bsq->map[i][j] = bsq->full;
	}
	free(int_map);
	return (0);
}

int	bsq(char* filename)
{
	t_bsq *bsq = malloc(sizeof(t_bsq));
	if (!bsq)
		return (1);
	bsq->map = get_map(bsq, filename);
	if (!bsq->map)
	{
		fprintf(stderr, "map error\n");
		free(bsq);
		return (1);
	}
	if (!check_map(bsq))
	{
		free_map(bsq);
		fprintf(stderr, "map error\n");
		free(bsq);
		return (1);
	}
	if (bsq_solver(bsq) == 1)
	{
		free_map(bsq);
		fprintf(stderr, "map error\n");
		free(bsq);
		return (1);
	}
	print_map(bsq);
	free_map(bsq);
	free(bsq);
	return (0);
}

int main(int ac, char** av)
{
    if (ac == 1)
        bsq(NULL);
    else
    {
        for (int i = 1; i < ac; i++)
        {
            bsq(av[i]);
            if (i < ac - 1)
                fprintf(stdout, "\n");
        }
    }
    return (0);
}
