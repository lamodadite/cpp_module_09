#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <stack>
#include <sstream>

class RPN {
	private:
		std::string av;
		std::stack<double> rpnStack;
		std::stack<std::string> splitedAv;

		RPN();
		bool isOper(std::string line);
		void calculator(std::string line);
		bool isValidNum(double num, char* endptr);
	public:
		~RPN();
		RPN(const RPN &obj);
		RPN& operator=(const RPN &obj);

		RPN(std::string av);
		void calculate();
};

#endif