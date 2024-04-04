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

void BitcoinExchange::convertToRate() {
	std::string line;

	std::getline(inputFileStream, line);
	if (line != "date | value") {
		throw std::runtime_error("wrong input file : first line");
	}
	while (std::getline(inputFileStream, line)) {
		if (isAllWhiteSpace(line))
			continue ;
		if (!isValidFormat(line)) {
			std::cout << "Error: bad input => " << line << std::endl;
		} else if (!isValidDate()) {
			std::cout << "Error : invalid date => " << sDate << std::endl;
		} else if (fRate < 0) {
			std::cout << "Error : not a poistive number" << std::endl;
		} else if (fRate > 1000) {
			std::cout << "Error : too large a number" << std::endl;
		} else {
			displayResult();
		}
	}
}

bool BitcoinExchange::isValidFormat(std::string line) {
	std::string date;
	std::string delimiter;
	std::string rate;

	if (line.length() <= 12) {
		return false;
	}
	date = line.substr(0, 10);
	delimiter = line.substr(10, 3);
	rate = line.substr(13, line.length());

	if (!(date[4] == '-' && date[7] == '-')) {
		return false;
	}
	if (delimiter != " | ") {
		return false;
	}
	// 2014-04-11
	for (size_t i = 0; i < date.length(); i++) {
		if (i == 4 || i == 7) continue;
		if (!isdigit(date[i])) return false;
	}
	std::istringstream iss(rate);
	float fRate;
	iss >> fRate;
	if (iss.fail() || !iss.eof())
		return (false);

	sDate = date;
	this->fRate = fRate;
	return (true);
}

bool	BitcoinExchange::isValidDate() {
	int	year;
	int	month;
	int	day;
	
	year = static_cast<int>(strtod((sDate.substr(0, 4)).c_str(), NULL));
	month = static_cast<int>(strtod((sDate.substr(5, 2)).c_str(), NULL));
	day = static_cast<int>(strtod((sDate.substr(8, 2)).c_str(), NULL));

	if (year <= 0 || month <= 0 || month > 12 || day <= 0) {
		return (false);
	}
	if (month == 2) {
		if (isLeapYear(year) && day > 29) {
			return (false);
		}
		if (!isLeapYear(year) && day > 28) {
			return (false);
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30 || day < 0) {
			return (false);
		}
	} else {
		if (day > 31 || day < 0) { 
			return (false);
		}
	}
	iDate = year * 10000 + month * 100 + day;
	return (true);
}

bool	BitcoinExchange::isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return (true);
	else
		return (false);
}

void	BitcoinExchange::displayResult() {
	std::map<int, double>::iterator it = data.lower_bound(iDate);
	if (it->first != iDate) {
		if (it == data.begin()) {
			std::cout << "Error: no date matched" << std::endl;
			return ;
		}
		it--;
	}
	std::cout << sDate << " => " << fRate << " = " << fRate * it->second << std::endl;
}
