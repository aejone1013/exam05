#pragma once
#include <iostream>
class vect2{
public:
	int x,y;
	vect2(int a=0,int b=0):x(a),y(b){}
	vect2(const vect2& v):x(v.x),y(v.y){}
	vect2& operator=(const vect2& v){x=v.x;y=v.y;return *this;}
	int& operator[](int i){return i?y:x;}
	int operator[](int i)const{return i?y:x;}
	vect2 operator+(int i)const{return vect2(x+i,y+i);}
	vect2 operator-(int i)const{return vect2(x-i,y-i);}
	vect2 operator*(int i)const{return vect2(x*i,y*i);}
	vect2 operator-()const{return vect2(-x,-y);}
	vect2 operator+(const vect2& v) const {return vect2(x+v.x,y+v.y);}
	vect2 operator-(const vect2& v)const{return vect2(x-v.x,y-v.y);}
	vect2 operator*(const vect2& v)const{return vect2(x*v.x,y*v.y);}
	vect2& operator+=(int i){x+=i;y+=i;return *this;}
	vect2& operator-=(int i){x-=i;y-=i;return *this;}
	vect2& operator*=(int i){x*=i;y*=i;return *this;}
	vect2& operator+=(const vect2& v){x+=v.x;y+=v.y;return *this;}
	vect2& operator-=(const vect2& v){x-=v.x;y-=v.y;return *this;}
	vect2& operator*=(const vect2& v){x*=v.x;y*=v.y;return *this;}
	vect2& operator++(){x++;y++;return *this;}
	vect2& operator--(){x--;y--;return *this;}
	vect2 operator++(int){vect2 t(*this);x++;y++;return t;}
	vect2 operator--(int){vect2 t(*this);x--;y--;return t;}
	bool operator==(const vect2& v)const{return x==v.x &&y==v.y;}
	bool operator!=(const vect2& v)const{return !(*this==v);}
};
inline vect2 operator+(int i, const vect2& v){return v+i;}
inline vect2 operator*(int i, const vect2& v){return v*i;}
inline vect2 operator-(int i, const vect2& v){return vect2(i-v.x,i-v.y);}
inline std::ostream& operator<<(std::ostream& os, const vect2& v){return os << "{" << v.x << ", " << v.y << "}";}
