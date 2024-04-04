#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &obj) {
	*this = obj;
}

RPN& RPN::operator=(const RPN &obj) {
	(void) obj;
	return (*this);
}

RPN::RPN(std::string av) : av(av) {}

void RPN::calculate() {
	std::istringstream ss(av);
	std::string line;
	char* endptr;
	double num;

	while (std::getline(ss, line, ' ')) {
		if (line.empty()) {
			continue;
		}
		if (isOper(line)) {
			calculator(line);
			continue;
		}
		num = std::strtod(line.c_str(), &endptr);
		if (isValidNum(num, endptr)) {
			rpnStack.push(num);
		} else {
			throw std::runtime_error("Error");
		}
	}
	if (rpnStack.size() == 1) {
		std::cout << rpnStack.top() << std::endl;
	} else {
		throw std::runtime_error("Error");
	}
}

void RPN::calculator(std::string line) {
	double n1;
	double n2;

	if (rpnStack.size() >= 2) {
		n1 = rpnStack.top();
		rpnStack.pop();
		n2 = rpnStack.top();
		rpnStack.pop();
	} else {
		throw std::runtime_error("Error");
	}
	if (line == "+") {
		rpnStack.push(n2 + n1);
	} else if (line == "-") {
		rpnStack.push(n2 - n1);
	} else if (line == "/") {
		rpnStack.push(n2 / n1);
	} else if (line == "*") {
		rpnStack.push(n2 * n1);
	} else {
		throw std::runtime_error("Error");
	}
}

bool RPN::isOper(std::string line) {
	if (line == "-" || line == "+" || line == "/" || line == "*") {
		return true;
	}
	return false;
}

bool RPN::isValidNum(double num, char* endptr) {
	if (*endptr != '\0' || num >= 10) {
		return false;
	}
	return true;
}
