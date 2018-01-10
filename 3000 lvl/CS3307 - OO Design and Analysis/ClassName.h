// ClassName.h : Defines the Name class whose data members consist of a first name and last name. 
// Methods include getters, setters and to JSON formats for each member
// Nicole Chow	nchow24		250725575
// Oct 3, 2017

#pragma once
#ifndef CLASSNAME_H
#define CLASSNAME_H

#include <string>

class Name {
	//Name data members (first name, last name)
	std::string first;
	std::string last;

	public:

		// Function Name: getFirst()
		// Parameters: None
		// Return: string of the first name
		// Description: returns the first name
		std::string getFirst(void) {
			return first;
		}

		// Function Name: getLast()
		// Parameters: None
		// Return: string of the last name
		// Description: returns the last name
		std::string getLast(void) {
			return last;
		}

		// Function Name: getFullName()
		// Parameters: None
		// Return: string of the first and last name
		// Description: returns the first and last name
		std::string getFullName(void) {
			return first.append(" ").append(last);
		}

		// Function Name: setFirst()
		// Parameters: string
		// Return: None
		// Description: sets the first name
		void setFirst(std::string newFirst) {
			first = newFirst;
		}
	

		// Function Name: setLast()
		// Parameters: string
		// Return: None
		// Description: sets the last name
		void setLast(std::string newLast) {
		last = newLast;
		}


		// Function Name: firstToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the first name in JSON format
		std::string firstToJSON() {
			return "\"firstname\":\"" + first + "\"";
		}

		// Function Name: lastToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the last name in JSON format
		std::string lastToJSON() {
			return "\"lastname\":\"" + last + "\"";
		}

};

#endif	/* CLASSNAME_H_ */
