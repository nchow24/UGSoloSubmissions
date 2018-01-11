// ClassPerson.h : Defines the Person class whose data members consist of an id, Name object, Address object and Phone object
// Methods include getters, setters and to JSON formats for the members
// Nicole Chow	nchow24		250725575
// Oct 3, 2017


#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include "ClassName.h"
#include "ClassAddress.h"
#include "ClassPhone.h"

class Person {
	//Person data members (Name, Address, Phone)
	Name name;
	Address address;
	Phone phone;
	int id;
	
	public:
		// Function Name: getName()
		// Parameters: None
		// Return: Name object
		// Description: returns the Name
		Name getName(void) {
			return name;
		}

		// Function Name: getAddress()
		// Parameters: None
		// Return: Address object
		// Description: returns the Address
		Address getAddress(void) {
			return address;
		}

		// Function Name: getPhone()
		// Parameters: None
		// Return: Phone object
		// Description: returns the Phone
		Phone getPhone(void) {
			return phone;
		}

		// Function Name: getId()
		// Parameters: None
		// Return: integer of the id
		// Description: returns the id
		int getId(void) {
			return id;
		}

		// Function Name: setId()
		// Parameters: int
		// Return: None
		// Description: sets the id
		void setId(int newId) {
			id = newId;
		}

		// Function Name: setName()
		// Parameters: Name object
		// Return: None
		// Description: sets the Name
		void setName(Name newName) {
			name = newName;
		}

		// Function Name: setAddress()
		// Parameters: Address object
		// Return: None
		// Description: sets the Address
		void setAddress(Address newAddress) {
			address = newAddress;
		}

		// Function Name: setPhone()
		// Parameters: Phone object
		// Return: None
		// Description: sets the Phone
		void setPhone(Phone newPhone) {
			phone = newPhone;
		}


		// Function Name: idToJSON()
		// Parameters: None
		// Return: string of the field and field's value 
		// Description: returns the id in JSON format
		std::string idToJSON(void) {
			return "\"id\":\"" + std::to_string(id) + "\"";

		}

		// Function Name: generalToJSON()
		// Parameters: None
		// Return: string of the field and field's value for the Name and id
		// Description: returns Name and id information about a Person in JSON format
		std::string generalToJSON(void){
			return "{ " + idToJSON() + ", " + getName().firstToJSON() + ", " + getName().lastToJSON() + " }";
		}

		// Function Name: allToJSON()
		// Parameters: None
		// Return: string of the field and field's value for each data member
		// Description: returns all information about a Person in JSON format
		std::string allToJSON(void) {
			return "{ <br />" + idToJSON() + ", <br />" + getName().firstToJSON() + ", <br />" + getName().lastToJSON() + ", <br />" + getAddress().streetToJSON() + ", <br />" + getAddress().cityToJSON() + ", <br />" + getAddress().provinceToJSON() + ", <br />" + getAddress().countryToJSON() + ", <br />" + getPhone().phoneToJSON() + "<br />" + "}";
		}
};

#endif	/* CLASSPERSON_H_ */
