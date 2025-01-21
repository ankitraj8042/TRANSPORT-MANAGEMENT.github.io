#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <limits>
#include <cstring>   // For C-style string functions
#include <cstdlib>   // For general utilities
#include <cstdio>    // For standard input/output
#include <cctype>    // For character handling
#include <list>      // For doubly linked lists
#include <iomanip>   // For organizing output into columns
#include <vector>    // For dynamic arrays
#include <queue>     // For queue data structure
#include <algorithm> // For sorting and searching
#include <unordered_map> // For hash tables
#include <map>       // For associative containers
#include <cmath>     // For mathematical functions
using namespace std;
// forward declaration
class Person;
class Flight;
class Queue;

/* ----CLASSES---- */

class Menu //class for managing the app's menu
{
	public:
		static void displayMenu(); // displays the menu
		static void select(int selection); // receives user's input and performs the corresponding function
		static void exit_prog(); // exits the app
};

struct Time // structure for managing the Arrival and Departing times
{
	int min;
	int hour;
};

class Flight // class for managing the availabe functions of a flight
{
	private:

		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;
		Time t_leave, t_arrive;

	public:
		/* --ADD/REMOVE FLIGHTS--*/
		void addFlight(); //διαχειρίζεται την προσθήκη πτήσεων (επιλογή μενού Νο 1)
		static void deleteFlight(int num); //διαχειρίζεται την αφαίρεση πτήσεων (επιλογή μενού Νο 2)

		/* --DISPLAY FLIGHTS--*/
		static void displayFlightInfo(int num); //προβάλλει τις πληροφορίες μιας πτήσης (επιλογή μενού Νο 3)
		static void displaySchedule(); //προβάλλει τις πτήσεις που υπάρχουν καταχωρημένες στο σύστημα (επιλογή μενού Νο 4)

		/* --BOOK SEATS--*/
		static void resSeat(int num, int val); //αυξομειώνει τις κατοχυρωμένες θέσεις μιας πτήσεις

		/* --FLIGHT CHECKERS--*/
		static bool flightExists(int num); // check flight is booked
		static bool checkForSeats(int num); // checks for already registerd flight in the system

		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};

class Person //class for managing the functions of a passenger
{
	private:

		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;

	public:
		/* --BOOK FLIGHT-- */
		void book(); // book flight for each customer (Menu Option Νο 6)
		void bookFromQueue(int num); // book flight for the oldest customer in
					    // (call ONLY when a reservation is cancelled)
		void cancel(); //cancel a reservation (Menu Option Νο 7)

		/* --SHOW PASSENGER'S INFO-- */
		static bool displayPersonInfo(int passport);

		/* --CHECHKER FOR UNIQUE PASSPORT-- */
		static bool uniquePass(int passport);

		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }

};

struct Node //structure for managing each flight's queue
{
    Person person;
    Node* next;
};

class Queue // class that stores passengers on each flight's queue
{

    private:

	int queueNo;
        Node* rear;
        Node* front;

	public:
		/* --CREATE NEW QUEUE-- */
        Queue(int queueId); // queueID is the same as the flight number for each flight

		/* --ADD/REMOVE ELEMENTS-- */
        void enqueue(Person p); // add a new passenger
        void dequeue(); // remove the passenger add last

		/* --ΠΡΟΒΟΛΗ ΣΤΟΙΧΕΙΩΝ ΟΥΡΑΣ-- */
		static void display(int num); //εμφανίζει τους πελάτες, που βρίσκονται κατοχυρωμένοι
									 //στην ουρά αναμονής της εκάστοτε πτήσης

		/* --ΕΠΙΣΤΡΟΦΗ ΑΡΧΑΙΟΤΕΡΟΥ ΧΡΗΣΤΗ-- */
		Person oldest(); //επιστρέφει το αντικέιμενο του αρχαιότερου πελάτη, μέσω της κλάσης Person

		/* --CHECK FOR EMPTY QUEUE-- */
		bool isEmpty(); // returns true if queue is empty

		/* --GETTERS-- */
		int getNo() { return this -> queueNo; }
		Node* getFront() { return this -> front; }
		Node* getRear() { return this -> rear; }

		/* --SETTERS-- */
		void setFront(Node* f) {
			if (f == 0){
				this -> front = NULL;
			}else{
				this -> front = f;
			}
		}
		void setRear(Node* r) {
			this -> rear = r;
		}
};

/* ----FUNCTIONS-CHECKERS FOR THE INPUTS---- */

/* --CHECKERS FOR DIRECT FLIGHTS-- */
bool checkTime(string time) { // check the validity of the time (must be xx:xx, where x = Natural number)

	// enter ONLY if string is NOT empty
	if(!time.empty()){
		for (int i=0; i < time.length(); i++) {
			if (i==2){
				if (time.at(i) != ':') {
				return false;
				}

			}else if ( !(time.at(i) >= '0' && time.at(i) <= '9') ) {
				return false;
			}
		}
		return true;
	}else{
		return false;
	}

}

bool checkNumber(string s){ // checks if the input string consists ONLY of numbers

	// enter if string is NOT empty
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}

		// check if string is a postive number
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}


}

bool checkString(string s){ // checks if string consists only of letters

	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{ //return false
		return false;
	}


}

/* --CHECKER FOR NON-DIRECT FLIGHTS-- */
bool checkTime2(Time tLeaving, Time tArriving){	// checks the validity of arrival and departure time
	if(tLeaving.hour > tArriving.hour){
		return true;
	}else if(tLeaving.hour == tArriving.hour){
		if(tLeaving.min > tArriving.min){
			return true;
		}
	}
	return false;
}


/*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																IMPLEMENTATION
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


/* ----GLOBAL VARS---- */

list<Flight> flist; // store the flights of the system
list<Person> plist; // store the passengers
list<Queue> qlist; // store the customers in the flights' waiting queues

/* ----FUNCTION OF CLASS Queue---- */

Queue::Queue(int queueId){

	this -> queueNo = queueId;
    this -> rear = NULL;
    this -> front = NULL;
}

void Queue::enqueue(Person p){

    Node* temp = new Node;

    temp -> person = p;
    temp -> next = NULL;

    if(this -> front == NULL){
       this -> front = temp;
   }else{
        this -> rear -> next = temp;
    }
    this -> rear = temp;
}

void Queue::dequeue(){

    Node* temp = new Node;

	temp = this -> front;

	this -> front = this -> front -> next;

	delete temp;
}

void Queue::display(int num){


	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i) {
		if(num == i -> queueNo){
			Node* p = new Node;
			p = i -> front;

			if(i -> front == NULL){
				cout<<"\nEmpty queue.\n";
			}else{
				cout << "\nPassengers waiting on queue:" << endl;
				cout << left << setw(15) << "Passport" << left << setw(15) << "Name" << left << setw(15) << "Surame" << endl;
				while(p!=NULL){
					cout << left << setw(15) << p -> person.getPassport() << left << setw(15) << p -> person.getName() << left << setw(15) << p -> person.getSurname() << endl;
					p = p -> next;
				}
			}
		}
	}



}

Person Queue::oldest(){

	return this -> front -> person;
}

bool Queue::isEmpty(){
 if(this -> front == NULL && this -> rear == NULL){
  return true;
 }

 return false;
}


/* ----FUNCTIONS OF CLASS Menu---- */

void Menu::displayMenu(){

	int selection;	// user's menu choice
	string temp; // temp to store user's input

	do{
			cout << "-----------------------------------------------";

			cout << "\n\t AIRLINE RESERVATION SYSTEM \n\n";
			cout << "Please pick an option from the menu below. \n";
			cout << "1. Add new flights \n";
			cout << "2. Delete flights \n";
			cout << "3. Display flight schedule \n";
			cout << "4. Display flight details \n";
			cout << "5. Display passenger personal info \n";
			cout << "6. Book reservation \n";
			cout << "7. Cancel reservation \n";
			cout << "8. Exit \n\n";

			cout << "-----------------------------------------------" << endl;

			cout << "Enter the number of a menu option: ";
			cin >> temp;

			// check validity of input
			while (!checkNumber(temp)) {
				cout << "Please enter a number!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> temp;
			}
			cout << endl;

			selection = atoi(temp.c_str());
			select(selection);

	}while(true);
}

void  Menu::select(int selection){

	Flight f; // FLight's object
	Person p; // class Person's object
	string temp; // temp to store input

	switch(selection){
		case 1:
			f.addFlight();
			break;
		case 2:
			if (!flist.empty()) {
				cout << "Enter the Flight Number you want to delete: "; cin >> temp;
				cout << endl;
				while (!checkNumber(temp)){
					cout << "Flight Number must be a number!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}

				Flight::deleteFlight( atoi(temp.c_str()) );
			}else {
				cout << "There are no flights to delete" << endl;
			}

			break;
		case 3:
			if (!flist.empty()) {
				Flight::displaySchedule();
			}else {
				cout << "There are no scheduled flights!" << endl;
			}
			break;
		case 4:
			if (!flist.empty()) {
				cout << "Please insert flight's number: ";
				cin >> temp; cout << endl;
				while (!checkNumber(temp)){
					cout << "Flight number must be a number!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
				Flight::displayFlightInfo( atoi(temp.c_str()) );
			}else {
				cout << "There are no scheduled flights!" << endl;
			}
			break;
		case 5:
			if (!plist.empty()){
				cout << "Please insert passport number: ";
				cin >> temp;
				while (!Person::displayPersonInfo( atoi(temp.c_str()) )) {
					cout << "Wrong passport number!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
			}else{
				cout << "There are no registered clients at the moment!" << endl;
			}
			break;
		case 6:
			p.book();
			break;
		case 7:
			p.cancel();
			break;
		case 8:
			Menu::exit_prog();
			break;
		default:
			cout << "Invalid selection \n";
	}

}

void Menu::exit_prog(){

	cout << "Thank you for using our system! \n";
	exit(1); // exit
}

/* ----FUNCTIONS OF CLASS Flight---- */

void Flight::addFlight(){

	/* ----INITIALISE VARS----*/
	bool flag = false; // used in loops

	/* --Check for arrival, departure time validity (USED ONLY IN BOARDING & ARRIVING TIME)-- */
	vector<string> fields; // stores, splitted,  user input to be checked
	string temp; // stores user's input temp
	char* pch; // stores result of function strtok()
	int hour; // stores hour
	int min; // store minutes

	cout << "Add new flights by giving the following attributes: \n";

	// clean stream
	cin.clear();
	cin.ignore(256,'\n');

	/* --FLIGHT NUBMER-- */
	cout << "Flight Number: ";
	// get user's input
	getline(cin, temp);

	do{
		flag = true;

		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid Flight Number! " << endl;
			flag = false;
			getline(cin, temp);
		}else if (Flight::flightExists( atoi(temp.c_str()) )) {
			cout << "This Flight already exists!" << endl;
			cout << "Please insert a valid Flight Number!" << endl;
			flag = false;
			getline(cin, temp);
		}else {
			flag = true;
			this -> flightNo = atoi(temp.c_str());
		}
	}while(!flag);

	/* --DEPARTURE-- */
	cout << "Departure: ";
	flag = false;

	// check input
	LOOP:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) ){
			this -> from = temp;
			flag = true;
		}else {
			cout << "Please insert a valid Departure city! ";
			goto LOOP;
		}
	}while(!flag);

	/* --DESTINATION-- */
	cout << "Destination: ";
	flag = false;

	// check input
	LOOP2:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) && (temp.compare(this -> from)) ){
			this -> to = temp;
			flag = true;
		}else{
			cout << "Please insert a valid Destination city! ";
			goto LOOP2;
		}
	}while(!flag);

	/* --DEPARTURE TIME-- */
	cout << "Boarding time (e.g. 19:40): "; //ask from user for the boarding time
	flag = false;

	// check input
	LOOP3:do{
		getline(cin, temp);

		if( temp.length() != 5 || !checkTime(temp) ){
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			goto LOOP3;
		}

		char t_temp[temp.length()];

		strcpy(t_temp, temp.c_str());

		//split string
		pch = strtok(t_temp, ":");

		while(pch != NULL){
			fields.push_back(pch);
			pch = strtok(NULL, ":");
		}

		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());

		// check time
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){
			this -> t_leave.hour = hour;
			this -> t_leave.min = min;
			flag = true;
		}else{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			fields.clear();
		}

	}while(!flag);

	/* --ARRIVAL TIME-- */
	cout << "Arriving time (e.g. 21:40): ";
	flag = false;
	fields.clear();	// clear fields (because it was used before, at "DEPARTURE TIME")

	// check input
	LOOP4:do{
		getline(cin, temp);

		if( temp.length() > 5 || !checkTime(temp) ){
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			goto LOOP4;
		}

		char t_temp[temp.length()];

		strcpy(t_temp, temp.c_str());

		//split string
		pch = strtok(t_temp, ":");

		while(pch != NULL){
			fields.push_back(pch);
			pch = strtok(NULL, ":");
		}

		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());

		// check validity of time
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){
			this -> t_arrive.hour = hour;
			this -> t_arrive.min = min;
			flag = true;
		}else{
			cout << "Please insert a valid arriving time (e.g. 19:40)! ";
			fields.clear();
		}

	}while(!flag);

	/* --TICKET COST-- */
	cout << "Ticket price: ";
	LOOP5:do{

		getline(cin, temp);
		flag = true;

		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid ticket price!" << endl;
			flag = false;
			goto LOOP5;
		}else{
			flag = true;
			this -> cost = atoi(temp.c_str());
		}
	}while(!flag);

	/* --AIRCRAFT TYPE-- */
	cout << "Aeroplane type: ";
	getline(cin, this -> plane_type);
	while(this -> plane_type.empty()){
		cout << "Please insert a valid Aeroplane type!" << endl;
		getline(cin, this -> plane_type);
	}

	/* --No OF SEATS-- */
	cout << "Number of seats: ";
	LOOP6:do{

		getline(cin, temp);
		flag = true;

		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid number of seats!" << endl;
			flag = false;
			goto LOOP6;
		}else{
			flag = true;
			this -> seats = atoi(temp.c_str());
		}
	}while(!flag);

	/* --No of BOOKED SEATS-- */
	cout << "Number of booked seats: ";
	LOOP7:do{

		getline(cin, temp);
		flag = true;

		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid number of booked seats!" << endl;
			flag = false;
			goto LOOP7;
		}else if ( atoi(temp.c_str()) > this -> seats ) {
			cout << "Booked seats must be less than plane's seats!" << endl;
			flag = false;
			goto LOOP7;
		}else {
			flag = true;
			this -> booked_seats = atoi(temp.c_str());
		}
	}while(!flag);
	cout << endl;


	flist.push_back(*this); // add object to the flist

	Queue q(this -> flightNo); // create new queue for the newly added flight
	qlist.push_back(q); // add object to the qlist

	cout << "Flight No: "<< this -> flightNo << " was successfully added!" << endl;

}

void Flight::deleteFlight(int num){

		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( num == i -> getNo() ){

				// enter if waiting queue for the flight is NOT empty
				if (!i -> isEmpty()) {
					// delete object from flist
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2){
						if( num == (i2 -> flightNo) ){
							i2 = flist.erase(i2);
							i = qlist.erase(i);
							cout << "Flight with number: " << num << " was successfully deleted" << endl;
							return;
						}
					}
				}else{
					cout << "There are passengers in the queue of the flight with No: " << num << endl;
					cout << "Remove ALL of them from the queue first!" << endl;
					return;
				}
			}
		}
		cout << "This flight number doesn't exist!" << endl;
		return;
}

void Flight::displayFlightInfo(int num){

	string l_time, a_time; // departure and arrival time
	stringstream convert;
	stringstream convert2;

	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
		if (num == i -> flightNo) {

			convert.str(std::string()); // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"

			convert << i -> t_leave.hour;
			convert2 << i -> t_leave.min;
			l_time = convert.str() + ":" + convert2.str();

			convert.str(std::string()); // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"

			convert << i -> t_arrive.hour;
			convert2 << i -> t_arrive.min;
			a_time = convert.str() + ":" + convert2.str();

			cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;
			cout << left << setw(10) << i -> flightNo << left << setw(10) << i -> from << left << setw(10) << i -> to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i -> cost << left << setw(10) << i -> plane_type << left << setw(10) << i -> seats << left << setw(10) << i -> booked_seats << endl;

			Queue::display(num);
			return;
		}
	}

	cout << "Invalid number of flight was given." << endl;
}

void Flight::displaySchedule(){

	string l_time, a_time; // departure and arrivale time
	stringstream convert;
	stringstream convert2;

		cout << "\n\t\t\t\t FLIGHT SCHEDULE" << endl << endl;
		cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;

		for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
				convert.str(std::string());	// clear stringstream "convert"
				convert2.str(std::string());	// clear stringstream "convert2"

				convert << i -> t_leave.hour;
				convert2 << i -> t_leave.min;
				l_time = convert.str() + ":" + convert2.str();

				convert.str(std::string());	// clear stringstream "convert"
				convert2.str(std::string());	// clear stringstream "convert2"

				convert << i -> t_arrive.hour;
				convert2 << i -> t_arrive.min;
				a_time = convert.str() + ":" + convert2.str();

				cout << left << setw(10) << i -> flightNo << left << setw(10) << i -> from << left << setw(10) << i -> to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i -> cost << left << setw(10) << i -> plane_type << left << setw(10) << i -> seats << left << setw(10) << i -> booked_seats << endl;
		}

		cout << endl;
}

void Flight::resSeat(int num, int val){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		if( num == (i -> flightNo) ){
			i -> booked_seats += val ;
			break;
		}
	}
}

bool Flight::flightExists(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		if (num == i -> flightNo){
			return true;
		}
	}
	return false;
}

bool Flight::checkForSeats(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		if( num == (i -> flightNo) ){
				if( i -> seats == i -> booked_seats )
					return false;
				else
					return true;
		}
	}
}

/* ----FUNCTIONS OF CLASS Person---- */

void Person::book(){

	/* ----INITIALISE VARS----*/
	/* --FLIGHTS-- */
	string temp; //temp to store user's input, to be checked
	int num; // stores flight's number, after successful check

	/* --VARS FOR NON DIRECT FLIGHTS-- */
	int counter = 1; // stores the amount(>=2) of the non-direct flights
	string choice; // stores user's choice for adding or not more flights to their reservation
	Time tArriving;
	Time tLeaving;
	string Departure;
	string Destination;
	list<int> nums; // store flights' numbers
	list<int>::iterator i1 = nums.begin(); //iterator for accessing List nums

	/* --VAR FOR LOOPS-- */
	bool flag = true;

	// clean stream
	cin.clear();
	cin.ignore(256,'\n');

	if (!flist.empty()) {
		cout << "Insert y (yes) for a new client or n (no) for an existing client. ";
		getline(cin, choice);

		// enter if client is new
		if (choice == "y" || choice == "Y") {

			cout << "Please give us your personal info. " << endl;

			/* --NAME-- */
			cout << "Name: ";
			flag = false;

			// check input
			LOOP8:do{
				getline(cin, this -> name);
				if ( (this -> name.length() <= 10) && (checkString(this -> name)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Name! ";
					goto LOOP8;
				}
			}while(!flag);

			/* --SURNAME-- */
			cout << "Surname: ";
			flag = false;

			// check input
			LOOP9:do{
				getline(cin, this -> surname);
				if ( (this -> surname.length() <= 10) && (checkString(this -> surname)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Surname! ";
					goto LOOP9;
				}
			}while(!flag);

			/* --PASPPORT No-- */
			cout << "Passport number: ";

			// check input
			LOOP10:do{

				getline(cin, temp);
				flag = true;

				if (!checkNumber(temp)){
					cout << "Please insert a valid passport number" << endl;
					flag = false;
					goto LOOP10;
				}else if (!Person::uniquePass( atoi(temp.c_str()) )) {
					cout << "Please check the validity of your passport number" << endl;
					flag = false;
					goto LOOP10;
				}else{
					flag = true;
					this -> passportNo = atoi(temp.c_str());
				}
			}while(!flag);

			/* --NATIONALLITY-- */
			cout << "Nationallity: ";
			flag = false;

			// check input
			LOOP11:do{

				getline(cin, this -> nationallity);

				if ( (this -> nationallity.length() <= 10) && (checkString(this -> nationallity)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Nationallity! ";
					goto LOOP11;
				}
			}while(!flag);

			/* --ADDRESS-- */
			cout << "Address: ";
			getline(cin, this -> address);

			/* --TEL-- */
			cout << "Telephone: ";
			getline(cin, temp);

			// check input
			while (!checkNumber(temp)) {
				cout << "Please insert a valid telephone number!" << endl;
				getline(cin, temp);
			}
			this -> tel = atoi(temp.c_str());
		}else { // existing customer
			cout << "Pleas give us your passport No: ";
			getline(cin, temp);

			// check input
			while(!checkNumber(temp)){
				cout << "Please insert a valid passport number!" << endl;
				flag = false;
				getline(cin, temp);
			}

			// check if passport No is unique
			if ( !(Person::uniquePass( atoi(temp.c_str()) ))) {
					for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
						if (atoi(temp.c_str()) == i -> passportNo) {
							this -> name = i -> name;
							this -> surname = i -> surname;
							this -> passportNo = i -> passportNo;
							this -> nationallity = i -> nationallity;
							this -> address = i -> address;
							this -> tel = i -> tel;

							for (std::list<int>::iterator i2 = i->flights.begin(); i2 != i->flights.end(); ++i2) {
								this -> flights.push_back(*i2);
							}

							// after copying the customers info,
							// delete the old object pointing to them
							i = plist.erase(i);
							break;
						}
					}
			}else {
				cout << "Wrong passport number!" << endl;
				return;
			}
		}


		// display flights
		Flight::displaySchedule();

		/* --FLIGTH No-- */
		cout << "\n\nEnter the number of the flight you 're intrested in: ";
		getline(cin, temp);
		flag = true;

		// check input
		while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
			cout << "Please insert a valid Flight No!" << endl;
			getline(cin, temp);
		}
		num = atoi(temp.c_str());

		/*
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
							BOOK CUSTOMER'S CHOSEN FLIGHT(S)
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/

		//DIRECT FLIGHT
		if(Flight::checkForSeats(num)){ // check for vacancy
			this -> flights.push_back(num);
			Flight::resSeat(num,1);
			cout << "Your flight with No: " << num << " was successfully booked." << endl;

		// NONO-DIRECT FLIGHT
		}else{
			choice = "y";

			cout << "There are no available direct flights for this destination." << endl;
			cout << "Please enter the special numbers for the alternative flights.";

			while(choice == "y" || choice == "Y"){ // exit if user doesn't want to add more flights

		  LOOP12:cout << "\nNumber #" << counter << " : ";
				getline(cin, temp);

				// check input
				while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
					cout << "Please insert a valid Flight No!" << endl;
					cin >> temp;
				}

				num = atoi(temp.c_str());

				if (counter > 1){ // enter if user has entered 2 or more flights

					// store the arrival, departure time and the departure, arriving city
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2) {
						if (*i1 == i2 -> getFlightNo()) {
							tArriving = i2 -> getArrivingTime();
							Destination = i2 -> getDestination();
						}else if (num == i2 -> getFlightNo()) {
							tLeaving = i2 -> getLeavingTime();
							Departure = i2 -> getDeparture();
						}
					}

					// check validity of each flight
					if ( !(checkTime2(tLeaving,tArriving) && !Departure.compare(Destination)) ) {
						cout << "Please enter a flight to a valid Destination!" << endl;
						goto LOOP12;
					}
				}

				nums.push_back(num); // add the flight's number
				i1++;

				if(counter >= 2){
					cout << "Do you want to add more flight numbers?(y/n) ";
					getline(cin, choice);
				}

				counter++;
			}


			// check for vacancies in the chosen flights
			// and add all of the flight's numbers to the specific node of the list flights
			for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
				flag = Flight::checkForSeats(*i) and flag;
				this -> flights.push_back(*i);
			}

			//enter ONLY if there are vacant seats and reserve a seat to each chosen flight
			if(flag){
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
					Flight::resSeat(*i,1);
				}
				cout << "Your flights were successfully booked." << endl;

			// if, at least, one flight is fully booked add the customer to the queues of each flight
			}else{
				cout << endl;
				cout << "Some of the flights you inserted were over booked." << endl;

				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
					for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2){
						if( *i == i2 -> getNo()){
							i2 -> enqueue(*this);
						}
					}
				}
				cout << "We have added you in queues for each of these flights." << endl;
			}
		}
		plist.push_back(*this); // add object to plist
	}else{
		cout << "There are no available flights at the moment." << endl;
		return;
	}
}

void Person::bookFromQueue(int num){  //is called only from cancel()

	bool flag = true;
	Person queueFront; // object of the customer added last

	// find the oldest customer
	for (std::list<Queue>::iterator it = qlist.begin(); it != qlist.end(); ++it){
		if (num == it -> getNo() ){
			if( !(it -> isEmpty()) ){
				queueFront = it -> oldest();
				break;
			}else{
				return;
			}
		}
	}

	// check if all of the customer's chosen flights have vacant seats
	for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
		flag = Flight::checkForSeats(*i) and flag;
	}

	// enter ONLY if there are vacancies in ALL of the customer's chosen flights
	// and book them
	if(flag){
		Node* p = new Node;

		// find the flights of the oldest customer
		for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){

			// delete him from the queues
			for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2) {
				if(*i == i2 -> getNo()){
					p = i2 -> getFront();
					while(p != NULL){
						if(queueFront.passportNo == p -> person.passportNo){
							i2 -> dequeue();
							Flight::resSeat(*i,1);
						}
						p = p -> next;
					}
				}
			}

		}
	}
}

void Person::cancel(){

	string passport, num;
	int counter = 1; //counter that stores user's wrong inputs
	bool flightFound = false; // is false if customer has already booked a seat in a flight
	bool isInQueue = false; //is false if the customer, that will be deleted, doesn't belong in
				// the queue of each flight

	if (!plist.empty()) {
		// clean stream
		cin.clear();
		cin.ignore(256,'\n');

		cout << "Please give us your passport number: ";
		getline(cin, passport); cout << endl;

		// check input
		while(!checkNumber(passport)){
			cout << "Please insert a valid passport number!" << endl;
			getline(cin, passport); cout << endl;
		}

		while(!Person::displayPersonInfo( atoi(passport.c_str()) )) {

			//έξοδος από το πρόγραμμα αν δοθεί λανθασμένος αριθμός διαβατηρίου 5 φορές
			if (counter == 5) {
				cout << "Wrong passporst number was given too many times.";
				return;
			}else{
				cout << "Please check your Passport Number." << endl;
				getline(cin, passport); cout << endl;

				//έλεγχος αν ο αριθμός διαβατηρίου αποτελείται μόνο από ψηφία
				while(!checkNumber(passport)){
					cout << "Please insert a valid passport number!" << endl;
					getline(cin, passport); cout << endl;
				}
			}
			counter++;
		}

		cout << "\nWhich flight do you want to cancel (enter the flight number)? ";
		getline(cin, num);
		counter = 1;

		// check input
		while(!checkNumber(num)){
			cout << "Please insert a valid flight number!" << endl;
			getline(cin, num); cout << endl;
		}

		// iterate through the passenger's flights
		for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
			if (atoi(passport.c_str()) == i -> passportNo) {

				// check input and exit if counter = 5
				do{
					for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
						if (atoi(num.c_str()) == *i2) {
							flightFound = true;
							i2 = flights.erase(i2); // delete flight from passenger's info
							break;
						}
					}

					if (counter == 5){
						cout << "Wrong flight number was given too many times.";
						return;
					}else if(!flightFound){
						cout << "Please check your flight number!.";
						getline(cin, num); cout << endl;

						// check input
						while(!checkNumber(num)){
						cout << "Please insert a valid flight number!" << endl;
						getline(cin, num); cout << endl;
						}
					}
					counter++;
				}while(!flightFound);
				break;
			}
		}

		// delete client from the queue of the flight, if they are a part of it
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( atoi(num.c_str()) == i -> getNo() ){
				if(!i -> isEmpty()){
					Node* p = new Node;
					Node* previousNode;
					p = i -> getFront();

					while(p!=NULL){
						if (atoi(passport.c_str()) == p -> person.passportNo){
							isInQueue = true;

							// enter if the client is on the first position
							if (p == i -> getFront()){
								i -> setFront(p -> next);
								// enter if queue has only one element
								if (i -> getFront() == i -> getRear()){
									i -> setRear(NULL);
								}
							}else if(p == i -> getRear()){ // enter if client is in the last poitsion of the queue
								previousNode -> next = NULL;
							}else{
								previousNode -> next = p -> next;
							}
							delete(p);
							break;
						}
						previousNode = p;
						p = p -> next;
					}
				}
			}
		}

		//enter if passenger is NOT part of the current queue
		if (!isInQueue){
			Flight::resSeat(atoi(num.c_str()), -1);

			this -> bookFromQueue(atoi(num.c_str()));
		}
		cout << "\nYour reservation was successfully removed! \n" << endl;
	}else {
		cout << "There are no registered clients at the moment!" << endl;
	}
}

bool Person::displayPersonInfo(int passport){

	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){

		if(passport == i -> passportNo){

			cout << "\n\t\t\t\t PERSONAL INFO" << endl << endl;
			cout << left << setw(15) << "NAME" << left << setw(15) << "SURNAME" << left << setw(15) << "PASSPORT_No" << left << setw(15) << "NATIONALLITY" << left << setw(15) << "ADDRESS" << left << setw(15) << "TELEPHONE" << endl;

			cout << left << setw(15) << i -> name << left << setw(15) << i -> surname << left << setw(15) << i -> passportNo << left << setw(15) << i -> nationallity << left << setw(15) << i -> address << left << setw(15) << i -> tel << endl << endl;
			cout << "Your flight(s): ";

			for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){

				cout << *i2 << "  ";
			}
			cout << endl;
			return true;
		}
	}
	cout << "Passport number was not found. Check again!" << endl;
	return false;
}

bool Person::uniquePass(int passport){
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		if (passport == i -> getPassport()) {
			return false;
		}
	}
	return true;
}

void flightBookingSystem(){

	Menu::displayMenu();
}
// Structure for linked list node to store passenger details
struct node {
    int ticketID;
    string Name, Age, AAD, Contact, BookedClass, BookedTName, BookedTID, BookedDest, BookedSource, BookedDate, DeptTime, ArrTime, BookedSeatNum;
    float Price;
    node* next;
};

// Structure to store train details
struct trains
{
    string TName, TID, TDest, TSource, TDate, arriveTime, departTime, TClasses, TDistance;
    int TSeats;
};

// Structure to record seat availability
struct SeatRecord {
    string RowA;
    string RowB;
    string RowC;
};

node* head = NULL;
node* tail = NULL;

// Function declaration for admin operations
void admin();
// Function declaration for main menu
int main();

// Global variables for passenger booking details
string Name, Age, AAD, Contact, Dest, Source, SeatNum, Class, TID, Date, ATime, DTime, TName;
bool trainCheck = false;
float Price;
string BookedID;
int currentID;
trains availTrains[100];  // Array to store available trains
int noOfTrains = 100;     // Number of available trains

// Function for handling payment process
void Payment()
{
    string cc, cvv, dob, payChoice;
    string accNum, accHolderFName, accHolderLName;
    cout << endl << endl;
    cout << "\n\n\t\t\t\t\t===============PAYMENT DETAILS===============" << endl;
    cout << "\t\t\t\t\tChoose Payment Method. \n";
    cout << "\t\t\t\t\t1. GPay. \n";
    cout << "\t\t\t\t\t2. PhonePe. \n";
    cout << "\t\t\t\t\t3. Credit/Debit Card. \n";
    cout << "\n\n\t\t\t\t\tEnter Choice (1-3): ";
    cin >> payChoice;
    if (payChoice == "1")
    {
        phoneCheck:
        cout << "\n\n\t\t\t\t\tEnter GPay Mobile Account Number: ";
        cin >> accNum;
        if (accNum.length() != 10 || accNum.length() > 10)
        {
            cout << endl;
            cout << "\n\n\t\t\t\t\tEnter a Valid 10 Digit Mobile Phone Number!" << endl << endl;
            goto phoneCheck;
        }
        cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }
    else if (payChoice == "2")
    {
        cout << "\n\n\t\t\t\t\tEnter PhonePe Mobile Account Number: ";
        cin >> accNum;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }
    else if (payChoice == "3")
    {
    check:
        cout << "\n\n\t\t\t\t\tEnter Credit/Debit Card Number (16 digits): ";
        cin >> cc;
        if (cc.length() != 16)
        {
            cout << "\n\n\t\t\t\t\tCC number must have a length of 16 only! \n";
            goto check;
        }
        else
            check2:
        cout << "\n\n\t\t\t\t\tEnter CVV (3 digits): ";
        for (int i = 0; i > -1; i++)
        {
            char temp;
            temp = _getch();
            if (temp != 13 && temp != 8)
            {
                _putch('*');
            }
            if (temp == 13)
            {
                break;
            }
            if (temp == 8 || temp == 127 && !cvv.empty())
            {
                cout << "\b \b";
                cvv.erase(cvv.size() - 1);
            }
            else
                cvv += temp;
        }
        if (cvv.length() != 3)
        {
            cout << "\n\n\t\t\t\t\tCVV number must have a length of 3 only! \n";
            cvv = "";
            goto check2;
        }
        else
        {
            cout << "\n\n\t\t\t\t\tEnter Date Of Expiry(DD/MM/YYYY): ";
            cin >> dob;
        }
    }
    else
    {
        cout << "\t\t\t\t\tInvalid Choice. Please try again. \n";
    }
    cout << "\n\n\t\t\t\t\t";
}

// Function to sort trains based on distance and then name
void trainSort() {
    string temp, temp2, temp3, temp4, temp5, temp6, temp7, temp9, temp10;
    int temp8, j;

    for (int i = 0; i < noOfTrains; i++) {
        temp = availTrains[i].arriveTime;
        temp2 = availTrains[i].departTime;
        temp3 = availTrains[i].TClasses;
        temp4 = availTrains[i].TDate;
        temp5 = availTrains[i].TDest;
        temp6 = availTrains[i].TID;
        temp7 = availTrains[i].TName;
        temp8 = availTrains[i].TSeats;
        temp9 = availTrains[i].TSource;
        temp10 = availTrains[i].TDistance; // Distance between source and destination

        j = i - 1;

        // Modify the condition to prioritize distance, then by name
        while (j >= 0 && (availTrains[j].TDistance > temp10 ||
                (availTrains[j].TDistance == temp10 && availTrains[j].TName > temp7))) {

            availTrains[j + 1].arriveTime = availTrains[j].arriveTime;
            availTrains[j + 1].departTime = availTrains[j].departTime;
            availTrains[j + 1].TClasses = availTrains[j].TClasses;
            availTrains[j + 1].TDate = availTrains[j].TDate;
            availTrains[j + 1].TDest = availTrains[j].TDest;
            availTrains[j + 1].TID = availTrains[j].TID;
            availTrains[j + 1].TName = availTrains[j].TName;
            availTrains[j + 1].TSeats = availTrains[j].TSeats;
            availTrains[j + 1].TSource = availTrains[j].TSource;
            availTrains[j + 1].TDistance = availTrains[j].TDistance;

            j--;
        }

        availTrains[j + 1].arriveTime = temp;
        availTrains[j + 1].departTime = temp2;
        availTrains[j + 1].TClasses = temp3;
        availTrains[j + 1].TDate = temp4;
        availTrains[j + 1].TDest = temp5;
        availTrains[j + 1].TID = temp6;
        availTrains[j + 1].TName = temp7;
        availTrains[j + 1].TSeats = temp8;
        availTrains[j + 1].TSource = temp9;
        availTrains[j + 1].TDistance = temp10;
    }
}

// Function to choose a seat
string SeatChoose()
{
    fstream Seat;
    int count = 0, delimit = 0;
    string line;
    SeatRecord Seats[10];
    Seat.open("Seat_Details.txt");

    // Count the number of lines in the file
    while (getline(Seat, line))
    {
        count++;
    }
    Seat.close();

    Seat.open("Seat_Details.txt");

    // Read each line and split into rows A, B, and C
    for (int j = 0; j < count; j++)
    {
        string line1;
        getline(Seat, line1);

        // Split Row A
        for (int i = 0; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowA += temp;
        }

        // Split Row B
        for (int i = delimit + 1; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowB += temp;
        }

        // Split Row C
        for (int i = delimit + 1; i > -1; i++)
        {
            char temp;
            temp = line1[i];
            if (temp == '-')
            {
                delimit = i;
                break;
            }
            Seats[j].RowC += temp;
        }
    }
    Seat.close();

    string RowName, SeatNum, FinalSeatNum;
    bool Flag = false;

    // Display available seats
    cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << " B" << "\t" << " C" << "\t\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "\n\n\t\t\t\t\t\t\t" << Seats[i].RowA << "\t" << Seats[i].RowB << "\t" << Seats[i].RowC << "\t\n";
    }

    cout << "\n\n\t\t\t\t\t\t  ======================================\n";

    // User selects row
    for (int x = 0; x > -1; x++)
    {
        cout << "\n\n\t\t\t\t\tEnter the row name that you chose: ";
        cin >> RowName;
        if (RowName != "A" && RowName != "B" && RowName != "C")
        {
            cout << "\n\n\t\t\t\t\tInvalid row, please try again. ";
        }
        else
            break;
    }

    // User selects seat number
    for (int x = 0; x > -1; x++)
    {
        check7:
        cout << "\n\n\t\t\t\t\tEnter the seat number that you chose: ";
        cin >> SeatNum;
        if (SeatNum == "XX")
        {
            cout << "\n\n\t\t\t\t\tInvalid seat, please try again! \n";
            goto check7;
        }
        for (int i = 0; i < 10; i++)
        {
            if (RowName == "A")
            {
                if (SeatNum == Seats[i].RowA)
                {
                    Seats[i].RowA = "XX";  // Mark seat as occupied
                    Flag = true;
                    break;
                }
            }
            else if (RowName == "B")
            {
                if (SeatNum == Seats[i].RowB)
                {
                    Seats[i].RowB = "XX";  // Mark seat as occupied
                    Flag = true;
                    break;
                }
            }
            else if (RowName == "C")
            {
                if (SeatNum == Seats[i].RowC)
                {
                    Seats[i].RowC = "XX";  // Mark seat as occupied
                    Flag = true;
                    break;
                }
            }
        }

        if (Flag == false)
        {
            cout << "\n\n\t\t\t\t\tSeat number not found, please try again. \n";
        }
        else
            break;
    }

    FinalSeatNum = RowName + SeatNum;

    // Overwrite the Seat_Details.txt file with updated seat records
    ofstream Del;
    Del.open("Seat_Details.txt", ios::trunc);
    Del.close();
    Del.open("Seat_Details.txt", ios::trunc);
    for (int i = 0; i < 10; i++)
    {
        Del << Seats[i].RowA << "-" << Seats[i].RowB << "-" << Seats[i].RowC << "-\n";
    }
    Del.close();

    return FinalSeatNum;  // Return the selected seat number
}

void iniTrain()
{
availTrains[0].TName = "ANDHRA ARUNACHAL Express";
availTrains[0].TID = "AA01";
availTrains[0].TSource = "ANDHRA_PRADESH";
availTrains[0].TDest = "ARUNACHAL_PRADESH";
availTrains[0].TDate = "01-FEB-2025";
availTrains[0].arriveTime = "18:00 (6:00 PM)";
availTrains[0].departTime = "10:00 (10:00 AM)";
availTrains[0].TDistance = "2850 KM";
availTrains[0].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[0].TSeats = 30;

availTrains[1].TName = "ASSAM BIHAR Express";
availTrains[1].TID = "AB02";
availTrains[1].TSource = "ASSAM";
availTrains[1].TDest = "BIHAR";
availTrains[1].TDate = "02-FEB-2025";
availTrains[1].arriveTime = "20:30 (8:30 PM)";
availTrains[1].departTime = "08:15 (8:15 AM)";
availTrains[1].TDistance = "1100 KM";
availTrains[1].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[1].TSeats = 30;

availTrains[2].TName = "CHHATTISGARH GOA Express";
availTrains[2].TID = "CG03";
availTrains[2].TSource = "CHHATTISGARH";
availTrains[2].TDest = "GOA";
availTrains[2].TDate = "03-FEB-2025";
availTrains[2].arriveTime = "22:45 (10:45 PM)";
availTrains[2].departTime = "13:20 (1:20 PM)";
availTrains[2].TDistance = "1400 KM";
availTrains[2].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[2].TSeats = 30;

availTrains[3].TName = "GUJARAT HARYANA Express";
availTrains[3].TID = "GH04";
availTrains[3].TSource = "GUJARAT";
availTrains[3].TDest = "HARYANA";
availTrains[3].TDate = "04-FEB-2025";
availTrains[3].arriveTime = "19:50 (7:50 PM)";
availTrains[3].departTime = "09:30 (9:30 AM)";
availTrains[3].TDistance = "1800 KM";
availTrains[3].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[3].TSeats = 30;

availTrains[4].TName = "HIMACHAL JHARKHAND Express";
availTrains[4].TID = "HJ05";
availTrains[4].TSource = "HIMACHAL_PRADESH";
availTrains[4].TDest = "JHARKHAND";
availTrains[4].TDate = "05-FEB-2025";
availTrains[4].arriveTime = "21:00 (9:00 PM)";
availTrains[4].departTime = "11:10 (11:10 AM)";
availTrains[4].TDistance = "1400 KM";
availTrains[4].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[4].TSeats = 30;

availTrains[5].TName = "KARNATAKA KERALA Express";
availTrains[5].TID = "KK06";
availTrains[5].TSource = "KARNATAKA";
availTrains[5].TDest = "KERALA";
availTrains[5].TDate = "06-FEB-2025";
availTrains[5].arriveTime = "17:15 (5:15 PM)";
availTrains[5].departTime = "08:00 (8:00 AM)";
availTrains[5].TDistance = "650 KM";
availTrains[5].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[5].TSeats = 30;

availTrains[6].TName = "MADHYA MAHARASHTRA Express";
availTrains[6].TID = "MM07";
availTrains[6].TSource = "MADHYA_PRADESH";
availTrains[6].TDest = "MAHARASHTRA";
availTrains[6].TDate = "07-FEB-2025";
availTrains[6].arriveTime = "16:30 (4:30 PM)";
availTrains[6].departTime = "06:30 (6:30 AM)";
availTrains[6].TDistance = "1200 KM";
availTrains[6].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[6].TSeats = 30;

availTrains[7].TName = "MANIPUR MEGHALAYA Express";
availTrains[7].TID = "MM08";
availTrains[7].TSource = "MANIPUR";
availTrains[7].TDest = "MEGHALAYA";
availTrains[7].TDate = "08-FEB-2025";
availTrains[7].arriveTime = "15:10 (3:10 PM)";
availTrains[7].departTime = "06:00 (6:00 AM)";
availTrains[7].TDistance = "500 KM";
availTrains[7].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[7].TSeats = 30;

availTrains[8].TName = "MIZORAM NAGALAND Express";
availTrains[8].TID = "MN09";
availTrains[8].TSource = "MIZORAM";
availTrains[8].TDest = "NAGALAND";
availTrains[8].TDate = "09-FEB-2025";
availTrains[8].arriveTime = "19:20 (7:20 PM)";
availTrains[8].departTime = "08:40 (8:40 AM)";
availTrains[8].TDistance = "750 KM";
availTrains[8].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[8].TSeats = 30;

availTrains[9].TName = "ODISHA PUNJAB Express";
availTrains[9].TID = "OP10";
availTrains[9].TSource = "ODISHA";
availTrains[9].TDest = "PUNJAB";
availTrains[9].TDate = "10-FEB-2025";
availTrains[9].arriveTime = "22:00 (10:00 PM)";
availTrains[9].departTime = "09:30 (9:30 AM)";
availTrains[9].TDistance = "1900 KM";
availTrains[9].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[9].TSeats = 30;

availTrains[10].TName = "RAJASTHAN SIKKIM Express";
availTrains[10].TID = "RS11";
availTrains[10].TSource = "RAJASTHAN";
availTrains[10].TDest = "SIKKIM";
availTrains[10].TDate = "11-FEB-2025";
availTrains[10].arriveTime = "21:45 (9:45 PM)";
availTrains[10].departTime = "08:20 (8:20 AM)";
availTrains[10].TDistance = "2200 KM";
availTrains[10].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[10].TSeats = 30;

availTrains[11].TName = "TAMIL TELANGANA Express";
availTrains[11].TID = "TT12";
availTrains[11].TSource = "TAMIL NADU";
availTrains[11].TDest = "TELANGANA";
availTrains[11].TDate = "12-FEB-2025";
availTrains[11].arriveTime = "19:00 (7:00 PM)";
availTrains[11].departTime = "09:00 (9:00 AM)";
availTrains[11].TDistance = "850 KM";
availTrains[11].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[11].TSeats = 30;

availTrains[12].TName = "TRIPURA UTTAR PRADESH Express";
availTrains[12].TID = "TU13";
availTrains[12].TSource = "TRIPURA";
availTrains[12].TDest = "UTTAR PRADESH";
availTrains[12].TDate = "13-FEB-2025";
availTrains[12].arriveTime = "20:30 (8:30 PM)";
availTrains[12].departTime = "07:00 (7:00 AM)";
availTrains[12].TDistance = "2700 KM";
availTrains[12].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[12].TSeats = 30;

availTrains[13].TName = "UTTARAKHAND WEST BENGAL Express";
availTrains[13].TID = "UW14";
availTrains[13].TSource = "UTTARAKHAND";
availTrains[13].TDest = "WEST BENGAL";
availTrains[13].TDate = "14-FEB-2025";
availTrains[13].arriveTime = "22:15 (10:15 PM)";
availTrains[13].departTime = "08:45 (8:45 AM)";
availTrains[13].TDistance = "1650 KM";
availTrains[13].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[13].TSeats = 30;

availTrains[14].TName = "DELHI J&K Express";
availTrains[14].TID = "DJ15";
availTrains[14].TSource = "DELHI";
availTrains[14].TDest = "JAMMU_KASHMIR";
availTrains[14].TDate = "15-FEB-2025";
availTrains[14].arriveTime = "18:45 (6:45 PM)";
availTrains[14].departTime = "08:30 (8:30 AM)";
availTrains[14].TDistance = "580 KM";
availTrains[14].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[14].TSeats = 30;

availTrains[15].TName = "LADAKH NAGALAND Express";
availTrains[15].TID = "LN16";
availTrains[15].TSource = "LADAKH";
availTrains[15].TDest = "NAGALAND";
availTrains[15].TDate = "16-FEB-2025";
availTrains[15].arriveTime = "21:30 (9:30 PM)";
availTrains[15].departTime = "10:00 (10:00 AM)";
availTrains[15].TDistance = "3100 KM";
availTrains[15].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[15].TSeats = 30;

availTrains[16].TName = "UTS NORTHEAST Express";
availTrains[16].TID = "UN17";
availTrains[16].TSource = "UNION_TERRITORIES";
availTrains[16].TDest = "NORTHEAST";
availTrains[16].TDate = "17-FEB-2025";
availTrains[16].arriveTime = "23:45 (11:45 PM)";
availTrains[16].departTime = "12:00 (12:00 PM)";
availTrains[16].TDistance = "2800 KM";
availTrains[16].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[16].TSeats = 30;

availTrains[17].TName = "ANDHRA MEGHALAYA Express";
availTrains[17].TID = "AM18";
availTrains[17].TSource = "ANDHRA_PRADESH";
availTrains[17].TDest = "MEGHALAYA";
availTrains[17].TDate = "18-FEB-2025";
availTrains[17].arriveTime = "22:30 (10:30 PM)";
availTrains[17].departTime = "08:15 (8:15 AM)";
availTrains[17].TDistance = "2500 KM";
availTrains[17].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[17].TSeats = 30;

availTrains[18].TName = "GUJARAT MANIPUR Express";
availTrains[18].TID = "GM19";
availTrains[18].TSource = "GUJARAT";
availTrains[18].TDest = "MANIPUR";
availTrains[18].TDate = "19-FEB-2025";
availTrains[18].arriveTime = "21:15 (9:15 PM)";
availTrains[18].departTime = "09:00 (9:00 AM)";
availTrains[18].TDistance = "2700 KM";
availTrains[18].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[18].TSeats = 30;

availTrains[19].TName = "KERALA MIZORAM Express";
availTrains[19].TID = "KM20";
availTrains[19].TSource = "KERALA";
availTrains[19].TDest = "MIZORAM";
availTrains[19].TDate = "20-FEB-2025";
availTrains[19].arriveTime = "20:00 (8:00 PM)";
availTrains[19].departTime = "06:45 (6:45 AM)";
availTrains[19].TDistance = "2950 KM";
availTrains[19].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[19].TSeats = 30;

availTrains[20].TName = "GOA CHHATTISGARH Express";
availTrains[20].TID = "GC21";
availTrains[20].TSource = "GOA";
availTrains[20].TDest = "CHHATTISGARH";
availTrains[20].TDate = "21-FEB-2025";
availTrains[20].arriveTime = "19:30 (7:30 PM)";
availTrains[20].departTime = "07:00 (7:00 AM)";
availTrains[20].TDistance = "1200 KM";
availTrains[20].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[20].TSeats = 30;

availTrains[21].TName = "HARYANA ARUNACHAL Express";
availTrains[21].TID = "HA22";
availTrains[21].TSource = "HARYANA";
availTrains[21].TDest = "ARUNACHAL_PRADESH";
availTrains[21].TDate = "22-FEB-2025";
availTrains[21].arriveTime = "23:45 (11:45 PM)";
availTrains[21].departTime = "11:00 (11:00 AM)";
availTrains[21].TDistance = "3200 KM";
availTrains[21].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[21].TSeats = 30;

availTrains[22].TName = "BIHAR ASSAM Express";
availTrains[22].TID = "BA23";
availTrains[22].TSource = "BIHAR";
availTrains[22].TDest = "ASSAM";
availTrains[22].TDate = "23-FEB-2025";
availTrains[22].arriveTime = "20:15 (8:15 PM)";
availTrains[22].departTime = "08:00 (8:00 AM)";
availTrains[22].TDistance = "1100 KM";
availTrains[22].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[22].TSeats = 30;

availTrains[23].TName = "UTTAR PRADESH ANDAMAN Express";
availTrains[23].TID = "UA24";
availTrains[23].TSource = "UTTAR_PRADESH";
availTrains[23].TDest = "ANDAMAN_NICOBAR";
availTrains[23].TDate = "24-FEB-2025";
availTrains[23].arriveTime = "22:30 (10:30 PM)";
availTrains[23].departTime = "11:00 (11:00 AM)";
availTrains[23].TDistance = "1600 KM";
availTrains[23].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[23].TSeats = 30;

availTrains[24].TName = "PUDUCHERRY JHARKHAND Express";
availTrains[24].TID = "PJ25";
availTrains[24].TSource = "PUDUCHERRY";
availTrains[24].TDest = "JHARKHAND";
availTrains[24].TDate = "25-FEB-2025";
availTrains[24].arriveTime = "19:00 (7:00 PM)";
availTrains[24].departTime = "06:30 (6:30 AM)";
availTrains[24].TDistance = "1850 KM";
availTrains[24].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[24].TSeats = 30;

availTrains[25].TName = "LAKSHADWEEP HIMACHAL Express";
availTrains[25].TID = "LH26";
availTrains[25].TSource = "LAKSHADWEEP";
availTrains[25].TDest = "HIMACHAL_PRADESH";
availTrains[25].TDate = "26-FEB-2025";
availTrains[25].arriveTime = "22:45 (10:45 PM)";
availTrains[25].departTime = "10:00 (10:00 AM)";
availTrains[25].TDistance = "2800 KM";
availTrains[25].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[25].TSeats = 30;

availTrains[26].TName = "DADRA MAHARASHTRA Express";
availTrains[26].TID = "DM27";
availTrains[26].TSource = "DADRA_&_NAGAR_HAVELI_AND_DAMAN_&_DIU";
availTrains[26].TDest = "MAHARASHTRA";
availTrains[26].TDate = "27-FEB-2025";
availTrains[26].arriveTime = "21:00 (9:00 PM)";
availTrains[26].departTime = "08:00 (8:00 AM)";
availTrains[26].TDistance = "350 KM";
availTrains[26].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[26].TSeats = 30;

availTrains[27].TName = "NCTCHANDIGARH Express";
availTrains[27].TID = "NC28";
availTrains[27].TSource = "DELHI_(NCT)";
availTrains[27].TDest = "CHANDIGARH";
availTrains[27].TDate = "28-FEB-2025";
availTrains[27].arriveTime = "18:15 (6:15 PM)";
availTrains[27].departTime = "08:30 (8:30 AM)";
availTrains[27].TDistance = "240 KM";
availTrains[27].TClasses = "GENERAL, SLEEPER, 3AC, 2AC, 1AC, 2S,CC";
availTrains[27].TSeats = 30;


}

// Function to fill train details and book seats
string trainFill()
{
    bool check = false;    // Flag to check if a train exists for the route
    bool check2 = false;   // Flag to check if the train ID entered exists
    trainCheck = true;     // Flag to confirm train availability

    flag:
    // Prompt user to enter departure and arrival cities
    cout << "\t\t\t\t\tEnter Your Departure City: ";
    cin >> Dest;           // Departure city
    cin.ignore();          // Clear the buffer
    cout << "\t\t\t\t\tEnter Your Arrival City: ";
    cin >> Source;         // Arrival city
    cin.ignore();          // Clear the buffer

    trainSort();           // Sort trains based on the route

    cout << "\n\n\t\t\t\t\tAVAILABLE TRAINS ON THAT DAY IN THIS ROUTE ARE AS FOLLOWS (IF ANY): \n\n" << endl;

    // Iterate through available trains and display matching trains
    for (int i = 0; i < noOfTrains; i++)
    {
        if (availTrains[i].TSource == Dest && availTrains[i].TDest == Source)
        {
            cout << "\t\t\t\t\tTrain Name: " << availTrains[i].TName << endl;
            cout << "\t\t\t\t\tTrain ID: " << availTrains[i].TID << endl;
            cout << "\t\t\t\t\tTrain Source: " << availTrains[i].TSource << endl;
            cout << "\t\t\t\t\tTrain Destination: " << availTrains[i].TDest << endl;
            cout << "\t\t\t\t\tDistance: " << availTrains[i].TDistance << endl;
            cout << "\t\t\t\t\tTrain Departure Date: " << availTrains[i].TDate << endl;
            cout << "\t\t\t\t\tTrain Arrival Time: " << availTrains[i].arriveTime << endl;
            cout << "\t\t\t\t\tTrain Departure Time: " << availTrains[i].departTime << endl;
            cout << "\t\t\t\t\tAvailable Train Classes: " << availTrains[i].TClasses << endl;
            cout << "\t\t\t\t\tSeats Available: " << availTrains[i].TSeats << endl;
            cout << endl << endl;
            check = true;  // Set flag to true if a matching train is found
        }
    }

    // If no trains are found for the route, prompt to re-enter details
    if (check == false)
    {
        cout << "\t\t\t\t\tNo trains available on this route. Re-enter your details. \n";
        goto flag;   // Loop back to input cities
    }
    else
    {
        redo:
        // Prompt user to enter the train ID they wish to book
        cout << "\t\t\t\t\tInput Train ID that you wish to book: ";
        cin >> BookedID;  // Train ID input

        // Search for the entered train ID in available trains
        for (int i = 0; i < noOfTrains; i++)
        {
            if (BookedID == availTrains[i].TID)
            {
                availTrains[i].TSeats--;  // Decrement available seats
                return BookedID;  // Return the booked train ID
                check2 = true;    // Set flag to true if ID is found
            }
        }

        // If train ID is not found, prompt to re-enter the correct train ID
        if (check2 == false)
        {
            cout << "\t\t\t\t\tInput correct train ID! \n";
            goto redo;  // Loop back to input train ID
        }
    }
}

void trainPrice()
{
    int choice = 0;  // Variable to store user's class choice
    double distance = 0.0;  // Variable to store distance

    // Displaying class options and rates per KM
    cout << "\t\t\t\t\tPrices based on classes are as follows (per KM in INR): \n";
    cout << "\t\t\t\t\t1. General \t\t 0.30 INR per KM \n";
    cout << "\t\t\t\t\t2. Sleeper \t\t 0.50 INR per KM \n";
    cout << "\t\t\t\t\t3. 3AC \t\t\t 1.25 INR per KM \n";
    cout << "\t\t\t\t\t4. 2AC \t\t\t 2.00 INR per KM \n";
    cout << "\t\t\t\t\t5. 1AC \t\t\t 3.50 INR per KM \n";
    cout << "\t\t\t\t\t6. 2S \t\t\t 0.25 INR per KM \n";
    cout << "\t\t\t\t\t7. CC \t\t\t 1.00 INR per KM \n\n";

    cout << "\t\t\t\t\tInput Choice (1-7): ";
    cin >> choice;  // User selects a class

    // Validate class choice
    if (choice < 1 || choice > 7)
    {
        cout << "\t\t\t\t\tInvalid choice. Please select a valid class.\n";
        return;  // Exit if choice is invalid
    }

    cout << "\t\t\t\t\tEnter the distance of your journey (in KM): ";
    cin >> distance;  // User inputs journey distance

    // Validate distance
    if (distance <= 0)
    {
        cout << "\t\t\t\t\tInvalid distance. Please enter a positive value.\n";
        return;  // Exit if distance is not positive
    }

    // Calculate price based on class and distance
    switch (choice)
    {
        case 1:
            Price = 0.30 * distance;  // General class rate
            Class = "General";
            break;
        case 2:
            Price = 0.50 * distance;  // Sleeper class rate
            Class = "Sleeper";
            break;
        case 3:
            Price = 1.25 * distance;  // 3AC class rate
            Class = "3AC";
            break;
        case 4:
            Price = 2.00 * distance;  // 2AC class rate
            Class = "2AC";
            break;
        case 5:
            Price = 3.50 * distance;  // 1AC class rate
            Class = "1AC";
            break;
        case 6:
            Price = 0.25 * distance;  // 2S class rate
            Class = "2S";
            break;
        case 7:
            Price = 1.00 * distance;  // CC class rate
            Class = "CC";
            break;
    }

    // Display the selected class and total price
    cout << "\n\t\t\t\t\tSelected Class: " << Class << endl;
    cout << "\t\t\t\t\tTotal Price for " << distance << " KM: " << Price << " INR\n";
}


// Function to reserve a train ticket
void reserveTicket()
{
    string fName, lName;  // Variables to store first and last name of the passenger
    node *obj = new node();  // Create a new node for storing passenger details
    node* temp = tail;      // Temporary pointer to traverse through the linked list

    // If the linked list is empty (no previous bookings)
    if (head == NULL && tail == NULL)
    {
        obj->next = NULL;  // New node points to NULL as it's the only node
        head = obj;        // Set head and tail to this new node
        tail = obj;
    }
    else
    {
        temp->next = obj;   // Append new node to the end of the linked list
        tail = obj;         // Update tail to the new node
    }

    // Prompt user to enter passenger details
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\tEnter First Name of Passenger: ";
    cin >> fName;          // First name input
    cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
    cin >> lName;          // Last name input
    Name = fName + " " + lName;  // Concatenate first and last names to form the full name

    cout << "\t\t\t\t\tEnter Age: ";
    cin >> Age;            // Age input

    // Prompt for Aadhaar Number with validation
    AADCheck:
    cout << "\t\t\t\t\tEnter Aadhaar Number: ";
    cin >> AAD;            // Aadhaar input

    // Check if Aadhaar number length is exactly 12
    if (AAD.length() != 12 || AAD.length() > 12)
    {
        cout << endl;
        cout << "\t\t\t\t\tEnter a Valid Aadhaar Number!" << endl << endl;
        goto AADCheck;  // Loop to re-enter Aadhaar number
    }

    // Prompt for contact number with validation
    phoneCheck:
    cout << "\t\t\t\t\tEnter Contact Number: ";
    cin >> Contact;       // Contact number input

    // Check if contact number length is exactly 10
    if (Contact.length() != 10 || Contact.length() > 10)
    {
        cout << endl;
        cout << "\t\t\t\t\tEnter a Valid Mobile Phone Number!" << endl << endl;
        goto phoneCheck;  // Loop to re-enter contact number
    }
    cin.clear();

    // Function to fill train details
    trainFill();
    int seatCheck;

    // Iterate through available trains to fetch booking details
    for (int i = 0; i < noOfTrains; i++)
    {
        if (availTrains[i].TID == BookedID)
        {
            TName = availTrains[i].TName;
            TID = BookedID;
            Date = availTrains[i].TDate;
            ATime = availTrains[i].arriveTime;
            DTime = availTrains[i].departTime;
        }
    }

    // Function to calculate train ticket price
    trainPrice();

    // Function to choose seat number
    SeatNum = SeatChoose();

    // Process payment
    Payment();

    system("cls");  // Clear the console screen

    // Display payment success message
    cout << "\n\n\t\t\t\t\t Your payment is successfully processed!" << endl;
    cout << "\t\t\t\t\t INR " << Price << " has been deducted from your Account." << endl;

    srand(time(0));  // Seed random number generator

    // Randomly generate ticket ID
    obj->ticketID = (rand());
    cout << endl << endl;
    cout << "\t\t\t\t\tTicket Generated! Your ID is: " << obj->ticketID << endl;
    currentID = obj->ticketID;  // Store generated ticket ID

    // Store passenger details in the new node
    obj->Name = Name;
    obj->AAD = AAD;
    obj->Age = Age;
    obj->Contact = Contact;
    obj->BookedTName = TName;
    obj->BookedDest = Dest;
    obj->BookedSource = Source;
    obj->BookedSeatNum = SeatNum;
    obj->Price = Price;
    obj->BookedClass = Class;
    obj->BookedTID = TID;
    obj->BookedDate = Date;
    obj->DeptTime = DTime;
    obj->ArrTime = ATime;

    cout << endl << endl;
}

// Function to view previously booked tickets
void viewTicket()
{
    int search;          // Variable to store the search term (ticket ID or 1/2 for choices)
    string choice;       // Choice for viewing recent or older booking
    bool check = false;  // Flag to check if booking is found
    node *temp = head;   // Temporary pointer to traverse through the linked list
    cin.clear();         // Clear any errors from the input buffer

    cout << endl << endl << endl << endl << endl;
    jump:
    // Prompt to choose viewing recent or older bookings
    cout << "\t\t\t\t\tDo You Want to View Most Recent Booking? If so, Press 1\n";
    cout << "\t\t\t\t\tDo You Want to Search on Older Booking? If so, Press 2\n";
    cout << "\t\t\t\t\tEnter Choice (1-2): ";
    cin >> choice;        // User selects an option
    cin.ignore();         // Clear input buffer

    // Process the user's choice
    if (choice == "1")
    {
        search = currentID;  // Use the most recent booking ID
        check = true;
    }
    else if (choice == "2")
    {
        cout << "\t\t\t\t\tEnter Your Booking ID: ";
        cin >> search;  // Enter specific booking ID
        cout << endl << endl;
        check = true;
    }
    else
    {
        cout << "\t\t\t\t\tInvalid input. Retry! \n";
        goto jump;  // Invalid choice, retry
    }

    // Search for the booking in the linked list
    do
    {
        if (temp != NULL)
        {
            if (temp->ticketID == search && check == true)
            {
                // Display booking details
                cout << "\t\t\t\t\tBooking ID: " << temp->ticketID << endl;
                cout << "\t\t\t\t\tName: " << temp->Name << endl;
                cout << "\t\t\t\t\tAge: " << temp->Age << endl;
                cout << "\t\t\t\t\tAAD: " << temp->AAD << endl;
                cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
                cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
                cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
                cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
                cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
                cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
                cout << "\t\t\t\t\tSource: " << temp->BookedDest << endl;
                cout << "\t\t\t\t\tDestination: " << temp->BookedSource << endl;
                cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
                cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
                cout << endl << endl;
                break;
            }
            else
            {
                temp = temp->next;  // Move to the next node if current node doesn't match
            }
        }
        else
        {
            cout << "\t\t\t\t\tNo Bookings Exist. \n";
        }
    } while (temp);
}


// Function to display all reserved tickets
void display()
{
    cout << endl << endl << endl << endl << endl;
    // Check if the linked list has nodes (tickets)
    if (head != NULL && tail != NULL)
    {
        cout << "\t\t\t\t\tList is as follows: \n";
        node *temp = head;  // Start from the head of the linked list

        // Traverse through each node and display ticket details
        do {
            cout << "\t\t\t\t\tTicket ID: " << temp->ticketID << endl;
            cout << "\t\t\t\t\tName: " << temp->Name << endl;
            cout << "\t\t\t\t\tAge: " << temp->Age << endl;
            cout << "\t\t\t\t\tAAD: " << temp->AAD << endl;
            cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
            cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
            cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
            cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
            cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
            cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
            cout << "\t\t\t\t\tSource: " << temp->BookedDest << endl;
            cout << "\t\t\t\t\tDestination: " << temp->BookedSource << endl;
            cout << "\t\t\t\t\tDeparture Time: " << temp->DeptTime << endl;
            cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
            cout << endl;
            temp = temp->next;  // Move to the next node in the linked list
        } while (temp);  // Continue until the end of the list
    }
    else
        cout << "List is empty, nothing to display. \n";  // If no nodes exist
}

// Function to remove a ticket from the booking system
void removeTicket(int remTicket)
{
    node* prev = head;     // Previous node pointer
    node* delNode = head;  // Node to be deleted

    // Traverse through the list to find the node with the matching ticket ID
    while (delNode != NULL)
    {
        if (delNode->ticketID == remTicket)
        {
            break;  // Node with matching ticket ID found
        }
        else
        {
            prev = delNode;     // Move previous pointer forward
            delNode = delNode->next;  // Move current node forward
        }
    }

    // If node with given ticket ID is not found
    if (delNode == NULL)
    {
        cout << "Ticket ID Not Found!" << endl;  // Display error message
    }
    else
    {
        cout << "\t\t\t\t\tDeleted Ticket ID: " << delNode->ticketID << "\n";
        prev->next = delNode->next;  // Unlink the node being removed
        delete delNode;  // Free memory of the deleted node
    }
}

// Function to edit details of an existing ticket
void editDetails()
{
    string fName, lName;

    cout << "\t\t\t\t\tEDIT DETAILS:" << endl << endl;
    int search;
    node *temp = head;
    cin.clear();  // Clear any errors in input
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\tEnter ticket ID: ";
    cin >> search;

    // Traverse through the list to find the ticket with the matching ID
    while (temp != NULL)
    {
        if (temp->ticketID == search)
        {
            cout << "\t\t\t\t\tEnter First Name of Passenger: ";
            cin >> fName;          // First name input
            cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
            cin >> lName;          // Last name input
            Name = fName + " " + lName;  // Concatenate first and last names

            cout << "\t\t\t\t\tEnter Aadhaar Number: ";
            cin >> AAD;            // Aadhaar input
            cin.ignore();  // Clear input buffer

            cout << "\t\t\t\t\tEnter Contact Number: ";
            cin >> Contact;       // Contact number input
            cin.ignore();  // Clear input buffer

            // Update the details of the matched node
            temp->Name = Name;
            temp->AAD = AAD;
            temp->Age = Age;
            temp->Contact = Contact;
        }
        temp = temp->next;  // Move to the next node
    }
}

// Function to add new trains to the available list
void addTrains()
{
    string choice;
    do
    {
        cin.ignore();  // Clear input buffer
        cout << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\tEnter Train Name: ";
        getline(cin, availTrains[noOfTrains].TName);  // Input train name
        cout << "\t\t\t\t\tEnter Train ID: ";
        getline(cin, availTrains[noOfTrains].TID);  // Input train ID
        cout << "\t\t\t\t\tEnter Train Source: ";
        getline(cin, availTrains[noOfTrains].TSource);  // Input train source
        cout << "\t\t\t\t\tEnter Train Destination: ";
        getline(cin, availTrains[noOfTrains].TDest);  // Input train destination
        cout << "\t\t\t\t\tEnter Train Departure Date: ";
        getline(cin, availTrains[noOfTrains].TDate);  // Input train departure date
        cout << "\t\t\t\t\tEnter Train Departure Time [HH:MM (MM:HH AM/PM)]: ";
        getline(cin, availTrains[noOfTrains].departTime);  // Input departure time
        cout << "\t\t\t\t\tEnter Train Arrival Time [HH:MM (MM:HH AM/PM)]: ";
        getline(cin, availTrains[noOfTrains].arriveTime);  // Input arrival time
        cout << "\t\t\t\t\tEnter Available Train Classes: ";
        getline(cin, availTrains[noOfTrains].TClasses);  // Input available train classes
        cout << "\t\t\t\t\tEnter Seats Available: ";
        cin >> availTrains[noOfTrains].TSeats;  // Input available seats
        noOfTrains++;  // Increment the count of trains

        cin.clear();  // Clear input buffer
        cout << "\t\t\t\t\tDo you want to add more trains? (Y/N): ";
        cin >> choice;  // Ask user if they want to add more trains

        // Handle invalid input
        if (choice != "Y" && choice != "N")
            cout << "\t\t\t\t\tInvalid input. Enter choice again. ";
        else if (choice == "N")
        {
            system("cls");  // Clear screen
            cout << "\n\n\n\n\n\t\t\t\t\tTrain added! \n";
            cout << "\t\t\t\t\tSession logged out. Please login again. \n";
            Sleep(1500);  // Pause for 1.5 seconds
            system("cls");  // Clear screen
            main();  // Restart the main menu
        }
    } while (choice != "N");  // Continue adding trains until 'N' is selected
}


// Main function for the Railway Booking System
void trainBookingSystem()
{
    // Initialize available trains
    iniTrain();

relog:
    cin.clear();  // Clear any error flags in the input stream
    string check;
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\tWELCOME TO RAILWAY BOOKING SYSTEM!\n\n\n";
    Sleep(300);
    cout << "\n\n\t\t\t\t\t\tProject Prepared by:";
    Sleep(400);
    cout << "\n\n\t\t\t\t\t\t--------------------";
    Sleep(500);
    cout << "\n\n\t\t\t\t                      Ankit Raj          ";
    Sleep(1000);
    cout << endl;
    system("cls");

log:
    // Prompt user for their role: User or Admin
    cout << "\n\n\n\n\n\t\t\t\tIf you are a user looking to book a ticket, type 1 \n";
    cout << "\t\t\t\tIf you are an admin, type 2 \n";
    cout << "\n\n\t\t\t\t\t\tChoice: ";
    cin >> check;

    // User mode
    if (check == "1")
    {
        int tickID;
        string choice;
        system("cls");

        cout << endl << endl << endl << endl << endl;
        do
        {
            cout << "\t\t\t\t     -----------------------------------------\n";
            cout << "\t\t\t\t\tSelect 1 to Reserve a Ticket. \n";
            cout << "\t\t\t\t\tSelect 2 to View your Reservation. \n";
            cout << "\t\t\t\t\tSelect 3 to Display all tickets. \n";
            cout << "\t\t\t\t\tSelect 4 to Delete a ticket. \n";
            cout << "\t\t\t\t\tSelect 5 to Edit Details. \n";
            cout << "\t\t\t\t\tSelect 6 to Log Out of Session. \n";
            cout << "\t\t\t\t\tSelect 7 to Exit\n";
            cout << endl << endl;
            cout << "\t\t\t\t\tEnter Choice To Proceed (1-7): ";
            cin >> choice;

            if (choice == "1")
            {
                system("cls");
                cin.clear();
                reserveTicket();  // Function to reserve a ticket
            }
            else if (choice == "2")
            {
                system("cls");
                viewTicket();  // Function to view reservations
            }
            else if (choice == "3")
            {
                system("cls");
                display();  // Function to display all tickets
            }
            else if (choice == "4")
            {
                cout << "\t\t\t\t\tEnter your Ticket ID: ";
                cin >> tickID;
                removeTicket(tickID);  // Function to remove a ticket
            }
            else if (choice == "5")
            {
                system("cls");
                editDetails();  // Function to edit ticket details
            }
            else if (choice == "6")
            {
                goto relog;  // Go back to user/admin selection
            }
            else if (choice == "7")
            {
                Sleep(300);
                cout << "\t\t\t\t\tTHANK YOU FOR USING OUR SOFTWARE! \n";
                Sleep(300);
                exit(0);  // Exit the program
            }
            else
            {
                cout << "\t\t\t\t\tEnter correct choice. Try again. \n";  // Invalid input
            }
        } while (choice != "7");
    }

    // Admin mode
    else if (check == "2")
        admin();  // Function to handle admin operations
    else
    {
        cout << "Invalid input. Try again. \n";  // Invalid input
        goto log;  // Retry selecting user or admin mode
    }
}

// Admin function to handle admin portal
void admin()
{
    string choice, user, password;
    system("cls");
    cin.clear();
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\tWELCOME TO ADMIN PORTAL!\n\n";

    cout << "\t\t\t\t\tEnter your login credentials below! \n";

login:
    cout << "\t\t\t\t\tEnter your Username: ";
    cin >> user;
    cout << "\t\t\t\t\tEnter your Password: ";
    cin >> password;

    // Hardcoded admin credentials
    if (user == "ANKIT" && password == "8969")
    {
        cout << "\t\t\t\t\tLogged in Successfully!\n";
        cin.clear();
        system("cls");
        cout << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\tSelect 1 to View all Booked Tickets. \n";
        cout << "\t\t\t\t\tSelect 2 to add Trains. \n";
        cout << "\t\t\t\t\tSelect 3 to Exit\n";
        do
        {
            cout << "\t\t\t\t\tEnter Choice To Proceed (1-2): ";
            cin >> choice;

            if (choice == "1")
                display();  // Function to display all booked tickets
            else if (choice == "2")
            {
                cin.clear();
                addTrains();  // Function to add new trains
                if (trainCheck == false)
                    trainFill();  // Additional train filling process
            }
            else if (choice == "3")
            {
                system("cls");
                main();  // Return to main user/admin selection
            }
            else
                cout << "\t\t\t\t\tEnter correct choice. Try again. \n";
        } while (choice != "3");
    }
    else
    {
        cout << "\t\t\t\t\tInvalid credentials. Please login again. \n";
        goto login;  // Retry login
    }
}




constexpr int Max_PRIROITY = 10;
constexpr int INF = std::numeric_limits<int>::max();

inline void printSeparator()

{

    cout << "--------------------------------------------\n";

}

inline void pauseExecution()

{

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

}

const vector<string> karnataka_locations =

{

    "Bangalore", "Mysore", "Mangalore", "Udupi", "Hubli", "Dharwad", "Belgaum", "Gulbarga", "Bellary", "Shimoga",

    "Davangere", "Tumkur", "Raichur", "Bijapur", "Hassan", "Bagalkot", "Chikmagalur", "Chitradurga", "Bidar", "Mandya"

};

unordered_map<string, unordered_map<string, int>> location_graph;

inline int calculateDistance(const string& loc1, const string& loc2)

{
    return abs(static_cast<int>(loc1[0]) - static_cast<int>(loc2[0]))

     +
           abs(static_cast<int>(loc1[1]) - static_cast<int>(loc2[1]));

}

void initializeGraph()

{

    for (const auto& loc1 : karnataka_locations)

        {

        for (const auto& loc2 : karnataka_locations)

         {

            location_graph[loc1][loc2] = calculateDistance(loc1, loc2);

        }

    }

}


class Passenger

{

public:
    int id;
    int priority;
    int arrivalTime;
    int serviceTime;
    int estimatedCrowdingTime;
    string pickup_location;
    string dropoff_location;
    string cab_type;
    int time_constraint;
    int feedback;

    Passenger(int id, int priority = 0, int serviceTime = 0, int arrivalTime = 0, int estimatedCrowdingTime = 0);

};


class Cab

{

public:
    int id;
    int capacity;
    vector<int> passengers;
    int currentLoad;
    string current_location;
    bool is_available;
    int total_distance_traveled;
    list<string> route_history;
    string cab_type;
    int maintenance_status;
    vector<int> assigned_passengers;

    Cab(int id, int capacity);
    bool assignPassenger(int passengerID);
    void showStatus();
    void reset();

};


class Seat

{

public:
    int id;
    bool isOccupied;

    Seat(int id);
    bool occupySeat();
    void freeSeat();

};


class Cabin

{

public:
    int id;
    int capacity;
    vector<Seat> seats;

    Cabin(int id, int capacity);
    bool assignSeat(Passenger& passenger);
    void showStatus();

};


class Scheduler

{

public:
    vector<Cab> cabs;
    vector<Cabin> cabins;
    int totalSeats;

    Scheduler(int numCabs, int capacityPerCab, int numCabins, int capacityPerCabin);


    void FCFS(vector<Passenger>& passengers);
    void PriorityScheduling(vector<Passenger>& passengers);
    void LeastConnections(vector<Passenger>& passengers);
    void RandomAllocation(vector<Passenger>& passengers);
    void LoadBalancing(vector<Passenger>& passengers);
    void RealTimePredictionAndAllocation(vector<Passenger>& passengers);


    void showAllCabs();
    void showAllCabins();
    void resetCabs();
    void resetCabins();
    void displayPassengers(vector<Passenger>& passengers);

};

Passenger::Passenger(int id, int priority, int serviceTime, int arrivalTime, int estimatedCrowdingTime)
    : id(id), priority(priority), serviceTime(serviceTime), arrivalTime(arrivalTime), estimatedCrowdingTime(estimatedCrowdingTime), time_constraint(0), feedback(0)

    {}

Cab::Cab(int id, int capacity) : id(id), capacity(capacity), currentLoad(0), is_available(true), total_distance_traveled(0)

{}

bool Cab::assignPassenger(int passengerID)

{

    if (currentLoad < capacity)

        {

        passengers.push_back(passengerID);
        currentLoad++;
        return true;

    }

    return false;
}

void Cab::showStatus()

{

    cout << "Cab " << id << " [Current Load: " << currentLoad << "/" << capacity << "]: ";
    for (int passenger : passengers)

        {

        cout << "P" << passenger << " ";
    }

    cout << endl;

}

void Cab::reset()

{
    passengers.clear();
    currentLoad = 0;
    is_available = true;
    total_distance_traveled = 0;
    route_history.clear();
    assigned_passengers.clear();

}

Seat::Seat(int id) : id(id), isOccupied(false)

{}

bool Seat::occupySeat()

{
    if (!isOccupied)
        {

        isOccupied = true;
        return true;
    }

    return false;

}

void Seat::freeSeat()

{
    isOccupied = false;
}

Cabin::Cabin(int id, int capacity) : id(id), capacity(capacity)

{
    for (int i = 0; i < capacity; ++i)

    {

        seats.push_back(Seat(i));

    }

}

bool Cabin::assignSeat(Passenger& passenger)

{
    for (auto& seat : seats)

        {

        if (seat.occupySeat())

        {

            return true;


        }

    }

    return false;
}

void Cabin::showStatus()

{

    cout << "Cabin " << id << " [" << seats.size() << "/" << capacity << " seats]: ";
    for (const auto& seat : seats)

        {

        cout << (seat.isOccupied ? "X " : "O ");
    }

    cout << endl;
}

Scheduler::Scheduler(int numCabs, int capacityPerCab, int numCabins, int capacityPerCabin)

{

    for (int i = 0; i < numCabs; ++i)

        {

        cabs.push_back(Cab(i, capacityPerCab));

    }

    for (int i = 0; i < numCabins; ++i)

        {

        cabins.push_back(Cabin(i, capacityPerCabin));

    }

    totalSeats = numCabs * capacityPerCab + numCabins * capacityPerCabin;
}

void Scheduler::showAllCabs()

{

    for (auto& cab : cabs)

        {

        cab.showStatus();

    }

}

void Scheduler::showAllCabins()

{

    for (auto& cabin : cabins)

        {

        cabin.showStatus();
    }
}

void Scheduler::resetCabs()

{

    for (auto& cab : cabs)

        {

        cab.reset();

    }

}

void Scheduler::resetCabins()

{

    for (auto& cabin : cabins)

        {

        for (auto& seat : cabin.seats)

        {

            seat.freeSeat();

        }

    }

}

void Scheduler::displayPassengers(vector<Passenger>& passengers)

{

    for (auto& p : passengers)

        {

        cout << "Passenger ID: " << p.id << ", Arrival Time: " << p.arrivalTime
             << ", Priority: " << p.priority << ", Estimated Crowding Time: " << p.estimatedCrowdingTime << endl;

    }

}

void Scheduler::FCFS(vector<Passenger>& passengers)

{

    sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b)

         {

        return a.arrivalTime < b.arrivalTime;
    }

    );

    for (auto& passenger : passengers)

        {

        bool assigned = false;
        for (auto& cab : cabs)

        {

            if (cab.assignPassenger(passenger.id))

            {

                assigned = true;
                break;


            }


        }

        if (!assigned)

            {

            cout << "Passenger " << passenger.id << " could not be assigned to a cab.\n";

        }

    }

}

void Scheduler::PriorityScheduling(vector<Passenger>& passengers)

{

    sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b)

         {

        return a.priority > b.priority;
    }

    );

    for (auto& passenger : passengers)

        {

        bool assigned = false;
        for (auto& cab : cabs)

        {

            if (cab.assignPassenger(passenger.id))

            {

                assigned = true;
                break;

            }


        }

        if (!assigned)

            {

            cout << "Passenger " << passenger.id << " could not be assigned to a cab.\n";

        }

    }

}

void Scheduler::LeastConnections(vector<Passenger>& passengers)

{

    for (auto& passenger : passengers)

        {

        int minCabIndex = 0;
        for (int i = 1; i < cabs.size(); ++i)

        {

            if (cabs[i].currentLoad < cabs[minCabIndex].currentLoad)

            {

                minCabIndex = i;


            }


        }


        if (!cabs[minCabIndex].assignPassenger(passenger.id))

            {

            cout << "Passenger " << passenger.id << " could not be assigned to a cab.\n";


        }


    }


}

void Scheduler::RandomAllocation(vector<Passenger>& passengers)

{

    srand(time(0));
    for (auto& passenger : passengers)

        {

        bool assigned = false;
        while (!assigned)

        {

            int randomCabIndex = rand() % cabs.size();
            if (cabs[randomCabIndex].assignPassenger(passenger.id))

            {

                assigned = true;


          }


        }


    }


}

void Scheduler::LoadBalancing(vector<Passenger>& passengers)

{

    sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b)

         {

        return a.estimatedCrowdingTime < b.estimatedCrowdingTime;
    }

    );

    for (auto& passenger : passengers)

        {

        bool assigned = false;
        for (auto& cab : cabs)

        {


            if (cab.assignPassenger(passenger.id))

            {

                assigned = true;
                break;


            }


        }

        if (!assigned)

            {

            cout << "Passenger " << passenger.id << " could not be assigned to a cab.\n";


        }


    }


}

void Scheduler::RealTimePredictionAndAllocation(vector<Passenger>& passengers)

{

    for (auto& passenger : passengers)

        {

        int predictedTime = passenger.arrivalTime + passenger.estimatedCrowdingTime;

        bool assigned = false;
        for (auto& cab : cabs)

            {

            if (cab.assignPassenger(passenger.id))

            {

                assigned = true;
                break;


            }

        }


        if (!assigned)

            {

            cout << "Passenger " << passenger.id << " could not be assigned to a cab.\n";


        }


    }


}

map<int, vector<int>> balanceLoad(const vector<Passenger>& passengers, vector<Cab>& cabs)

{

    map<int, vector<int>> allocations;

    for (const auto& passenger : passengers)

        {

        int best_cab = -1;
        int min_distance = INF;

        for (auto& cab : cabs)

            {

            if (cab.is_available && cab.currentLoad < cab.capacity && cab.cab_type == passenger.cab_type)

            {

                int distance = calculateDistance(cab.current_location, passenger.pickup_location);
                if (distance < min_distance)

                {

                    min_distance = distance;
                    best_cab = cab.id;


                }


            }


        }

        if (best_cab != -1)

            {

            allocations[best_cab].push_back(passenger.id);

            for (auto& cab : cabs)

                {

                if (cab.id == best_cab)

                {

                    cab.currentLoad++;
                    cab.total_distance_traveled += min_distance;
                    cab.route_history.push_back(passenger.pickup_location);
                    cab.assigned_passengers.push_back(passenger.id);
                    if (cab.currentLoad == cab.capacity)

                    {

                        cab.is_available = false;


                    }


                }


            }


        }


    }

    return allocations;


}

void generateStatistics(const vector<Cab>& cabs)

{

    int total_distance = 0;
    int utilized_cabs = 0;
    int total_passengers = 0;
    map<string, int> cab_type_count;
    map<int, int> maintenance_status_count;

    for (const auto& cab : cabs)

        {

        total_distance += cab.total_distance_traveled;
        if (!cab.is_available)

        {

            utilized_cabs++;

        }

        total_passengers += cab.currentLoad;
        cab_type_count[cab.cab_type]++;
        maintenance_status_count[cab.maintenance_status]++;

    }

    printSeparator();
    cout << "Simulation Statistics:\n";
    cout << "Total Distance Traveled: " << total_distance << " units\n";
    cout << "Utilized Cabs: " << utilized_cabs << " out of " << cabs.size() << "\n";
    cout << "Total Passengers Transported: " << total_passengers << "\n";
    cout << "Cab Type Distribution:\n";
    for (const auto& [type, count] : cab_type_count)

        {

        cout << type << ": " << count << "\n";

    }

    cout << "Maintenance Status Distribution:\n";
    for (const auto& [status, count] : maintenance_status_count)

        {

        cout << "Status " << status << ": " << count << "\n";

    }

    printSeparator();

}

void displayRouteHistory(const vector<Cab>& cabs)

{

    cout << "\nRoute History:\n";
    for (const auto& cab : cabs)

        {

        cout << "Cab " << cab.id << " (" << cab.cab_type << "): ";
        for (const auto& location : cab.route_history)

        {

            cout << location << " -> ";

        }

        cout << "END\n";


    }


}

void displayAllocations(const map<int, vector<int>>& allocations)

{

    cout << "\nPassenger Allocations:\n";
    for (const auto& [cab_id, passenger_ids] : allocations)

        {

        cout << "Cab " << cab_id << " assigned to passengers: ";
        for (const auto& pid : passenger_ids)

        {

            cout << pid << " ";

        }

        cout << "\n";

    }

    printSeparator();

}

void inputPassengers(vector<Passenger>& passengers, int num_passengers)

{

    for (int i = 0; i < num_passengers; ++i)

        {

        Passenger p(i);
        cout << "Enter pickup location for passenger " << i << ": ";
        cin >> p.pickup_location;
        cout << "Enter dropoff location for passenger " << i << ": ";
        cin >> p.dropoff_location;
        cout << "Enter priority (0-" << Max_PRIROITY << ") for passenger " << i << ": ";
        cin >> p.priority;
        cout << "Enter cab type (Mini/Sedan/SUV) for passenger " << i << ": ";
        cin >> p.cab_type;
        cout << "Enter time constraint (minutes) for passenger " << i << ": ";
        cin >> p.time_constraint;
        cout << "Enter feedback (1-5) for passenger " << i << ": ";
        cin >> p.feedback;

        passengers.push_back(p);


    }


}

void inputCabs(vector<Cab>& cabs, int num_cabs)

{

    for (int i = 0; i < num_cabs; ++i)

        {

        Cab c(i, 4);
        cout << "Enter current location for cab " << i << ": ";
        cin >> c.current_location;
        cout << "Enter cab type (Mini/Sedan/SUV) for cab " << i << ": ";
        cin >> c.cab_type;
        c.capacity = (c.cab_type == "SUV") ? 6 : 4;
        cout << "Enter maintenance status (0-2) for cab " << i << ": ";
        cin >> c.maintenance_status;

        cabs.push_back(c);


    }


}

void cabBookingSystem()

{

    initializeGraph();

    vector<Passenger> passengers;
    vector<Cab> cabs;

    int num_passengers;
    cout << "Enter the number of passengers: ";
    cin >> num_passengers;
    inputPassengers(passengers, num_passengers);

    int num_cabs;
    cout << "Enter the number of cabs: ";
    cin >> num_cabs;
    inputCabs(cabs, num_cabs);

    auto allocations = balanceLoad(passengers, cabs);
    generateStatistics(cabs);
    displayAllocations(allocations);
    displayRouteHistory(cabs);

    cout << "Simulation Complete.\n";
    pauseExecution();

}

struct Edge
 {

     int destination;
     int weight;

};

class BusSystem
{

private:

      vector<vector<Edge>> graph;
      vector<int> busOccupancy;
      int numBuses;

public:

    BusSystem(int n) : numBuses(n)
    {

        graph.resize(n + 1);
        busOccupancy.resize(n + 1, 0);

    }

    void addRoute(int source, int destination, int weight)
    {

        if (source < 1 || source > numBuses || destination < 1 || destination > numBuses)
            {

            cout << "Invalid bus ID(s) for route." << endl;
            return;

            }
        graph[source].push_back({destination, weight});
        graph[destination].push_back({source, weight});
        cout << "Route added from bus " << source << " to bus " << destination << " with weight " << weight << endl;

    }


    void updateOccupancy(int busId, int occupancy)
     {

        if (busId < 1 || busId > numBuses)
            {

             cout << "Invalid bus ID." << endl;
             return;

            }

        busOccupancy[busId] = occupancy;
        cout << "Occupancy updated for bus " << busId << ": " << busOccupancy[busId] << endl;

    }

    vector<int> findLeastCrowdedRoute(int start, int end)
     {

        if (start < 1 || start > numBuses || end < 1 || end > numBuses)
            {

            cout << "Invalid bus ID(s) for route search." << endl;
            return {};

            }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distances(numBuses + 1, numeric_limits<int>::max());
        vector<int> previous(numBuses + 1, -1);
        vector<bool> visited(numBuses + 1, false);

        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
            {

              int currentBus = pq.top().second;
              pq.pop();

            if (visited[currentBus]) continue;
            visited[currentBus] = true;

            if (currentBus == end)
                {

                   break;

                }

            for (const Edge& edge : graph[currentBus])
                {

                   int newDist = distances[currentBus] + edge.weight;
                   if (newDist < distances[edge.destination])
                    {

                      distances[edge.destination] = newDist;
                      previous[edge.destination] = currentBus;
                      pq.push({newDist, edge.destination});

                }

            }

        }

        vector<int> path;
        for (int at = end; at != -1; at = previous[at])
            {

               path.push_back(at);

            }
        reverse(path.begin(), path.end());
        return path;

    }

    void balanceLoad(int busId, int newOccupancy)
     {

        if (busId < 1 || busId > numBuses)
            {

            cout << "Invalid bus ID." << endl;
            return;

            }
        busOccupancy[busId] += newOccupancy;
        cout << "Updated occupancy for bus " << busId << ": " << busOccupancy[busId] << endl;


        int leastCrowdedBus = -1;
        int minOccupancy = numeric_limits<int>::max();

        for (int i = 1; i <= numBuses; ++i)
            {

            if (busOccupancy[i] < minOccupancy)
            {

                minOccupancy = busOccupancy[i];
                leastCrowdedBus = i;

            }

        }

        cout << "Least crowded bus is " << leastCrowdedBus << " with occupancy " << minOccupancy << endl;

     }

    void displayOccupancy()
     {

        cout << "Current Bus Occup ancy:" << endl;
        for (int i = 1; i <= numBuses; ++i)
            {

            cout << "Bus " << i << ": " << busOccupancy[i] << " passengers" << endl;

            }

    }

    void displayRoutes()
     {

        cout << "Current Bus Routes:" << endl;
        for (int i = 1; i <= numBuses; ++i)
            {

            cout << "Bus " << i << " routes to: ";
            for (const Edge& edge : graph[i])
            {
                cout << edge.destination << " (weight: " << edge.weight << "), ";
            }

            cout << endl;

        }

    }

    void resetOccupancy()
    {

        for (int i = 1; i <= numBuses; ++i)
            {

            busOccupancy[i] = 0;

            }

        cout << "All bus occupancies have been reset." << endl;

    }

    void userAddRoute()
     {

        int source, destination, weight;
        cout << "Enter source bus ID: ";
        cin >> source;
        cout << "Enter destination bus ID: ";
        cin >> destination;
        cout << "Enter weight (passenger count): ";
        cin >> weight;
        addRoute(source, destination, weight);

    }

    void userUpdateOccupancy()
    {

        int busId, occupancy;
        cout << "Enter bus ID to update occupancy: ";
        cin >> busId;
        cout << "Enter new occupancy: ";
        cin >> occupancy;
        updateOccupancy(busId, occupancy);

    }

    void userBalanceLoad()
    {

        int busId, newOccupancy;
        cout << "Enter bus ID to balance load: ";
        cin >> busId;
        cout << "Enter new occupancy to add: ";
        cin >> newOccupancy;
        balanceLoad(busId, newOccupancy);

    }

    void displayMenu()
    {

        cout << "Bus System Menu:" << endl;
        cout << "1. Add Route" << endl;
        cout << "2. Update Occupancy" << endl;
        cout << "3. Balance Load" << endl;
        cout << "4. Display Occupancy" << endl;
        cout << "5. Display Routes" << endl;
        cout << "6. Reset Occupancy" << endl;
        cout << "7. Find Least Crowded Route" << endl;
        cout << "8. Exit" << endl;

    }


    void findAndDisplayLeastCrowdedRoute()
    {

        int start, end;
        cout << "Enter start bus ID: ";
        cin >> start;
        cout << "Enter end bus ID: ";
        cin >> end;
        vector<int> route = findLeastCrowdedRoute(start, end);
        if (!route.empty())
            {

            cout << "Least crowded route from bus " << start << " to bus " << end << ": ";
            for (int bus : route)
            {
                cout << bus << " ";
            }

            cout << endl;
        }
        else
            {

                 cout << "No valid route found." << endl;
            }

    }

};


int routeSelectionSystem()
{

    int numberOfBuses;
    cout << "Enter the number of buses in the system: ";
    cin >> numberOfBuses;

    BusSystem busSystem(numberOfBuses);

    busSystem.addRoute(1, 2, 3);
    busSystem.addRoute(4, 5, 6);
    busSystem.addRoute(7, 8, 9);
    busSystem.addRoute(10, 11, 12);
    busSystem.addRoute(13, 14, 15);

    busSystem.updateOccupancy(1, 100);
    busSystem.updateOccupancy(2, 75);
    busSystem.updateOccupancy(3, 50);
    busSystem.updateOccupancy(4, 25);
    busSystem.updateOccupancy(5, 5);

    int choice;
    while (true)
    {

        busSystem.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
         {

            case 1:
                busSystem.userAddRoute();
                break;

            case 2:
                busSystem.userUpdateOccupancy();
                break;

            case 3:
                busSystem.userBalanceLoad();
                break;

            case 4:
                busSystem.displayOccupancy();
                break;

            case 5:
                busSystem.displayRoutes();
                break;

            case 6:
                busSystem.resetOccupancy();
                break;

            case 7:
                busSystem.findAndDisplayLeastCrowdedRoute();
                break;

            case 8:
                cout << "Exiting the system." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    }

    return 0;

}

const int TOTAL_SEATS = 10;

class Passenger1 {

public:
    std::string name;
    int age;
    std::string id;

    Passenger1() : name(""), age(0), id("") {}
    Passenger1(std::string name, int age, std::string id)
        : name(name), age(age), id(id) {}

};

class SeatAllocationSystem
 {

private:
    bool occupiedSeats[TOTAL_SEATS];
    Passenger1 seatMap[TOTAL_SEATS];

public:
    SeatAllocationSystem()
    {

        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            occupiedSeats[i] = false;

            }

    }

    bool allocateSeat(const std::string& name, int age, const std::string& id)
    {

        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            if (!occupiedSeats[i])
            {

                occupiedSeats[i] = true;
                seatMap[i] = Passenger1(name, age, id);
                std::cout << "Seat " << i + 1 << " allocated to " << name << std::endl;
                return true;

            }

        }
        std::cout << "No seats available for allocation." << std::endl;
        return false;

    }


    bool deallocateSeat(int seatId)
     {

        if (seatId < 1 || seatId > TOTAL_SEATS)
            {

            std::cout << "Invalid seat ID." << std::endl;
            return false;

            }
        int index = seatId - 1;
        if (occupiedSeats[index])
            {

            occupiedSeats[index] = false;
            seatMap[index] = Passenger1();
            std::cout << "Seat " << seatId << " deallocated." << std::endl;
            return true;

        }
         else {

                    std::cout << "Seat " << seatId << " is already unoccupied." << std::endl;
                    return false;

        }

    }

    void displaySeatStatus()
     {

        std::cout << "Current Seat Status:" << std::endl;
        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            if (occupiedSeats[i])
             {

                std::cout << "Seat " << i + 1 << " is occupied by "
                          << seatMap[i].name << " (ID: " << seatMap[i].id << ", Age: " << seatMap[i].age << ")" << std::endl;

             }
             else
                {

                  std::cout << "Seat " << i + 1 << " is unoccupied." << std::endl;

                }
           }

      }



    void searchPassengerById(const std::string& id)
    {

        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            if (occupiedSeats[i] && seatMap[i].id == id)
             {

                std::cout << "Passenger found: " << seatMap[i].name
                          << " (Age: " << seatMap[i].age << ", Seat: " << i + 1 << ")" << std::endl;
                return;

            }

        }

        std::cout << "Passenger with ID " << id << " not found." << std::endl;

    }


    void listAllPassengers()
    {

        std::cout << "List of all passengers:" << std::endl;
        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            if (occupiedSeats[i])
             {

                std::cout << "Seat " << i + 1 << ": " << seatMap[i].name
                          << " (ID: " << seatMap[i].id << ", Age: " << seatMap[i].age << ")" << std::endl;

            }

        }

    }


    void reserveMultipleSeats(int numberOfPassengers)
    {

        if (numberOfPassengers <= 0 || numberOfPassengers > TOTAL_SEATS)
            {

            std::cout << "Invalid number of passengers." << std::endl;
            return;

            }

        for (int i = 0; i < numberOfPassengers; ++i)
            {

               std::string name, id;
               int age;

            std::cout << "Enter name for passenger " << (i + 1) << ": ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter age for passenger " << (i + 1) << ": ";
            while (!(std::cin >> age) || age < 0) {
                std::cout << "Invalid age. Please enter a valid age: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }
            std::cout << "Enter ID for passenger " << (i + 1) << ": ";
            std::cin >> id;

            if (!allocateSeat(name, age, id))
                {

                 std::cout << "Failed to allocate seat for passenger " << name << ". Stopping reservation." << std::endl;
                 break;

            }

        }

    }


    void displayAvailableSeats()
     {

        std::cout << "Available Seats:" << std::endl;
        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

             if (!occupiedSeats[i])
              {

                std::cout << "Seat " << i + 1 << " is available." << std::endl;

              }

        }

    }


    void clearAllReservations()
    {

        for (int i = 0; i < TOTAL_SEATS; ++i)
            {

            if (occupiedSeats[i])
             {

                occupiedSeats[i] = false;
                seatMap[i] = Passenger1();

            }

        }

        std::cout << "All reservations have been cleared." << std::endl;

    }

};

int seatAllocationSystem()
{

    SeatAllocationSystem system;
    int choice;
    std::string id;
    int age, seatId, numberOfPassengers;

    do
        {

        std::cout << "\n1. Allocate Seat\n2. Deallocate Seat\n3. Display Seat Status\n4. Search Passenger by ID\n5. List All Passengers\n6. Reserve Multiple Seats\n7. Display Available Seats\n8. Clear All Reservations\n9. Exit\n";
        std::cout << "Enter your choice: ";
        while (!(std::cin >> choice) || choice < 1 || choice > 9)
         {

            std::cout << "Invalid choice. Please enter a number between 1 and 9: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }

        switch (choice)
        {

            case 1:
                {

                    std::string name;
                    std::cout << "Enter passenger name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter passenger age: ";
                    while (!(std::cin >> age) || age < 0)
                        {

                        std::cout << "Invalid age. Please enter a valid age: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        }

                    std::cout << "Enter passenger ID: ";
                    std::cin >> id;
                    system.allocateSeat(name, age, id);

                }

                break;

            case 2:
                std::cout << "Enter seat ID to deallocate: ";
                std::cin >> seatId;
                system.deallocateSeat(seatId);
                break;

            case 3:
                system.displaySeatStatus();
                break;

            case  4:
                std::cout << "Enter passenger ID to search: ";
                std::cin >> id;
                system.searchPassengerById(id);
                break;

            case 5:
                system.listAllPassengers();
                break;

            case 6:
                std::cout << "Enter number of passengers to reserve seats for: ";
                while (!(std::cin >> numberOfPassengers) || numberOfPassengers <= 0 || numberOfPassengers > TOTAL_SEATS) { // Validate number of passengers
                    std::cout << "Invalid number of passengers. Please enter a valid number: ";
                    std::cin.clear(); // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                }
                system.reserveMultipleSeats(numberOfPassengers);
                break;

            case 7:
                system.displayAvailableSeats();
                break;

            case 8:
                system.clearAllReservations();
                break;

            case 9:
                std::cout << "Exiting the system." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;

        }

    }
    while (choice != 9);

    return 0;

}

struct BusSchedule
 {

    int arrivalTime;
    int departureTime;
    int routeLength;
    int demand;

    BusSchedule(int arrival, int departure, int length, int demand)
        : arrivalTime(arrival), departureTime(departure), routeLength(length), demand(demand) {}

};


struct CompareDemand
{

    bool operator()(const BusSchedule& a, const BusSchedule& b)
     {

         return a.demand < b.demand;

    }

};


void generateOptimizedBusSchedules(vector<BusSchedule>& schedules)
 {

    sort(schedules.begin(), schedules.end(), [](const BusSchedule& a, const BusSchedule& b)
         {

        return a.routeLength < b.routeLength;

         });

    priority_queue<BusSchedule, vector<BusSchedule>, CompareDemand> maxHeap;

    for (const auto& schedule : schedules)
        {

           maxHeap.push(schedule);

        }

    cout << "\nOptimized Bus Schedule based on Demand:" << endl;
    while (!maxHeap.empty())
        {

          BusSchedule bus = maxHeap.top();
          maxHeap.pop();
          cout << "Bus (Arrival: " << bus.arrivalTime << ", Departure: " << bus.departureTime
             << ", Route Length: " << bus.routeLength << ", Demand: " << bus.demand << ")" << endl;

    }

}

void optimizeSchedules(vector<BusSchedule>& schedules, int maxTime)
{

    vector<int> dp(maxTime + 1, 0);

    for (const auto& bus : schedules)
        {

        for (int j = maxTime; j >= bus.routeLength; --j)
        {
            dp[j] = max(dp[j], dp[j - bus.routeLength] + bus.demand);
        }

    }


    cout << "Maximum Demand Achievable within " << maxTime << " minutes: " << dp[maxTime] << endl;

}


void displaySchedules(const vector<BusSchedule>& schedules)
 {

    cout << "\nBus Schedules:" << endl;
    cout << left << setw(15) << "Arrival Time"
         << setw(15) << "Departure Time"
         << setw(15) << "Route Length"
         << setw(15) << "Demand" << endl;

    for (const auto& bus : schedules)
        {

            cout << left << setw(15) << bus.arrivalTime
             << setw(15) << bus.departureTime
             << setw(15) << bus.routeLength
             << setw(15) << bus.demand << endl;
       }

}

bool validateInput(int& input)
{
    cin >> input;
    if (cin.fail() || input < 0)
        {

         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         return false;

        }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;

}


void addBusSchedule(vector<BusSchedule>& schedules)
 {
    int arrival, departure, length, demand;

    cout << "Enter arrival time : ";
    while (!validateInput(arrival))
        {

        cout << "Invalid input. Please enter a valid arrival time: ";

        }

    cout << "Enter departure time : ";
    while (!validateInput(departure))
        {

           cout << "Invalid input. Please enter a valid departure time: ";

        }

    cout << "Enter route length (in km): ";
    while (!validateInput(length))
        {

          cout << "Invalid input. Please enter a valid route length: ";

        }

    cout << "Enter demand (number of passengers): ";
    while (!validateInput(demand))
        {

          cout << "Invalid input. Please enter a valid demand: ";

        }

    schedules.emplace_back(arrival, departure, length, demand);
    cout << "Bus schedule added successfully!" << endl;

}

void removeBusSchedule(vector<BusSchedule>& schedules)
{

    int index;
    cout << "Enter the index of the bus schedule to remove (0 to " << schedules.size() - 1 << "): ";
    while (!validateInput(index) || index < 0 || index >= schedules.size())
        {
            cout << "Invalid input. Please enter a valid index: ";
        }

    schedules.erase(schedules.begin() + index);
    cout << "Bus schedule removed successfully!" << endl;

}

void updateBusSchedule(vector<BusSchedule>& schedules)
{

    int index;
    cout << "Enter the index of the bus schedule to update (0 to " << schedules.size() - 1 << "): ";
    while (!validateInput(index) || index < 0 || index >= schedules.size())
        {
            cout << "Invalid input. Please enter a valid index: ";
        }

    int arrival, departure, length, demand;
    cout << "Enter new arrival time : ";
    while (!validateInput(arrival))
        {

           cout << "Invalid input. Please enter a valid arrival time: ";

        }

    cout << "Enter new departure time: ";
    while (!validateInput(departure))
        {
        cout << "Invalid input. Please enter a valid departure time: ";
        }

    cout << "Enter new route length (in km): ";
    while (!validateInput(length))
        {
        cout << "Invalid input. Please enter a valid route length: ";
        }

    cout << "Enter new demand (number of passengers): ";
    while (!validateInput(demand))
     {
        cout << "Invalid input. Please enter a valid demand: ";
     }

    schedules[index] = BusSchedule(arrival, departure, length, demand);
    cout << "Bus schedule updated successfully!" << endl;

}

void displayMenu()
{

    cout << "\nBus Scheduling System Menu:" << endl;
    cout << "1. Display Bus Schedules" << endl;
    cout << "2. Add Bus Schedule" << endl;
    cout << "3. Remove Bus Schedule" << endl;
    cout << "4. Update Bus Schedule" << endl;
    cout << "5. Generate Optimized Bus Schedules" << endl;
    cout << "6. Optimize Schedules" << endl;
    cout << "7. Exit" << endl;

}

int busScheduleSystem()
{

    vector<BusSchedule> schedules;
    int choice;

    while (true)
        {

        displayMenu();
        cout << "Enter your choice: ";
        while (!validateInput(choice) || choice < 1 || choice > 7)

         {
            cout << "Invalid choice. Please enter a number between 1 and 7: ";
         }

        switch (choice)
        {

            case 1:
                displaySchedules(schedules);
                break;

            case 2:
                addBusSchedule(schedules);
                break;

            case 3:
                removeBusSchedule(schedules);
                break;

            case 4:
                updateBusSchedule(schedules);
                break;

            case 5:
                generateOptimizedBusSchedules(schedules);
                break;

            case 6:
                 {

                int maxTime;
                cout << "Enter maximum time constraint (in minutes): ";
                while (!validateInput(maxTime) || maxTime < 0)
                    {
                    cout << "Invalid input. Please enter a valid maximum time: ";
                    }
                optimizeSchedules(schedules, maxTime);
                break;

                }
            case 7:
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                }
    }
       return 0;
}

class CrowdPredictor {
private:
    std::queue<int> passengerQueue;
    std::vector<int> historicalData;
    int windowSize;
    int currentSum;

public:

    CrowdPredictor(int size) : windowSize(size), currentSum(0) {}

    void addPassengerData(int passengers)
     {

        if (passengerQueue.size() == windowSize)
            {
              currentSum -= passengerQueue.front();
              passengerQueue.pop();
            }

        passengerQueue.push(passengers);
        currentSum += passengers;

        historicalData.push_back(passengers);

    }

    double calculateSMA() const
     {
        if (passengerQueue.empty())
            {

               return 0.0;

            }
         return static_cast<double>(currentSum) / passengerQueue.size();

    }

    int calculateTotalPassengers() const
     {
         int total = 0;
         for (const auto& data : historicalData)
            {
               total += data;
            }
        return total;

    }

    double calculateAveragePassengers() const
    {

        if (historicalData.empty())
            {
              return 0.0;
            }
        return static_cast<double>(calculateTotalPassengers()) / historicalData.size();
    }


    void displayHistoricalData() const
    {

        std::cout << "Historical Data: ";
        for (const auto& data : historicalData)
            {
              std::cout << data << " ";
            }
        std::cout << std::endl;

    }


    void displayCurrentPrediction() const
     {
        std::cout << "Current Crowd Prediction (SMA): " << std::fixed << std::setprecision(2) << calculateSMA() << std::endl;
    }

    void displayTotalPassengers() const
     {
        std::cout << "Total Passengers Recorded: " << calculateTotalPassengers() << std::endl;
     }

    void displayAveragePassengers() const
    {
        std::cout << "Average Passengers: " << std::fixed << std::setprecision(2) << calculateAveragePassengers() << std::endl;
    }

    void displayCurrentQueue() const
    {

        std::cout << "Current Queue State: ";
        std::queue<int> tempQueue = passengerQueue;
        while (!tempQueue.empty())
            {
             std::cout << tempQueue.front() << " ";
             tempQueue.pop();
            }
         std::cout << std::endl;
    }


    int calculateMaxPassengers() const
    {

        if (historicalData.empty())
            {
               return 0;
            }
        int maxPassengers = historicalData[0];
        for (const auto& data : historicalData)
         {

            if (data > maxPassengers)
             {
                maxPassengers = data;
             }
        }
        return maxPassengers;

    }

    int calculateMinPassengers() const
     {

        if (historicalData.empty())
            {
               return 0;
            }

        int minPassengers = historicalData[0];
        for (const auto& data : historicalData)
            {

               if (data < minPassengers)
               {
                  minPassengers = data;
               }
        }
        return minPassengers;

    }

    void displayMaxMinPassengers() const
     {

        std::cout << "Maximum Passengers Recorded: " << calculateMaxPassengers() << std::endl;
        std::cout << "Minimum Passengers Recorded: " << calculateMinPassengers() << std::endl;

    }
};

void displayMenu1()
 {

    std::cout << "\nMenu Options:\n";
    std::cout << "1. Add Passenger Data\n";
    std::cout << "2. Display Historical Data\n";
    std::cout << "3. Display Current Prediction\n";
    std::cout << "4. Display Total Passengers\n";
    std::cout << "5. Display Average Passengers\n";
    std::cout << "6. Display Current Queue State\n";
    std::cout << "7. Display Max and Min Passengers\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option (1-8): ";

}

int crowdManagementSystem()
 {

    int windowSize;
    std::cout << "Enter the size of the sliding window for crowd prediction: ";
    std::cin >> windowSize;

    CrowdPredictor predictor(windowSize);
    int choice;

    do
        {
          displayMenu1();
          std::cin >> choice;

        switch (choice)
         {

            case 1:
                 {
                   int passengers;
                   std::cout << "Enter the number of passengers: ";
                   std::cin >> passengers;
                   if (passengers < 0)
                        {
                           std::cout << "Please enter a non-negative number of passengers." << std::endl;
                        }
                else
                    {
                      predictor.addPassengerData(passengers);
                    }
                break;
            }

            case 2:
                predictor.displayHistoricalData();
                break;

            case 3:
                predictor.displayCurrentPrediction();
                break;

            case 4:
                predictor.displayTotalPassengers();
                break;

            case 5:
                predictor.displayAveragePassengers();
                break;

            case 6:
                predictor.displayCurrentQueue();
                break;

            case 7:
                predictor.displayMaxMinPassengers();
                break;

            case 8:
                std::cout << "Exiting the program. Thank you!" << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
                break;
        }

    }
    while (choice != 8);

    return 0;

}

int busBookingSystem() {
    int mainChoice = 0;
    bool continueProgram = true;

    while (continueProgram) {
        system("cls");  // Clear screen
        cout << "\n\t\t==================================\n";
        cout << "\t\t   INTEGRATED BUS BOOKING SYSTEM\n";
        cout << "\t\t==================================\n\n";
        cout << "\t\t1. Select Bus Route\n";
        cout << "\t\t2. Allocate Seats\n";
        cout << "\t\t3. View Bus Schedules\n";
        cout << "\t\t4. Check Crowd Status\n";
        cout << "\t\t5. Exit\n";
        cout << "\n\t\tEnter your choice (1-5): ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                system("cls");
                bool routeMenu = true;
                while (routeMenu) {
                    routeSelectionSystem();  // Your first code
                    char routeChoice;
                    cout << "\n\t\tDo you want to select another route? (y/n): ";
                    cin >> routeChoice;
                    if (routeChoice != 'y' && routeChoice != 'Y') {
                        routeMenu = false;
                    }
                }
                break;
            }

            case 2: {
                system("cls");
                bool seatMenu = true;
                while (seatMenu) {
                    seatAllocationSystem();  // Your second code
                    char seatChoice;
                    cout << "\n\t\tDo you want to allocate more seats? (y/n): ";
                    cin >> seatChoice;
                    if (seatChoice != 'y' && seatChoice != 'Y') {
                        seatMenu = false;
                    }
                }
                break;
            }

            case 3: {
                system("cls");
                bool scheduleMenu = true;
                while (scheduleMenu) {
                    busScheduleSystem();  // Your third code
                    char scheduleChoice;
                    cout << "\n\t\tDo you want to check more schedules? (y/n): ";
                    cin >> scheduleChoice;
                    if (scheduleChoice != 'y' && scheduleChoice != 'Y') {
                        scheduleMenu = false;
                    }
                }
                break;
            }

            case 4: {
                system("cls");
                bool crowdMenu = true;
                while (crowdMenu) {
                    crowdManagementSystem();  // Your fourth code
                    char crowdChoice;
                    cout << "\n\t\tDo you want to check crowd status again? (y/n): ";
                    cin >> crowdChoice;
                    if (crowdChoice != 'y' && crowdChoice != 'Y') {
                        crowdMenu = false;
                    }
                }
                break;
            }

            case 5: {
                cout << "\n\t\tThank you for using our Bus Booking System!\n";
                continueProgram = false;
                break;
            }

            default: {
                cout << "\n\t\tInvalid choice! Please try again.\n";
                cout << "\t\tPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
    return 0;
}


class TravelBookingSystem {
private:
    string travelType;
    string transportMode;

    bool validateChoice(int& choice, int min, int max) {
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
            return false;
        }
        return true;
    }

public:
    void displayMainMenu() {
        int choice;
        do {
            cout << "\n=== Travel Booking System ===\n"
                 << "1. State to State Travel\n"
                 << "2. City to City Travel\n"
                 << "Enter your choice (1/2): ";

            cin >> choice;
        } while (!validateChoice(choice, 1, 2));

        travelType = (choice == 1) ? "state" : "city";
        displayTransportMenu();
    }

    void displayTransportMenu() {
        int choice;
        if (travelType == "state") {
            do {
                cout << "\nState to State Travel Options:\n"
                     << "1. Flight\n"
                     << "2. Train\n"
                     << "Enter your choice (1/2): ";

                cin >> choice;
            } while (!validateChoice(choice, 1, 2));

            switch (choice) {
                case 1: flightBookingSystem(); break;
                case 2: trainBookingSystem(); break;
            }
        }
        else {
            do {
                cout << "\nCity to City Travel Options:\n"
                     << "1. Bus\n"
                     << "2. Cab\n"
                     << "Enter your choice (1/2): ";

                cin >> choice;
            } while (!validateChoice(choice, 1, 2));

            switch (choice) {
                case 1: busBookingSystem(); break;
                case 2: cabBookingSystem(); break;
            }
        }
    }
};

int main() {
    TravelBookingSystem bookingSystem;
    char continueBooking;

    do {
        bookingSystem.displayMainMenu();

        do {
            cout << "\nDo you want to make another booking? (y/n): ";
            cin >> continueBooking;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');


            if (continueBooking != 'y' && continueBooking != 'Y' &&
                continueBooking != 'n' && continueBooking != 'N') {
                cout << "Invalid input! Please enter 'y' or 'n'\n";
            }
        } while (continueBooking != 'y' && continueBooking != 'Y' &&
                 continueBooking != 'n' && continueBooking != 'N');

    } while (continueBooking == 'y' || continueBooking == 'Y');

    return 0;
}
