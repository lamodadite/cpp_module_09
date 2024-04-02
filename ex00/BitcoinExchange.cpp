#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) {
	*this = obj;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj) {
	(void) obj;
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::string inputFile) {
	inputFileStream.open(inputFile.c_str());
	if (!inputFileStream.is_open()) {
		throw std::runtime_error("file open fail error");
	}
	loadDataFile();
}

void BitcoinExchange::loadDataFile() {
	std::string line;

	dataFileStream.open("data.csv");
	if (!dataFileStream.is_open()) {
		throw std::runtime_error("file open fail error");
	}
	std::getline(dataFileStream, line);
	while (!dataFileStream.eof()) {
		std::getline(dataFileStream, line);
		if (isAllWhiteSpace(line))
			continue ;
		std::istringstream	iss(line);
		std::string	sYear;
		std::string	sMonth;
		std::string	sDay;
		std::string	sRate;
		int			iDate;
		double		dRate;

		std::getline(iss, sYear, '-');
		std::getline(iss, sMonth, '-');
		std::getline(iss, sDay, ',');
		std::getline(iss, sRate);
		iDate = dateStoi(sYear, sMonth, sDay);
		dRate = std::strtod(sRate.c_str(), NULL);
		data[iDate] = dRate;
	}
}

bool BitcoinExchange::isAllWhiteSpace(std::string line) {
	for (size_t i = 0; i < line.length(); i++) {
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (false);
	}
	return (true);
}


int BitcoinExchange::dateStoi(std::string sYear, std::string sMonth, std::string sDay) {
	int	year;
	int	month;
	int day;
	int	convertedDate;

	year = static_cast<int>(std::strtod(sYear.c_str(), NULL));
	month = static_cast<int>(std::strtod(sMonth.c_str(), NULL));
	day = static_cast<int>(std::strtod(sDay.c_str(), NULL));
	convertedDate = (year * 10000) + (month * 100) + day;
	return (convertedDate);
}

void BitcoinExchange::printData() {
	for (std::map<int, double>::const_iterator it = data.begin(); it != data.end(); ++it) {
    std::cout << it->first << " : " << it->second << std::endl;
  }
}


