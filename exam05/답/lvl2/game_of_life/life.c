#include "life.h"

static int count_nb(char b[50][51], int x, int y, int w, int h)
{
	int cnt = 0;
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if ((dx || dy) && x+dx >= 0 && x+dx < w && y+dy >= 0 && y+dy < h
				&& b[y+dy][x+dx] == '0')
				cnt++;
	return cnt;
}

void game_of_life(int w, int h, int iter)
{
	char boards[2][50][51];
	int flag = 0;

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 51; j++)
			boards[0][i][j] = ' ';

	int x = 0, y = 0, pen = 0;
	char c;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'x') pen = !pen;
		else if (c == 'w' && y > 0) y--;
		else if (c == 's' && y < h - 1) y++;
		else if (c == 'a' && x > 0) x--;
		else if (c == 'd' && x < w - 1) x++;
		if (pen) boards[0][y][x] = '0';
	}

	while (iter--)
	{
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				int n = count_nb(boards[flag], j, i, w, h);
				boards[!flag][i][j] = (n == 3 || (n == 2 && boards[flag][i][j] == '0')) ? '0' : ' ';
			}
		flag = !flag;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) putchar(boards[flag][i][j]);
		putchar('\n');
	}
}
