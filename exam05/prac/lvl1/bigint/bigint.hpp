#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <sstream>
#include <string>

class bigint
{
private:
	std::string	_s;
public:
	bigint() : _s("0") {}
	bigint(unsigned int n) { std::ostringstream o; o << n; _s = o.str(); }
	bigint(const bigint& o) : _s(o._s) {}
	bigint&	operator=(const bigint& o) { _s = o._s; return *this; }

	bigint	operator+(const bigint& o) const
	{
		const std::string& a = (_s.size() >= o._s.size()) ? _s : o._s;
		const std::string& b = (_s.size() >= o._s.size()) ? o._s : _s;
		std::string res(a.size() + 1, '0');
		int carry = 0;
		for (int i = (int)a.size() - 1, j = (int)b.size() - 1, k = (int)res.size() - 1; k >= 0; --k, --i, --j)
		{
			int sum = carry + (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0);
			res[k] = sum % 10 + '0';
			carry = sum / 10;
		}
		if (res[0] == '0')
			res.erase(0, 1);
		bigint r;
		r._s = res;
		return r;
	}
	bigint&	operator+=(const bigint& o) { return *this = *this + o; }
	bigint&	operator++()    { *this += bigint(1); return *this; }
	bigint	operator++(int) { bigint t(*this); ++(*this); return t; }

	bigint	operator<<(unsigned int n) const
	{
		if (_s == "0")
			return *this;
		bigint r(*this);
		r._s.append(n, '0');
		return r;
	}
	bigint&	operator<<=(unsigned int n) { *this = *this << n; return *this; }
	bigint	operator>>(unsigned int n) const
	{
		if (_s == "0" || _s.size() <= n)
			return bigint(0);
		bigint r(*this);
		r._s.erase(r._s.size() - n);
		return r;
	}
	bigint&	operator>>=(const bigint& o)
	{
		unsigned int n = 0;
		for (size_t i = 0; i < o._s.size(); ++i)
			n = n * 10 + o._s[i] - '0';
		return *this = *this >> n;
	}

	bool	operator==(const bigint& o) const { return _s == o._s; }
	bool	operator!=(const bigint& o) const { return !(*this == o); }
	bool	operator<(const bigint& o) const
	{
		return _s.size() == o._s.size() ? _s < o._s : _s.size() < o._s.size();
	}
	bool	operator>(const bigint& o) const  { return o < *this; }
	bool	operator<=(const bigint& o) const { return *this < o || *this == o; }
	bool	operator>=(const bigint& o) const { return *this > o || *this == o; }

	const std::string&	getValue() const { return _s; }
};

inline std::ostream& operator<<(std::ostream& out, const bigint& o) { return out << o.getValue(); }
#endif
