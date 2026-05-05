#include "bigint.hpp"

// 예시 실행: c++ -g main.cpp bigint.cpp bigint.hpp && valgrind --leak-check=full --show-leak-kinds=all ./a.out
int	main(void)
{
	{
		const bigint	a(42);
		bigint			b(21), c, d(1337), e(d);
		
		// 모두 10진수 기준이다.
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << d << std::endl;
		std::cout << e << std::endl;
		std::cout << "a + b = " << a + b << std::endl; // 결과는 63
		std::cout << "(c += a) = " << (c += a) << std::endl; // c는 42가 되므로 출력도 42다.
		
		std::cout << "\n\n" << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "++b = " << ++b << std::endl;
		std::cout << "b++ = " << b++ << std::endl;
		std::cout << "b = " << b << std::endl;
		int	i = 0;// 증가 연산 확인용
		std::cout << "i = " << i << std::endl;
		std::cout << "++i = " << ++i << std::endl;
		std::cout << "i++ = " << i++ << std::endl;
		std::cout << "i = " << i << std::endl;

		std::cout << "\n\n" << std::endl;
		std::cout << "\"((b << 10) + 42)\" = " << ((b << 10) + 42) << std::endl;
		std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
		std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
		std::cout << "a = " << a << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "(d < a) = " << (d < a) << std::endl;
		std::cout << "(d > a) = " << (d > a) << std::endl;
		std::cout << "(d == a) = " << (d == a) << std::endl;
		std::cout << "(d != a) = " << (d != a) << std::endl;
		std::cout << "(d == a) = " << (d == d) << std::endl;
		std::cout << "(d <= a) = " << (d <= a) << std::endl;
		std::cout << "(d >= a) = " << (d >= a) << std::endl;

		bigint x(1234);
		std::cout << std::endl;
		std::cout << "\"(x << 2)\"--> " << (x << 2) << "\n";   // 123400 출력
		std::cout << "\"(x >>= 2)\"--> " << (x >>= 2) << "\n";   // 12 출력
	}
	return (0);
}
