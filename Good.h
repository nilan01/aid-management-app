/***********************************************************
// OOP244 Milestone 3: Aid Management Application
// File Error.h
// Version 1.0
// Date July. 23, 2019
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

#ifndef AID_GOOD_H
#define AID_GOOD_H
#include "iGood.h"
#include "Error.h"
const int max_sku_length = 7;
const int max_unit_length = 10;
const int max_name_length = 75;
const double tax_rate = 0.13;
namespace aid {
	class Good : public iGood{
	private:
		char m_good;
		char m_sku[max_sku_length + 1];
		char m_unit[max_unit_length + 1];
		char* m_nameOfGood;
		int m_qtyOnHand;
		int m_qtyNeeded;
		double m_priceBeforeTax;
		bool m_taxableStatus;
	public:
		Good(char goodType = 'N');
		Good(const char* sku, const char* nameOfGood, 
			const char* unit, int qtyOnHand = 0, bool taxableStatus = true, double priceBeforeTax = 0.0, int qtyNeeded = 0);
		Good(const Good&);
		Good& operator=(const Good& currentObj);
		~Good();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const iGood&) const;
		bool operator>(const Good&) const;
		int operator+=(int);
	protected:
		Error m_errorState;
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;
	};
	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);
}
#endif // !AID_GOOD_H