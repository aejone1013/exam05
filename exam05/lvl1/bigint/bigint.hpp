#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

class	bigint
{
	private:
		std::string	_string;

	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& other);
		bigint&	operator=(const bigint& other);

		bigint	operator+(const bigint& other) const;
		bigint&	operator+=(const bigint& other);
		bigint&	operator++();
		bigint	operator++(int);
		// 참조가 아니라 값 복사 인자이므로 여기서는 const가 필요 없다.
		
		bigint	operator<<(unsigned int n) const; 
		bigint&	operator<<=(unsigned int n);
		bigint	operator>>(unsigned int n) const;
		bigint&	operator>>=(const bigint& other);
		
		bool	operator>(const bigint& other) const;
		bool	operator<(const bigint& other) const;
		bool	operator==(const bigint& other) const;
		bool	operator!=(const bigint& other) const;
		bool	operator<=(const bigint& other) const;
		bool	operator>=(const bigint& other) const;

		const std::string&	getValue() const;
};

// ostream은 출력 스트림의 기반 타입이며 ostringstream도 이를 따른다.
// 스트림은 복사할 수 없으므로 참조로 받아야 한다.
std::ostream&	operator<<(std::ostream& out, const bigint& other);

// 멤버 함수: 첫 번째 피연산자는 this(현재 객체)다.
// 비멤버 함수: 두 피연산자 모두 매개변수로 전달된다.
#endif
