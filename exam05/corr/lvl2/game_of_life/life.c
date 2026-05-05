#include "life.h"

// 주어진 좌표 (x, y) 주변 8칸 중 살아 있는 셀('0')의 개수를 셉니다.
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
	int flag = 0; // 현재 사용할 보드 인덱스

	// boards[0]를 공백으로 초기화
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 51; j++)
			boards[0][i][j] = ' ';

	int x = 0, y = 0, pen = 0;
	char c;

	// 표준 입력에서 키 입력을 한 글자씩 읽어들입니다.
	// 'w', 'a', 's', 'd'로 이동하고 'x'로 펜 상태를 토글합니다.
	while (read(0, &c, 1) > 0)
	{
		if (c == 'x')
			pen = !pen;
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;

		// 펜이 켜져 있으면 현재 위치를 살아 있는 셀로 표시합니다.
		if (pen) boards[0][y][x] = '0';
	}

	// iter 만큼 세대를 진행합니다.
	while (iter--)
	{
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				int n = count_nb(boards[flag], j, i, w, h);
				// 게임 오브 라이프 규칙:
				// 살아있는 이웃이 3개면 새 셀이 살아나고,
				// 2개이면 현재 셀이 살아있을 때 유지합니다.
				boards[!flag][i][j] = (n == 3 || (n == 2 && boards[flag][i][j] == '0')) ? '0' : ' ';
			}
		// 다음 세대를 위해 버퍼 전환
		flag = !flag;
	}

	// 최종 결과를 출력합니다.
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			putchar(boards[flag][i][j]);
		putchar('\n');
	}
}
