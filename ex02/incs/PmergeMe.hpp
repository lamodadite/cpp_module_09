#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>

class PmergeMe {
	private:
		template<typename C>
		C	rearrange(C& ret, C& main, C& sub);
		template<typename Iter>
		Iter binarySearch(Iter begin, Iter end, int value);
		int jacobsthal(int n, int max);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe& operator=(const PmergeMe &obj);

		std::vector<int> mergeInsertionSort(std::vector<int>& v);
};

template<typename T>
void	printContainer(T& a, const char* name) {
	typedef typename T::iterator Iter;

	std::cout << name << ": ";
	for (Iter iter = a.begin(); iter != a.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;;
}

#endif