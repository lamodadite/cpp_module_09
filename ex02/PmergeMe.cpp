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

std::vector<std::pair<int, int> > PmergeMe::mergeInsertionSort(std::vector<std::pair<int, int> >& v, int depth) {
	std::vector<std::pair<int, int> > main;
	std::vector<std::pair<int, int> > sub;

	if (v.size() == 1) {
		return v;
	}
	for (size_t i = 0; i < v.size() - 1; i += 2) {
		main.push_back(std::max(v[i], v[i + 1]));
		sub.push_back(std::min(v[i], v[i + 1]));
	}
	if (v.size() % 2 == 1)
		sub.push_back(v[v.size() - 1]);

	std::vector<std::pair<int, int> > ret(mergeInsertionSort(main, depth + 1));

	sub = rearrange(ret, main, sub, depth);
	ret.insert(ret.begin(), sub[0]);
	for (size_t i = 1; i < sub.size(); i++) {
		int jn = jacobsthal(i, sub.size());
		std::vector<std::pair<int, int> >::iterator tmp = ret.begin();
		std::advance(tmp, std::min(jn + i, ret.size()));
		ret.insert(binarySearch(ret.begin(), tmp, sub[jn].first), sub[jn]);
	}
	return ret;
}

IndexableList<std::pair<int, int> > PmergeMe::mergeInsertionSort(IndexableList<std::pair<int, int> >& l, int depth) {
	IndexableList<std::pair<int, int> > main;
	IndexableList<std::pair<int, int> > sub;

	if (l.size() == 1) {
		return l;
	}
	for (size_t i = 0; i < l.size() - 1; i += 2) {
		main.push_back(std::max(l[i], l[i + 1]));
		sub.push_back(std::min(l[i], l[i + 1]));
	}
	if (l.size() % 2 == 1)
		sub.push_back(l[l.size() - 1]);

	IndexableList<std::pair<int, int> > ret(mergeInsertionSort(main, depth + 1));

	sub = rearrange(ret, main, sub, depth);
	ret.insert(ret.begin(), sub[0]);
	for (size_t i = 1; i < sub.size(); i++) {
		int jn = jacobsthal(i, sub.size());
		IndexableList<std::pair<int, int> >::iterator tmp = ret.begin();
		std::advance(tmp, std::min(jn + i, ret.size()));
		ret.insert(binarySearch(ret.begin(), tmp, sub[jn].first), sub[jn]);
	}
	return ret;
}

template<typename C>
C	PmergeMe::rearrange(C& ret, C& main, C& sub, int depth) {
	typedef typename C::iterator Iter;
	C arrangedSub;

	for (Iter iter = ret.begin(); iter != ret.end(); iter++) {
		arrangedSub.push_back(sub[(*iter).second / std::pow(2, depth)]);
	}
	if (sub.size() != main.size()) {
		arrangedSub.push_back(sub[sub.size() - 1]);
	}
	return arrangedSub;
}

template<typename Iter>
Iter PmergeMe::binarySearch(Iter begin, Iter end, int value) {
	while (begin != end) {
		Iter mid = begin;
		std::advance(mid, std::distance(begin, end) / 2);

		if (value < (*mid).first) {
			end = mid;
		} else if ((*mid).first < value) {
			begin = std::next(mid);
		} else {
			return mid;
		}
	}
	return end;
}

int PmergeMe::jacobsthal(int n, int max) {
	int jacobs[18] = {0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381};
	for (int i = 0; i < 18; i++) {
		if (jacobs[i] <= n && n < jacobs[i + 1]) {
			int ret = jacobs[i] + (std::min(max, jacobs[i + 1]) - n) - 1;
			return ret;
		}
	}
	return n;
}