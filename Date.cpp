/***********************************************************
// OOP244 Workshop 6: Class with a Resource
// File Contact.cpp
// Version 1.0
// Date July. 2, 2019
// Author Nilan Patel
// Student Number: <038 908 117>
// Section SEE
// Description
//
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
***********************************************************/
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Date.h"
using namespace std;

namespace aid {

	Date::Date() {
		m_year = 0000;
		m_month = 00;
		m_day = 00;
		comparator = 0;
		errorCode = NO_ERROR;
	}
	Date::Date(int year, int month, int day) {
		int numberOfDays = mdays(year, month);
		int yearValid = (year >= min_year && year <= max_year);
		int monthValid = (month >= 1 && month <= 12);
		int dayValid = (numberOfDays != 13 && day <= numberOfDays);
		comparator = year * 372 + month * 13 + day;

		if (yearValid == 1 && monthValid == 1 && dayValid == 1) {
			m_year = year;
			m_month = month;
			m_day = day;
			errCode(NO_ERROR);
		}
		else if (yearValid != 1 && monthValid == 1 && dayValid == 1) {
			errCode(YEAR_ERROR);
		}
		else if (yearValid == 1 && monthValid != 1 && dayValid == 1) {
			errCode(MON_ERROR);
		}
		else if (yearValid == 1 && monthValid == 1 && dayValid != 1) {
			errCode(DAY_ERROR);
		}
		else if (m_year * 372 * 31 + m_day < min_date) {
			errCode(PAST_ERROR);
		}
		else {
			errCode(NO_ERROR);

		}
	}
	void Date::errCode(int errorCode1) {
		errorCode = errorCode1;
	}
	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	bool Date::operator==(const Date& rhs) const {
		return (this->comparator == rhs.comparator);

	}
	bool Date::operator!=(const Date& rhs) const {
		return (this->comparator != rhs.comparator);

	}
	bool Date::operator<(const Date& rhs) const {
		return (this->comparator < rhs.comparator);

	}
	bool Date::operator>(const Date& rhs) const {
		return (this->comparator > rhs.comparator);

	}
	bool Date::operator<=(const Date& rhs) const {
		return (this->comparator <= rhs.comparator);

	}
	bool Date::operator>=(const Date& rhs) const {

		return this->comparator >= rhs.comparator;

	}
	int Date::errCode() const {
		return errorCode;
	}
	bool Date::bad() const {
		if (errorCode != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	std::istream& Date::read(std::istream& istr) {
		char dash;
		int year, month, day;

		istr >> year >> dash >> month >> dash >> day;
		comparator = year * 372 + month * 31 + day;
		errCode(NO_ERROR);
		if (istr.fail()) {
			errCode(CIN_FAILED);
		}
		else if (min_year > year || year > max_year) {
			errCode(YEAR_ERROR);
		}
		else if (1 > month || month > 12) {
			errCode(MON_ERROR);
		}
		else if (day > mdays(year, month)) {
			errCode(DAY_ERROR);
		}
		else if (comparator < min_date) {
			errCode(PAST_ERROR);
		}
		else {
			errCode(NO_ERROR);
			m_year = year;
			m_month = month;
			m_day = day;
		}
		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr) const {
		ostr.fill('0');
		ostr << m_year << "/";
		ostr.width(2);
		ostr << m_month << "/";
		ostr.width(2);
		ostr << m_day;
		ostr.fill(' ');
		return ostr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		return date.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Date& date) {
		return date.read(istr);
	}
}