// ClassAddress.h : Defines the Address class whose data members consist of a  street, city, province and country
// Methods include getters, setters and to JSON formats for each member
// Nicole Chow	nchow24		250725575
// Oct 3, 2017


#pragma once
#ifndef CLASSADDRESS_H
#define CLASSADDRESS_H

#include <string>

class Address {
	//Address data members (street, city, province, country)
	std::string street;									
	std::string city;									
	std::string province;
	std::string country = "Canada";

	public:

		// Function Name: getStreet()
		// Parameters: None
		// Return: string of the street
		// Description: returns the street
		std::string getStreet(void) {
			return street;
		}

		// Function Name: getCity()
		// Parameters: None
		// Return: string of the city
		// Description: returns the lcity
		std::string getCity(void) {
			return city;
		}

		// Function Name: getProvince()
		// Parameters: None
		// Return: string of the province
		// Description: returns the province
		std::string getProvince(void) {
			return province;
		}

		// Function Name: getCountry()
		// Parameters: None
		// Return: string of the country
		// Description: returns the country
		std::string getCountry(void) {
			return country;
		}

		// Function Name: setStreet()
		// Parameters: string
		// Return: None
		// Description: sets the street
		void setStreet(std::string newStreet) {
			street = newStreet;
		}

		// Function Name: setCity()
		// Parameters: string
		// Return: None
		// Description: sets the city
		void setCity(std::string newCity) {
			city = newCity;
		}

		// Function Name: setProvince()
		// Parameters: string
		// Return: None
		// Description: sets the province
		void setProvince(std::string newProvince) {
			province = newProvince;
		}


		// Function Name: streetToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the street in JSON format
		std::string streetToJSON() {
			return "\"street\":\"" + street + "\"";
		}

		// Function Name: provinceToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the province in JSON format
		std::string provinceToJSON() {
			return "\"province\":\"" + province + "\"";
		}

		// Function Name: cityToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the city in JSON format
		std::string cityToJSON() {
			return "\"city\":\"" + city + "\"";
		}

		// Function Name: countryToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the country in JSON format
		std::string countryToJSON() {
			return "\"country\":\"" + country + "\"";
		}
};

#endif  /* CLASSADDRESS_H_ */
