#include "bigint.hpp"
// 큰 정수를 문자열로 다루는 구현

bigint::bigint() : _string("0") {}

bigint::bigint(unsigned int n)
{
	// 내부 값은 문자열로 저장한다.
	std::ostringstream oss; 
	// 숫자를 문자열로 바꾸기만 하면 되므로 ostringstream이면 충분하다.
	oss << n;
	_string = oss.str();
}

bigint::bigint(const bigint& other) : _string(other._string) {}

bigint&	bigint::operator=(const bigint& other) {
	_string = other._string;
	return *this;
}

const std::string&	bigint::getValue() const { return _string; }

bigint bigint::operator+(const bigint& other) const
{
    const std::string& s1 = (_string.size() >= other._string.size()) ? _string : other._string;
    const std::string& s2 = (_string.size() >= other._string.size()) ? other._string : _string;
    
    // 오른쪽 자리부터 더하면서 올림을 전파한다.
    std::string result;
    result.reserve(s1.size() + 1);
    int carry = 0;
    int i = static_cast<int>(s1.size()) - 1;
    int j = static_cast<int>(s2.size()) - 1;
    
	// 현재 자리 합 + 이전 자리의 올림
    while (i >= 0 || j >= 0 || carry)
	{
        int sum = carry;
        if (i >= 0) sum += s1[i--] - '0';
        if (j >= 0) sum += s2[j--] - '0';
        
        result.push_back(static_cast<char>(sum % 10 + '0'));
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    
    bigint res;
    res._string = result;
    return res;
}

bigint&	bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return *this;
}

// ++a: 값을 먼저 늘리고 그 값을 반환
bigint&	bigint::operator++() // 전위 증가 (++a)
{
	*this += bigint(1);
	return *this;
}

// b++: 기존 값을 반환한 뒤 1 증가
bigint	bigint::operator++(int) // 후위 증가 (a++)
{
	bigint temp(*this);
	++(*this);
	return temp;
}

bigint	bigint::operator<<(unsigned int n) const // 끝에 0을 n개 붙인다.
{
	if (_string == "0")
		return *this;
	bigint res(*this);
	// 10의 거듭제곱을 곱하는 효과다.
	res._string.append(n, '0');
	return res;
}

bigint&	bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint	bigint::operator>>(unsigned int n) const
{
	// 지울 자릿수가 더 많으면 결과는 0이다.
	if (_string == "0" || _string.size() <= n)
		return bigint(0);
	bigint res(*this);
	// 뒤에서 n자리를 제거한다.
	res._string.erase(res._string.size() - n);
	return res;
}

/*
`stringstream >> unsigned int` 오버로드가 이미 있어서
문자열을 바로 정수로 읽어올 수 있다.
*/

bigint&	bigint::operator>>=(const bigint& other) {
	std::stringstream ss;
	ss << other._string;
	unsigned int n;
	ss >> n;
	// 시프트 수는 기본 정수형으로 바꿔서 사용한다.
	*this = *this >> n;
	return *this;
}

bool	bigint::operator==(const bigint& other) const {
	return _string == other._string;
}

bool	bigint::operator!=(const bigint& other) const {
	return !(*this == other);
}

bool	bigint::operator<(const bigint& other) const
{
	// 길이가 다르면 긴 쪽이 더 큰 수다.
	if (_string.size() != other._string.size())
		return _string.size() < other._string.size();
	return _string < other._string;
}

bool	bigint::operator>(const bigint& other) const {
	return other < *this;
}

bool	bigint::operator<=(const bigint& other) const {
	return *this < other || *this == other;
}

bool	bigint::operator>=(const bigint& other) const {
	return *this > other || *this == other;
}

// 스트림을 반환해야 `cout << a << b`처럼 이어서 출력할 수 있다.
std::ostream&	operator<<(std::ostream& out, const bigint& other) {
	out << other.getValue();
	return out;
}
