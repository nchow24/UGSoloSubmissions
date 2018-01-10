// main.cpp : Defines the entry point for the console application. Includes the Wt application 
// Nicole Chow	nchow24		250725575
// Oct 3, 2017

#include <stdio.h>
#include <iostream>
#include <vector>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WServer>
#include "Randomizer.h"
#include "MyResource.h"
#include "log.h"
#include "ClassPerson.h"

using namespace Wt;
using namespace std;
extern std::vector<Person> book;


/*
* An address book application class which generates a list of people from a given input value
*/
class AddressBookApplication : public WApplication
{
public:
	AddressBookApplication(const WEnvironment& env);

private:
	WLineEdit *numberEdit_;
	WText *addressBook_;

	void generatePeople();
};


AddressBookApplication::AddressBookApplication(const WEnvironment& env)
	: WApplication(env)
{
	setTitle("NCHOW24 3307 Assignment 1");										// application title

	root()->addWidget(new WText("How many people to generate? "));				// text to ask user how many people to generate
	numberEdit_ = new WLineEdit(root());										// user text input
	numberEdit_->setFocus();													// give focus

	WPushButton *button
		= new WPushButton("Submit", root());									// submit button
	button->setMargin(5, Left);													// add 5 pixels margin

	root()->addWidget(new WBreak());											// insert a line break

	addressBook_ = new WText(root());											// empty text

	std::string list = "<br /> Current list of people: <br />";
	for (int i = 0; i < book.size(); i++) {
		list.append(book[i].getName().getFullName()).append("<br />");
	}

	addressBook_->setText(list);

	button->clicked().connect(this, &AddressBookApplication::generatePeople);	//call generatePeople() when form is submitted

	numberEdit_->enterPressed().connect
	(boost::bind(&AddressBookApplication::generatePeople, this));

}

// Function Name: generatePeople()
// Parameters: None
// Return: None
// Description: takes a user's input and validates it as a positive integer, as many Person records in a list as specified by the user
void AddressBookApplication::generatePeople()
{
	//get user input and check if it is a valid positive integer
	std::string input = numberEdit_->text().toUTF8();
	bool num = true;
	for (int i = 0; i < input.length(); i++) {
		if (!(isdigit(input[i]))) {
			num = false;
		}
	}

	//error message for invalid inputs
	if (!num) {
		addressBook_->setText("Please input valid positive integer");
	}

	//create a new list of people based from the user input and display them
	//also display the list of people generated (just their full names)
	else {
		int number = atoi(input.c_str());
		std::string list = "<br /> Current list of people: <br />";
		srand(time(NULL));
		book.clear();
		for (int i = 0; i < number; i++) {
			Person x = Randomizer::randomPerson();
			x.setId(i + 1);
			book.push_back(x);
			list.append(x.getName().getFullName()).append("<br />");

		}
		addressBook_->setText(list);
	}
}

WApplication *createApplication(const WEnvironment& env)
{
	return new AddressBookApplication(env);
}

int main(int argc, char **argv)
{
	//from the helper link on OWL
	WLogger logger;
	configLogger(logger);
	try {
		WServer server(argv[0], "");
		try {
			server.setServerConfiguration(argc, argv);

			//from the helper link on OWL
			Wt::WServer server(argv[0]);
			server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
			server.addResource(new MyResource, "/people");
			server.addEntryPoint(Wt::Application, createApplication);

			info(logger, "Starting resource server.");
			if (server.start()) {
				WServer::waitForShutdown();
				server.stop();
			}
			else {
				fatal(logger, "Fatal error starting resource server.");
				return 1;
			}
			return 0;
		}
		catch (std::exception& e) {
			fatal(logger, "Fatal error starting resource server.", e.what());
			return 1;
		}
	}
	catch (WServer::Exception& e) {
		fatal(logger, "Fatal error creating WServer.", e.what());
		return 1;
	}
	catch (exception& e) {
		fatal(logger, "Fatal error occurred.", e.what());
		return 1;
	}
}
