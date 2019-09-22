/***********************************************************
// OOP244 Milestone 1: Aid Management Application
// File Contact.h
// Version 1.0
// Date July. 3, 2019
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
#define _CRT_SECURE_NO_WARNINGS

#ifndef AID_DATE_H
#define AID_DATE_H

namespace aid {
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {
#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

		int m_year;
		int m_month;
		int m_day;
		int errorCode;
		int comparator;
		void errCode(int errorCode);
		int mdays(int year, int month) const;
	public:
		Date();
		Date(int year, int month, int date);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Date& date);
	std::istream& operator>>(std::istream& istr, Date& date);
}
#endif