/***********************************************************
// OOP244 Milestone 5: Aid Management Application
// File Good.cpp
// Version 1.0
// Date July. 31, 2019
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
#include <string>
#include <iomanip>
#include "Perishable.h"
using namespace std;
namespace aid {
	Perishable::Perishable() : Good('P') {}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		file << "," << m_date;
		if (newLine == true) {
			file << endl;
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		file.ignore();
		m_date.read(file);
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);

		if (isEmpty() == false && isClear() == true) {
			if (linear) {
				os << expiry();
			}
			else {
				os << "\n Expiry date: " << expiry();
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is) {
		Date dTempie;
		int error;
		Good::read(is);
		if (is.fail() == false) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			dTempie.read(is);
			if (dTempie.bad() == true) {
				is.setstate(std::ios::failbit);
				error = dTempie.errCode();
				if (error == CIN_FAILED) {
					this->message("Invalid Date Entry");
				}
				else if (error == YEAR_ERROR) {
					this->message("Invalid Year in Date Entry");
				}
				else if (error == MON_ERROR) {
					this->message("Invalid Month in Date Entry");
				}
				else if (error == DAY_ERROR) {
					this->message("Invalid Day in Date Entry");
				}
				else if (error == PAST_ERROR) {
					this->message("Invalid Expiry in Date Entry");
				}
			}
			else {
				m_date = dTempie;
			}
		}
		return is;
	}
	const Date& Perishable::expiry() const {
		return m_date;
	}
	iGood* CreateProduct(char tag) {
		iGood* tempObj = nullptr;
		if (tag == 'n' || tag == 'N') {
			tempObj = new Good();
		}
		else if (tag == 'P' || tag == 'p') {
			tempObj = new Perishable();
		}
		return tempObj;
	}
}
