#include "searchable_bag.hpp"
#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include <climits>
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (1);
	searchable_bag *t = new Searchabletree_bag;
	searchable_bag *a = new Searchablearray_bag;

	for (int i = 1; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();
	a->print();

	for (int i = 1; i < argc; i++)
	{
		std::cout << t->has(atoi(argv[i])) << std::endl;
		std::cout << a->has(atoi(argv[i])) << std::endl;
		std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
		std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	}

	t->clear();
	a->clear();

	const Searchablearray_bag tmp(static_cast<Searchablearray_bag &>(*a));
	tmp.print();
	tmp.has(1);

	set sa(*a);
	set st(*t);
	for (int i = 1; i < argc; i++)
	{
		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));

		sa.has(atoi(argv[i]));
		sa.print();
		// sa.get_bag().print();
			// 제거됨: set에는 get_bag() 메서드가 없다.
		st.print();
		sa.clear();
		int arr[] = {
			1,
			2,
			3,
			4,
		};
		sa.insert(
			arr,
			4);
		std::cout << std::endl;
		std::cout << "extra tests for set " << std::endl;
		// searchable_bag 포인터 사용 예시
		a->clear();
		set test_s(a);
		test_s.insert(99);
		test_s.insert(arr, 4);
		test_s.insert(99);
		test_s.print();
	}

	return (0);
}
