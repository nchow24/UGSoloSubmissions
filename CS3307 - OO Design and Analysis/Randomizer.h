// ClassRandomizer.h : Defines the Randomizer class which is used to generate a Person object with random data members
// Methods include generating a random Name, random Address, random Phone and a Person.
// Nicole Chow	nchow24		250725575
// Oct 3, 2017


#pragma once
#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <string>
#include <random>
#include <ctime>
#include "ClassName.h"
#include "ClassAddress.h"
#include "ClassPhone.h"
#include "ClassPerson.h"

class Randomizer {
	private:

		// Function Name: randomName()
		// Parameters: None
		// Return: Name object
		// Description: returns a Name consisting of a random first name and random last name from a set of hard coded choices
		static Name randomName(void) {
			std::string first[15] = { "Alex", "Julie", "Codi", "Denise", "Elliot", "Fiona", "George","Heather", "Ian","Jessica","Kaleb","Mona","Tony","Valerie","Steve" };
			std::string last[15] = { "Doe", "Smith", "Jones", "Williams", "Johnson", "Brown", "Davis","Miller", "Wilson","Anderson","Jackson","Moore","Robinson","Wright","Harris" };
			int firstNum = rand() % 15;
			int lastNum = rand() % 15;
			Name name;
			name.setFirst(first[firstNum]);
			name.setLast(last[lastNum]);
			return name;
		}

		// Function Name: randomAddress()
		// Parameters: None
		// Return: Address object
		// Description: returns an Address consisting of a random street, random city, random province and constant country from a set of hard coded choices
		static Address randomAddress(void) {
			std::string streetName[10] = { "Hill Lane", "Heritage Avenue", "Emerald Route", "Campus Route", "New Castle Row", "Dove Passage", "Cliff Street", "Coral Street", "Beachside Lane", "Rainbow Road" };
			std::string city[10] = { "Merrowholt","Lightlea", "Bybridge", "Deerland", "Bushcliff", "Corcrest", "Stonebrook", "Vallake", "Westbridge", "Northdell" };
			std::string province[10] = { "Ontario","Quebec","Newfoundland and Labrador","Nova Scotia", "New Brunswick", "Manitoba","British Columbia","Prince Edward Island","Saskatchewan","Alberta" };
			int streetNum = rand() % 100 + 1;
			int street = rand() % 10;
			int cityNum = rand() % 10;
			int provinceNum = rand() % 10;
			Address address;
			address.setStreet(std::to_string(streetNum) + " " + streetName[street]);
			address.setCity(city[cityNum]);
			address.setProvince(province[provinceNum]);
			return address;
		}

		// Function Name: randomPhone()
		// Parameters: None
		// Return: Phone object
		// Description: returns a Phone consisting of phone number of random digits 
		static Phone randomPhone(void) {
			int digit;
			std::string number = "";
			for (int i = 1; i <= 10; i++) {
				if (i == 1 || i == 4) {
					digit = rand() % 9 + 1;
				} else {
					digit = rand() % 10;
				}
				number.append(std::to_string(digit));
				if (i == 3 || i == 6) {
					number.append("-");
				}
			}

			Phone phone;
			phone.setNumber(number);
			return phone;
		}

	public:

		// Function Name: randomPerson()
		// Parameters: None
		// Return: Person object
		// Description: returns a Person with a Name, Address and Phone by calling the randomName(), randomAddress() and randomPhone() methods
		static Person randomPerson(void) {
			Person person;
			person.setName(randomName());
			person.setAddress(randomAddress());
			person.setPhone(randomPhone());
			return person;
		}

};

#endif	/* CLASSRANDOMIZER_H_ */
