// MyResource.cpp : Taken from the helper site on OWL and modified to implement a RESTful API with Wt
// This file executes when the user navigates to URL/people - the page either displays general information about all people 
// OR speciic information about 1 person if the user specifies and ID
// Nicole Chow	nchow24		250725575
// Oct 3, 2017

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Wt/Http/Response>
#include "MyResource.h"
#include "ClassPerson.h"

using namespace std;
using namespace Wt::Http;
std::vector<Person> book;

MyResource::MyResource() {
}

MyResource::~MyResource() {
}

void MyResource::handleRequest(const Request& request, Response& response) {

	//get the requested ID from the URL (if it exists) and give full details about a specific person
	//if there is no ID specified, give general information about all Persons
	//if ID is out of bounds, give error message
	string path = request.pathInfo();							//ID parameter
	string list = "{ <br/> \"people\": [ <br />";												//information to be displayed
	string title;												//title of page 

	//give general information about Persons
	if (path.empty()) {
		//create a string of all the Person record's general information  (id, first name, last name)
		for (int i = 0; i < book.size(); i++) {
			list.append(book[i].generalToJSON()).append("\n");
		}
		list.append("] <br />}");
		title = "ADDRESS BOOK - GENERAL INFORMATION:";
	}
	else {
		//get the Id from the URL
		string param = path.substr(1, path.size() - 1);
		int id = atoi(param.c_str());

		//get full Person details from the Id
		if (id > 0 && id <= book.size()) {
			list = book[id - 1].allToJSON();
			title = "ADDRESS BOOK - SPECIFIC PERSON INFORMATION:";
		}
		else {
			//error message for nonexistent ID
			list = "Person with ID: " + param + " does not exist";
			title = "ADDRESS BOOK - SPECIFIC PERSON INFORMATION:";
		}
	}

	//taken from the helper link on OWL
	int contentLength = request.contentLength();
	char* buffer = new char[contentLength + 1];
	request.in().read(buffer, contentLength);
	buffer[contentLength] = 0;
	response.setMimeType("application/xml");
	ostream& out = response.out();

	//display on the webpage
	out << "<?xml version='1.0' encoding='utf-8' ?>" << endl;
	out << "<?xml-stylesheet href='my-style.css' ?>" << endl;
	out << "<reply>" << endl;
	out << "<method>" << title << "</method>" << endl;
	out << "<string>" << list << "</string>" << endl;
	out << "</reply>";

	delete[] buffer;
}
