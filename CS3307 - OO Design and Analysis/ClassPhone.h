// ClassPhone.h : Defines the Phone class which has 1 data member: phone number
// Methods include getters, setters and to JSON formats for the member
// Nicole Chow	nchow24		250725575
// Oct 3, 2017


#pragma once
#ifndef CLASSPHONE_H
#define CLASSPHONE_H

#include <string>

class Phone {
	//data members (phone number)
	std::string number;

	public:
		// Function Name: getNumber()
		// Parameters: None
		// Return: string of the phone number
		// Description: returns the phone number
		std::string getNumber(void) {
			return number;
		}

		// Function Name: setNumber()
		// Parameters: string
		// Return: None
		// Description: sets the phone number
		void setNumber(std::string newNumber) {
			number = newNumber;
		}


		// Function Name: phoneToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the phone number in JSON format
		std::string phoneToJSON(void) {
			return "\"phone\":\"" + number + "\"";
		}
};

#endif	/* CLASSPHONE_H_ */
