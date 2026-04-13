#include "bigint.hpp"

bigint bigint::operator+(const bigint& o) const
{
	// 긴 쪽 = s1, 짧은 쪽 = s2
	const std::string& s1 = (_s.size() >= o._s.size()) ? _s : o._s;
	const std::string& s2 = (_s.size() >= o._s.size()) ? o._s : _s;
	std::string res;
	int carry = 0;
	int i = (int)s1.size() - 1;
	int j = (int)s2.size() - 1;

	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0) sum += s1[i--] - '0';
		if (j >= 0) sum += s2[j--] - '0';
		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	std::reverse(res.begin(), res.end());
	bigint r; r._s = res; return r;
}

bigint bigint::operator<<(unsigned int n) const
{
	if (_s == "0") return *this;
	bigint r(*this); r._s.append(n, '0'); return r;
}

bigint bigint::operator>>(unsigned int n) const
{
	if (_s == "0" || _s.size() <= n) return bigint(0);
	bigint r(*this); r._s.erase(r._s.size() - n); return r;
}

bigint& bigint::operator>>=(const bigint& o)
{
	std::stringstream ss; ss << o._s;
	unsigned int n; ss >> n;
	*this = *this >> n; return *this;
}

bool bigint::operator<(const bigint& o) const
{
	if (_s.size() != o._s.size())
		return _s.size() < o._s.size();
	return _s < o._s;
}

std::ostream& operator<<(std::ostream& out, const bigint& o)
{ out << o.getValue(); return out; }
