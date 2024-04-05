#include <PmergeMe.hpp>

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
	std::vector<int> originalData;
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
			originalData.push_back(static_cast<int>(strtod(stringBuffer.c_str(), NULL)));
		}
		++i;
	}
	PmergeMe pm;
	std::vector<int> sorted = pm.mergeInsertionSort(originalData);
	printContainer(originalData, "before");
	printContainer(sorted, "after");
	return 0;
}