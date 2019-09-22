/***********************************************************
// OOP244 Milestone 5: Aid Management Application
// File Perishable.h
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
#define _CRT_SECURE_NO_WARNINGS

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H
#include <iostream>
#include "Good.h"
#include "Date.h"

namespace aid {
	class Perishable : public Good {
		Date m_date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
	iGood* CreateProduct(char tag);
}



#endif