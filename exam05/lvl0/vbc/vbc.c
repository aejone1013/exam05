#include "vbc.h"

int safe_write(int fd, const char *str, size_t len)
{
    if (write(fd, str, len) == -1)
        return (1);
    return (0);
}

int print_unexpected_end(void)
{
    return safe_write(1, "Unexpected end of input\n", 24);
}

int print_unexpected_token(char c)
{
    if (printf("Unexpected token '%c'\n", c) < 0)
        return (1);
    return (0);
}

int parse_factor(char *expr, int *pos, int len, int *error)
{
    // 숫자 하나를 읽거나, 괄호 안 식을 재귀적으로 계산한다.
    if (*pos >= len)
    {
        *error = print_unexpected_end();
        return (0);
    }

    if (expr[*pos] == '(')
    {
        (*pos)++; // 여는 괄호 건너뛰기
        int result = parse_expression(expr, pos, len, error);
        if (*error)
            return (0);
        
        // 여기서 열린 괄호는 반드시 닫혀야 한다.
        if (*pos >= len)
        {
            *error = print_unexpected_end();
            return (0);
        }
        if (expr[*pos] != ')')
        {
            *error = print_unexpected_token(expr[*pos]);
            return (0);
        }
        (*pos)++;
        return (result);
    }
    
    if (isdigit(expr[*pos])) 
        return (expr[(*pos)++] - '0');
    
    *error = print_unexpected_token(expr[*pos]);
    return (0);
}

int parse_term(char *expr, int *pos, int len, int *error)
{
    int result = parse_factor(expr, pos, len, error);
    if (*error)
        return (0);
    
    // 곱셈을 먼저 모두 처리해 우선순위를 맞춘다.
    while (*pos < len && expr[*pos] == '*')
    {
        (*pos)++;
        result *= parse_factor(expr, pos, len, error);
        if (*error)
            return (0);
    }
    return (result);
}

int parse_expression(char *expr, int *pos, int len, int *error)
{
    int result = parse_term(expr, pos, len, error);
    if (*error)
        return (0);
    
    // 남아 있는 덧셈을 왼쪽부터 처리한다.
    while (*pos < len && expr[*pos] == '+')
    {
        (*pos)++;
        result += parse_term(expr, pos, len, error);
        if (*error)
            return (0);
    }
    return (result);
}

int calculate(char *expr, int *error)
{
    int pos = 0;
    int len = 0;
    
    while (expr[len])
        len++;
    
    if (len == 0)
    {
        *error = print_unexpected_end();
        return (0);
    }
    
    int result = parse_expression(expr, &pos, len, error);
    if (*error)
        return (0);
    
    // 계산이 끝났으면 입력도 끝까지 읽은 상태여야 한다.
    if (pos < len)
    {
        if (pos == len - 1)
            *error = print_unexpected_end();
        else
            *error = print_unexpected_token(expr[pos]);
        return (0);
    }
    return (result);
}

int main(int argc, char **argv)
{
    int error = 0;
    int result;

    if (argc != 2)
        return (1);
    
    result = calculate(argv[1], &error);
    if (error)
        return (1);
    if (printf("%d\n", result) < 0)
        return (1);
    return (0);
}
