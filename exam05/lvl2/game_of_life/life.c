#include "life.h"

// 대각선까지 포함해 주변 8칸을 이웃으로 센다.
/*
(x-1, y-1) (x, y-1) (x+1, y-1)
(x-1, y  ) (x, y  ) (x+1, y  )
(x-1, y+1) (x, y+1) (x+1, y+1)
*/
int count_neighbors(char board[50][51], int x, int y, int width, int height)
{
    int count = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            if (!(dx == 0 && dy == 0) && 
                x + dx >= 0 && x + dx < width && 
                y + dy >= 0 && y + dy < height && 
                board[y + dy][x + dx] == '0')
                count++;
    return count;
}

void game_of_life(int width, int height, int iteration)
{
    char board[50][51];
    char temp[50][51];
    char (*current)[51] = board;
    char (*next)[51] = temp;
    int x = 0, y = 0, pen = 0;
    char c;
    
    // 보드 초기화
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 51; j++)
        {
            board[i][j] = ' ';
            temp[i][j] = ' ';
        }
    
    // `w`, `a`, `s`, `d`로 커서를 움직이고 `x`로 그리기 모드를 토글한다.
    while (read(0, &c, 1) > 0)
    {
        if (c == 'x') pen = !pen;
        else if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < height - 1) y++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'd' && x < width - 1) x++;
        
        if (pen) current[y][x] = '0';
    }
    
    // 한 세대씩 다음 상태를 계산한다.
    while (iteration--)
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                int neighbors = count_neighbors(current, j, i, width, height);
                next[i][j] = ((neighbors == 3) || (neighbors == 2 && current[i][j] == '0')) ? '0' : ' ';
                // 이웃 3개면 탄생, 살아 있던 셀은 이웃 2개일 때 유지된다.
            }
        {
            char (*swap)[51] = current;
            current = next;
            next = swap;
        }
    }
    
    // 결과 출력
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            putchar(current[i][j]);
        putchar('\n');
    }
}
