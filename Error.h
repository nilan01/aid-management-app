/***********************************************************
// OOP244 Milestone 2: Aid Management Application
// File Error.h
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
#define _CRT_SECURE_NO_WARNINGS

#ifndef AID_ERROR_H
#define AID_ERROR_H
#include<iostream>

namespace aid {
	class Error {
		char* m_address;
	public:
		explicit Error(const char* errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, Error&);
}



#endif