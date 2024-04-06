#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>
#include <cmath>
#include <list>

template<typename T>
class IndexableList : public std::list<T> {
	public:
		T& operator[](int index) {
			typename std::list<T>::iterator it = this->begin();
			std::advance(it, index);
			return *it;
		}

		const T& operator[](int index) const {
			typename std::list<T>::iterator it = this->cbegin();
			std::advance(it, index);
			return *it;
		}
};

class PmergeMe {
	private:
		template<typename C>
		C	rearrange(C& ret, C& main, C& sub, int depth);
		template<typename Iter>
		Iter binarySearch(Iter begin, Iter end, int value);
		int jacobsthal(int n, int max);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &obj);
		PmergeMe& operator=(const PmergeMe &obj);

		std::vector<std::pair<int, int> > mergeInsertionSort(std::vector<std::pair<int, int> >& v, int depth);
		IndexableList<std::pair<int, int> > mergeInsertionSort(IndexableList<std::pair<int, int> >& l, int depth);
};


template<typename T>
void	printContainer(T& a, const char* name) {
	typedef typename T::iterator Iter;

	std::cout << name << ": ";
	for (Iter iter = a.begin(); iter != a.end(); iter++)
		std::cout << (*iter).first << " ";
	std::cout << std::endl;;
}


#endif