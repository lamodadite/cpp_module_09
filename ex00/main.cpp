#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "wrong arguments" << std::endl;
		return 1;
	}

	BitcoinExchange be(av[1]);
	be.printData();
}