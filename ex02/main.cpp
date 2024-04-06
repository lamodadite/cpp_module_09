#include <PmergeMe.hpp>
#include <ctime>

bool validateInput(std::string s) {
	char *endptr = NULL;
	double value = std::strtod(s.c_str(), &endptr);
	if (value == 0.0 && !std::isdigit(s[0])) {
		return false;
	}
	if (*endptr && std::strcmp(endptr, "f")) {
		return false;
	}
	if (value < 0) {
		return false;
	}
	return (value == static_cast<int>(value));
}

int main(int ac, char **av) {
	if (ac < 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	std::vector<std::pair<int, int> > originalDataVector;
	IndexableList<std::pair<int, int> > originalDataList;
	int i = 1;
	while (i < ac) {
		std::string stringTmp(av[i]);
		std::istringstream ss(stringTmp);
		std::string stringBuffer;
		while (std::getline(ss, stringBuffer, ' ')) {
			if (!stringBuffer.empty() && !validateInput(stringBuffer)) {
				std::cout << "Error" << std::endl;
				return 1;
			}
			if (stringBuffer.empty()) continue;
			int num = static_cast<int>(strtod(stringBuffer.c_str(), NULL));
			originalDataVector.push_back(std::make_pair(num, i - 1));
			originalDataList.push_back(std::make_pair(num, i - 1));

		}
		i++;
	}
	PmergeMe pm;

	printContainer(originalDataVector, "vector before");
	clock_t vecStart = clock();
	std::vector<std::pair<int, int> > sortedVector = pm.mergeInsertionSort(originalDataVector, 1);
	clock_t vecEnd = clock();
	printContainer(sortedVector, "vector after");

	std::cout << std::endl;
	printContainer(originalDataList, "list before");
	clock_t listStart = clock();
	IndexableList<std::pair<int, int> > sortedList = pm.mergeInsertionSort(originalDataList, 1);
	clock_t listEnd = clock();
	printContainer(sortedVector, "list after");

	std::cout << std::endl;
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << originalDataVector.size() << " elements with std::vector : " << (float)(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000 * 1000 << " us" << std::endl;
	std::cout << "Time to process a range of " << originalDataList.size() << " elements with std::list  : " << (float)(listEnd - listStart) / CLOCKS_PER_SEC * 1000 * 1000 << " us" << std::endl;
	return 0;
}