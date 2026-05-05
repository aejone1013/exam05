#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

class bigint
{
private:
	std::string	_s;
public:
	bigint() : _s("0") {}
	bigint(unsigned int n) { std::ostringstream o; o << n; _s = o.str(); }
	bigint(const bigint& o) : _s(o._s) {}
	bigint&	operator=(const bigint& o) { _s = o._s; return *this; }

	bigint	operator+(const bigint& o) const;
	bigint&	operator+=(const bigint& o) { *this = *this + o; return *this; }
	bigint&	operator++()    { *this += bigint(1); return *this; }
	bigint	operator++(int) { bigint t(*this); ++(*this); return t; }

	bigint	operator<<(unsigned int n) const;
	bigint&	operator<<=(unsigned int n) { *this = *this << n; return *this; }
	bigint	operator>>(unsigned int n) const;
	bigint&	operator>>=(const bigint& o);

	bool	operator==(const bigint& o) const { return _s == o._s; }
	bool	operator!=(const bigint& o) const { return !(*this == o); }
	bool	operator<(const bigint& o) const;
	bool	operator>(const bigint& o) const  { return o < *this; }
	bool	operator<=(const bigint& o) const { return *this < o || *this == o; }
	bool	operator>=(const bigint& o) const { return *this > o || *this == o; }

	const std::string&	getValue() const { return _s; }
};

std::ostream& operator<<(std::ostream& out, const bigint& o);
#endif
