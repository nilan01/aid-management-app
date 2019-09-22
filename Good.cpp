/***********************************************************
// OOP244 Milestone 3: Aid Management Application
// File Good.cpp
// Version 1.0
// Date July. 29, 2019
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
#include <memory>
#include <fstream>
#include <iomanip>
#include "Good.h"
#include "Error.h"
using namespace std;
namespace aid {
	Good::Good(char goodType){
		m_good = goodType;
		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_nameOfGood = nullptr;
		m_qtyOnHand = 0;
		m_qtyNeeded = 0;
		m_priceBeforeTax = 0.0;
		m_taxableStatus = false;
		//m_errorState.message(nullptr);
	}
	Good::Good(const char* sku, const char* nameOfGood,
		const char* unit, int qtyOnHand, bool taxableStatus, double priceBeforeTax, int qtyNeeded) {
		if (nameOfGood != nullptr && unit != nullptr && sku != nullptr) {
			if (nameOfGood[0] != '\0' || unit[0] != '\0' || sku[0] != '\0') {
				m_good = 'N';
				name(nameOfGood);
				strncpy(m_sku, sku, max_sku_length);
				m_sku[max_sku_length] = '\0';
				strncpy(m_unit, unit, max_unit_length);
				m_unit[max_unit_length] = '\0';
				m_qtyOnHand = qtyOnHand;
				m_taxableStatus = taxableStatus;
				m_priceBeforeTax = priceBeforeTax;
				m_qtyNeeded = qtyNeeded;
				if (m_nameOfGood[0] == 'w' || m_nameOfGood[0] == 'W') {
					m_good = 'P';
				}
			}
			else {
				*this = Good();
			}
		}
		else {
			*this = Good();
		}
	}
	Good::Good(const Good& tempObj) {
		name(tempObj.m_nameOfGood);
		strncpy(m_sku, tempObj.m_sku, max_sku_length);
		strncpy(m_unit, tempObj.m_unit, max_unit_length);
		this->m_qtyOnHand = tempObj.m_qtyOnHand;
		this->m_taxableStatus = tempObj.m_taxableStatus;
		this->m_priceBeforeTax = tempObj.m_priceBeforeTax;
		this->m_qtyNeeded = tempObj.m_qtyNeeded;
	}
	Good& Good::operator=(const Good& currentObj) {
		if (this != &currentObj) {
			name(currentObj.m_nameOfGood);
			strncpy(m_sku, currentObj.m_sku, max_sku_length);
			strncpy(m_unit, currentObj.m_unit, max_unit_length);
			this->m_qtyOnHand = currentObj.m_qtyOnHand;
			this->m_taxableStatus = currentObj.m_taxableStatus;
			this->m_priceBeforeTax = currentObj.m_priceBeforeTax;
			this->m_qtyNeeded = currentObj.m_qtyNeeded;
		}
		return *this;
	}
	Good::~Good() {
		if (m_nameOfGood != nullptr) {
			delete[] m_nameOfGood;
		}
	}
	void Good::name(const char* name) {
		if (name != nullptr) {
			m_nameOfGood = new char[max_name_length + 1];
			strncpy(m_nameOfGood, name, max_name_length);
			m_nameOfGood[max_name_length] = '\0';
		}
		else {
			m_nameOfGood = new char;
			m_nameOfGood[0] = '\0';
		}
	}
	const char* Good::name() const{
		if (m_nameOfGood != nullptr && m_nameOfGood[0] != '\0') {
			return m_nameOfGood;
		}
		else {
			return nullptr;
		}
	}
	const char* Good::sku() const {
		return m_sku;
	}
	const char* Good::unit() const {
		return m_unit;
	}
	bool Good::taxed() const {
		return m_taxableStatus;
	}
	double Good::itemPrice() const {
		return m_priceBeforeTax;
	}
	double Good::itemCost() const {
		double cost = itemPrice();
		if (m_taxableStatus != false) {
			cost = cost * (tax_rate + 1);
		}
		else {
			cost = itemPrice();
		}
		return cost;
	}
	void Good::message(const char* message){
		m_errorState.message(message);
	}
	bool Good::isClear() const {
		return m_errorState.isClear();
	}
	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		file << m_good << ',' << m_sku << ',' << m_nameOfGood << ',' << m_unit << ',' << m_taxableStatus << "," 
			<< m_priceBeforeTax << "," << m_qtyOnHand << "," << m_qtyNeeded;
		if (newLine == true) {
			file << std::endl;
		}
		return file;
	}
	std::fstream& Good::load(std::fstream& file) {
		Good obj;
		obj.m_nameOfGood = new char[max_name_length + 1];
		char dump;
		if (file.is_open()){
			file.getline(obj.m_sku, max_sku_length, ',');
			file.getline(obj.m_nameOfGood, max_name_length, ',');
			file.getline(obj.m_unit, max_unit_length, ',');
			file >> obj.m_taxableStatus >> dump;
			file >> obj.m_priceBeforeTax >> dump;
			file >> obj.m_qtyOnHand >> dump;
			file >> obj.m_qtyNeeded;

			*this = obj;
		}

		delete[] obj.m_nameOfGood;
		obj.m_nameOfGood = nullptr;
		return file;
	}
	std::ostream& Good::write(std::ostream& os, bool linear) const {

		if (m_errorState.isClear() == false) {
			os << m_errorState.message();
		}
		else {
			
			if (isEmpty() == false) {
				
				if (linear) {
					os.setf(ios::fixed);
					os.precision(2);

					os.width(max_sku_length);
					os.setf(ios::left);
					os << sku() << '|';

					os.width(20);
					os << name() << '|';

					os.width(7);
					os.unsetf(ios::left);
					os << itemCost() << '|';


					os.width(4);
					os << m_qtyOnHand << '|';
					os.width(10);
					os.setf(ios::left);
					os << m_unit << '|';

					os.unsetf(ios::left);
					os.width(4);
					os << qtyNeeded() << '|';
				}
				else {
					os << " Sku: " << m_sku << std::endl
						<< " Name (no spaces): " << m_nameOfGood << std::endl
						<< " Price: " << m_priceBeforeTax << std::endl;
					if (m_taxableStatus)
					{
						os << " Price after tax: " << itemCost() << std::endl;
					}
					else
					{

						os << " Price after tax:  N/A" << std::endl;
					}
					os << " Quantity on Hand: " << m_qtyOnHand << " " << m_unit << std::endl
						<< " Quantity needed: " << m_qtyNeeded;
				}
			}
		}
			
		return os;
	}
	std::istream& Good::read(std::istream& is){
		char skuP[max_sku_length + 1], unit_desc[max_name_length + 1], yn;
		char* name_p;
		name_p = new char[max_name_length + 1];
		int qtyHand, qtyNeeded;
		double priceBefore;
		bool tax;

		std::cout << " Sku: ";
		is >> skuP;
		std::cout << " Name (no spaces): ";
		is >> name_p;
		std::cout << " Unit: ";
		is >> unit_desc;
		std::cout << " Taxed? (y/n): ";
		is >> yn;

		if (yn == 'Y' || yn == 'y') {
			tax = true;
		}
		else if (yn == 'N' || yn == 'n') {
			tax = false;
		}
		else{
			is.setstate(std::ios::failbit);
			m_errorState.clear();
			m_errorState.message("Only (Y)es or (N)o are acceptable");
		}
		if (is.fail() == false){
			std::cout << " Price: ";
			is >> priceBefore;
			m_errorState.clear();
			if (is.fail() == true) {
				m_errorState.message("Invalid Price Entry");
			}
		}

		if (is.fail() == false){
			std::cout << " Quantity on hand: ";
			is >> qtyHand;
			m_errorState.clear();
			if (is.fail() == true) m_errorState.message("Invalid Quantity Entry");
		}

		if (is.fail() == false)
		{
			std::cout << " Quantity needed: ";
			is >> qtyNeeded;
			m_errorState.clear();
			if (is.fail() == true) m_errorState.message("Invalid Quantity Needed Entry");
		}

		if (is.fail() == false)
		{
			m_errorState.clear();
			Good temp = Good(skuP, name_p, unit_desc, qtyHand, tax, priceBefore, qtyNeeded);
			*this = temp;
		}
		delete[] name_p;
		name_p = nullptr;

		return is;
	}
	bool Good::operator==(const char* compObj) const {
		bool flag;
		if (this->m_sku == compObj) {
			flag = true;
		}
		else {
			flag = false;
		}
		return flag;
	}
	double Good::total_cost() const {											
		double totalCost = itemCost() * m_qtyOnHand;
		return totalCost;
	}
	void Good::quantity(int qty) {
		if (qty > 0) {
			m_qtyOnHand = qty;
		}
	}
	bool Good::isEmpty() const {
		bool flag;
		if (this->m_nameOfGood == nullptr) {
			flag = true;
		}
		else {
			flag = false;
		}
		return flag;
	}
	int Good::qtyNeeded() const {
		return m_qtyNeeded;
	}
	int Good::quantity() const {
		return m_qtyOnHand;
	}
	bool Good::operator>(const iGood& goo) const {
		bool flag;
		int result;
		result = (strcmp(this->m_sku, goo.name()));
			if (result > 0) {
				flag = true;
			}
			else {
				flag = false;
			}
			return flag;
	}
	bool Good::operator>(const Good& tempObj) const {
		bool flag;
		flag = (strcmp(m_nameOfGood, tempObj.m_nameOfGood));
		if (flag > 0) {
			flag = true;
		}
		else {
			flag = false;
		}
		return flag;
	}
	int Good::operator+=(int add) {
		if (add > 0) {
			return m_qtyOnHand += add;
		}
		else {
			return m_qtyOnHand;
		}
	}
	std::ostream& operator<<(std::ostream& os, const iGood& temp)
	{
		return temp.write(os, true);
	}
	std::istream& operator>>(std::istream& i, iGood& temp) {
		temp.read(i);
		return i;
	}
	double operator+=(double& total, const iGood& temp)
	{
		return total + temp.total_cost();
	}
}