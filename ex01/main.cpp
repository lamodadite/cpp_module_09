#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "no arguments" << std::endl;
		return 1;
	}

	try {
		RPN rpn(av[1]);
		rpn.calculate();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}