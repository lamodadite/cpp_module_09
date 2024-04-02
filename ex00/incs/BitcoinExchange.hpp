#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <sstream>

class BitcoinExchange {
	private:
		std::map<int, double> data;
		std::ifstream inputFileStream;
		std::ifstream dataFileStream;

		BitcoinExchange();
		void loadDataFile();
		bool isAllWhiteSpace(std::string line);
		int dateStoi(std::string sYear, std::string sMonth, std::string sDay);
	public:
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange& operator=(const BitcoinExchange &obj);

		BitcoinExchange(std::string inputFile);

		void printData();
};

#endif