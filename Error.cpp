/***********************************************************
// OOP244 Milestone 2: Aid Management Application
// File Error.cpp
// Version 1.0
// Date July. 18, 2019
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
#include "Error.h"
namespace aid {
	Error::Error(const char* errorMessage) {
		m_address = nullptr;
		message(errorMessage);
	}
	Error::~Error() {
		delete[] m_address;
		clear();
	}
	void Error::clear() {
		m_address = nullptr;
	}
	bool Error::isClear() const {
		bool valid;
		if (m_address == nullptr) {
			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}
	void Error::message(const char* str) {
		if (str != nullptr){
			clear();

			m_address = new char[strlen(str) + 1];
			strcpy(m_address, str);
		}
		else {
			m_address = nullptr;
		}
		
	}
	const char* Error::message() const {
		if (isClear()) {
			return nullptr;;
		}
		else {
			return m_address;
		}
	}
	std::ostream& operator<<(std::ostream& os, Error& obj) {
		if (obj.isClear()) {
			return os;
		}
		else {
			return os << obj.message();
		}
	}
}