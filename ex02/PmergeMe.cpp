#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &obj) {
	*this = obj;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &obj) {
	(void) obj;
	return *this;
}

std::vector<int> PmergeMe::mergeInsertionSort(std::vector<int>& v) {
	std::vector<int> main;
	std::vector<int> sub;

	if (v.size() == 1) {
		return v;
	}
	for (size_t i = 0; i < v.size() - 1; i += 2) {
		main.push_back(std::max(v.at(i), v.at(i + 1)));
		sub.push_back(std::min(v.at(i), v.at(i + 1)));
	}
	if (v.size() % 2 == 1)
		sub.push_back(v.at(v.size() - 1));

	std::vector<int> ret(mergeInsertionSort(main));
	std::vector<int> cpy(ret);

	//printContainer(main, "before arrange main");
	//printContainer(sub, "before arrange");
	sub = rearrange(ret, main, sub);
	//printContainer(sub, "after arrange");
	cpy.insert(binarySearch(cpy.begin(), cpy.end(), sub[0]), sub[0]);
	//printContainer(cpy, "after insert sub[0]");
	for (size_t i = 1; i < sub.size(); i++) {
		int jn = jacobsthal(i, sub.size());
		//std::cout << "jacobsthal num : " << jn << std::endl;
		cpy.insert(binarySearch(cpy.begin(), cpy.end(), sub[jn]), sub[jn]);
		//printContainer(cpy, "after insert jacobsthal num : ");
	}
	std::cout << std::endl;
	return cpy;
}

template<typename C>
C	PmergeMe::rearrange(C& ret, C& main, C& sub) {
	typedef typename C::iterator Iter;
	C arrangedSub;

	for (Iter iter = ret.begin(); iter != ret.end(); iter++) {
		Iter cur = std::find(main.begin(), main.end(), *iter);
		int idx = std::distance(main.begin(), cur);
		arrangedSub.push_back(sub.at(idx));
	}
	if (sub.size() != main.size()) {
		arrangedSub.push_back(sub.at(sub.size() - 1));
	}
	return arrangedSub;
}

template<typename Iter>
Iter	PmergeMe::binarySearch(Iter begin, Iter end, int value) {
	while (begin < end) {
		Iter mid(begin + (end - begin) / 2);

		if (value < *mid) {
			end = mid;
		} else {
			begin = mid + 1;
		}
	}
	return begin;
}

int PmergeMe::jacobsthal(int n, int max) {
	int jacobs[18] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381};
	for (int i = 0; i != 18; i++) {
		if (jacobs[i] <= n && n < jacobs[i + 1])
			return (jacobs[i] + (std::min(max, jacobs[i + 1]) - n) - 1);
	}
	return (n);
}