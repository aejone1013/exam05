#pragma once
#include <iostream>

class vect2 {
public:
    int x, y;

    // 정수 좌표 2개를 담는 간단한 벡터 타입
    vect2(int a = 0, int b = 0) : x(a), y(b) {} 
    vect2(const vect2& c) : x(c.x), y(c.y) {}
    
    // 대입 연산자
    vect2& operator=(const vect2& other) { x = other.x; y = other.y; return *this; }

    // 0은 x, 그 외는 y를 반환한다.
    int& operator[](int i) { return i ? y : x; }
    int operator[](int i) const { return i ? y : x; }

    // 스칼라 연산
    vect2 operator+(int i) const { return vect2(x + i, y + i); }
    vect2 operator*(int i) const { return vect2(x * i, y * i); }
    vect2 operator-(int i) const { return vect2(x - i, y - i); }

    // 벡터끼리의 연산
    vect2 operator+(const vect2& v) const { return vect2(x + v.x, y + v.y); }
    vect2 operator*(const vect2& v) const { return vect2(x * v.x, y * v.y); }
    vect2 operator-(const vect2& v) const { return vect2(x - v.x, y - v.y); }

    // 전위 연산: 먼저 바꾸고 자기 자신 반환
	vect2& operator++() { x++; y++; return *this; } // 전위 증가
    vect2& operator--() { x--; y--; return *this; }
    // 후위 연산: 이전 값을 복사해서 반환
    vect2 operator++(int) { vect2 tmp(*this); x++; y++; return tmp; } // 후위 증가
    vect2 operator--(int) { vect2 tmp(*this); x--; y--; return tmp; }


    // 비교
    bool operator==(const vect2& v) const { return x == v.x && y == v.y; }
    bool operator!=(const vect2& v) const { return !(*this == v); }

    // 스칼라 복합 대입
    vect2& operator+=(int i) { x += i; y += i; return *this; }
    vect2& operator*=(int i) { x *= i; y *= i; return *this; }
    vect2& operator-=(int i) { x -= i; y -= i; return *this; }

    // 벡터 복합 대입
    vect2& operator+=(const vect2& v) { x += v.x; y += v.y; return *this; }
    vect2& operator-=(const vect2& v) { x -= v.x; y -= v.y; return *this; }
    vect2& operator*=(const vect2& v) { x *= v.x; y *= v.y; return *this; }

    // 출력
    void print() const { std::cout << "{" << x << ", " << y << "}" << std::endl; }
};

// `2 + v`처럼 왼쪽 피연산자가 int인 경우를 지원한다.
inline vect2 operator+(int i, const vect2& v) { return v + i; }
inline vect2 operator*(int i, const vect2& v) { return v * i; }
inline vect2 operator-(int i, const vect2 &v) { return vect2(i - v.x, i - v.y); }

// 출력 연산자
inline std::ostream& operator<<(std::ostream& os, const vect2& v) {
    os << "{" << v.x << ", " << v.y << "}";
    return os;
}

// 비멤버 함수라서 뒤에 `const`를 붙일 수 없다.
