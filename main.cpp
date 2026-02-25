// Bonnie Rott
// 24 Jan 2026
// CS 210 
// gonna make a 2 clock system, 24 hour and 12 hour with spacing, AM and PM, and a menu with options to change the time and exit




#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#include <sstream> // inputs to make sure code works, including inputs from visual studio code to make sure this file will run properly



using namespace winrt;
using namespace Windows::Foundation; 
using namespace std; //set of standard library names for what visual code wants me to use

// time to set up menu selection choices, as per the example we want 1 through 4 to add time, and to exit
const int LOWEST_VALID_SELECTION = 1; // minimum menu selection option
const int HIGHEST_VALID_SELECTION = 4; // maximum menu selection option
const int EXIT_SELECTION = HIGHEST_VALID_SELECTION;  // the highest menu selection option also lets you exit the menu
const int CLOCK_WIDTH = 26; //display format for spacing and such

struct TimeClock {    // going to create our clock as well as determine our integers and related strings 
	int hour = 0; // wil hold hours (set for 24 hour format, can hold up to 23) 
	int minute = 0; // will hold minutes
	int second = 0; // will hold seconds 
	string ampm = "AM"; // holds values of AM or PM if clock is 12 hours rather than 24 

	TimeClock() = default;
}; // end of clock structuring

void displayMenu();
string createMenuItem(string, int);
int getMenuSelection(const string&);
void processSelection(int, TimeClock&);
struct TimeClock getInitialTime();
int getInteger(string, int, int);
int getInteger(string);
bool isIntReg(string);
void clearScreen();
// initialize the menu, selection functions, and the clocks, set functions for string and integer inputs

// time for our sets and gets, they're going to look kind of like this for our display for the clock, and then we want to take those and turn them into increments and displays, so we would take; 
// "void setHour(int);
// void setMinute(int);
// void setSecond(int);
// int getHour();
// int getMinute();
// int getSecond();" 
// and try to turn that into 
void incHour(TimeClock&);
void incMinute(TimeClock&);
void incSecond(TimeClock&);
void displayClock(TimeClock&);
void displayClock12(TimeClock&);
void displayClock24(TimeClock&);
string centerText(string text, int length, char fill);
// so we can set up our increments and displays for both clocks

int main() {
	int selection = 0; // to store users menu selection
	struct TimeClock theTime; // stores our time in hours minutes and seconds
	theTime = getInitialTime(); // gonna get our beginning time numbers


	do { // loop that will continue until we use the exit option
		displayClock(theTime);
		selection = getMenuSelection("Please, make your selection "); // asks user for menu input
		if (selection != EXIT_SELECTION) {
			clearScreen(); // clear da window
			processSelection(selection, theTime); // process user selection
		}

	} while (selection != EXIT_SELECTION);
	return 0;

} // end main I think, lets move forward 

void displayMenu()
{
	int numStars = 25;
	string stars(numStars, '*');
	unsigned i = 0; // star border 

	cout << stars << endl;
	cout << createMenuItem((to_string(++i) + " - Add one hour"), numStars) << endl; // first menu item
	cout << createMenuItem((to_string(++i) + " - Add one minute"), numStars) << endl; // second menu item
	cout << createMenuItem((to_string(++i) + " - Add one second"), numStars) << endl; // third menu item
	cout << createMenuItem((to_string(++i) + " - End program and exit"), numStars) << endl; // fourth menu item and exit options
	cout << stars << endl;
} 
// that displays our menu, adds our star border, and should show the menu the way it's shown in the example from class 

string createMenuItem(string menuItem, int itemLength)
{
	int menuItemLength = menuItem.length();
	int spacesNeeded = (itemLength - menuItemLength - 3); // removing length by 3 allows for padding, stars and adqeuate spacing

	string spaces(spacesNeeded, ' ');
	menuItem = "* " + menuItem + spaces + '*';
	return menuItem;
} // we've gotten the menu padding situated so the menu items should all be set up very similarly to the example

int getMenuSelection(string prompt) //what happens when we use the menu selection function
{
	bool needSelection = false;
	int selection = 0;

	do {
		displayMenu();
		cout << prompt;
		cin >> selection;
		needSelection = ((selection < LOWEST_VALID_SELECTION) || (selection > HIGHEST_VALID_SELECTION)); // menu selection needs to fall between 1 and 4, or our existing menu options
		if (needSelection) {
			cout << "Invalid, please enter again" << endl; // invalid message, user must input valid selection
		}
	} while (needSelection);
	return selection; // if an invalid item is selected, this is what the user will have return to them until they choose a valid menu option
}

void processSelection(int selection, TimeClock& oneClock)
{
	switch (selection) {
	case 1:
		incHour(oneClock); // increment hour function
		break; // 
	case 2:
		incMinute(oneClock); // increment minute function
		break;
	case 3:
		incSecond(oneClock); // increment second function
		break;
	case 4:
		break;
	default:
		cout << "goodbye"; // should never reach here
	}
} // now we know what happens for each menu selection option

TimeClock getInitialTime()
{
	TimeClock theTime;
	// cout << "Please enter the hour " << endl;
	theTime.hour = getInteger("please enter the hour:", 0, 23);
	// cout << "Please enter the minute " << endl;
	theTime.minute = getInteger("please enter the minute:". 0, 59);
	// cout << "Please enter the second " << endl;
	theTime.seconds = getInteger("please enter the second", 0, 59);
	theTime.ampm = (theTime.hour >= 12) ? "PM" : "AM";

	return theTime; // this will help us get the initial time, and asks for user input so that we can set the clock before using the menu options, time should be returned after all values are input
}

int getInteger(string prompt, int lowest, int highest)
{
	int number = 0;
	bool needNumbree = true;

	prompt = prompt + " between " + to_string(lowest) + " and " + to_string(highest) + " "; // values have to be within our clock related number range
	do {
		number = getInteger(prompt);

		meedNumber = ((number < lowest) || (number) > highest)); // number has to be within range or an error occurs
		if (needNumber) {
			cout << "\a Invalid entry, please try again" << endl; // message for invalid entry
		}
	} while (needNumber);


	return number;
} 

int getInteger(string prompt) // to get the time, we need values for hour, minute, and second
{
	bool needInteger = true;
	string strNum = " ";

	do {
		cout << prompt;
		getline(cin, strNum);
		needInteger = !isIntReg(strNum);
		if (needInteger) {
			cout << "\aPlease type a valid number" << endl; // we can input whatever time we want, as long as the input range is valid
		}
	} while (needInteger);
	return stoi(strNum);
}

bool isIntReg(string num)
{
	regex intExpression("^[+|-]?[0-9]+$"); // our numbers are within a range, so we need to set up a regex expression to make sure the input is valid (all numbers between 0 and 9), as well as accounting for the existence of negative numbers and positive numbers

	return regex_match(num, intExpression); // returns true if the input matches the regex expression (we won't have luck with using other character or symbols outside of what our regex allows)

}

void clearScren()
{
	cout << "\033[2J\033[1;1H"; // clears our screen
}

// we need to set increment conditions for the hours, minutes, and seconds as well as an AM/PM condition for the 12 hour clock
void incHour(TimeClock& oneClock) // increment hour function
{
	oneClock.hour++;
	if (oneClock.hour >= 24) {
		oneClock.hour %= 24; // resets hour to 0 after reaching 24
	}

	// oneClock.hour >= 12 ? ampm = "PM" : ampm = "AM"; gives us the AM/PM condition
	oneClock.ampm = (oneClock.hour >= 12) ? "PM" : "AM"; // AM/PM condition for 12 hour clock
}

void incMinute(TimeClock& oneClock) // increment minute function
{
	oneClock.minutes++;
	if (oneClock.minute == 60) {
		incHour(oneClock);
		oneClock.minute = 0;
	}
}

void incSecond(TimeClock& oneClock) // increment second function
{
	oneClock.second++;
	if (oneClock.secon 60) {
		incMinute(oneClock);
		oneClock.second = 0;
	}
}

// now it's time to get more into the display abilities, spacing, and formatting of the clocks
void displayClock(TimeClock& oneClock) // time to add our stars, spacers and position our clocks
{
	ostringstream oss;

	string stars(CLOCK_WIDTH, '*'); //character for spacers, the stars
	const int SPACER_SIZE = 5;
	const string SPACER(SPACER_SIZE, ' '); // gives us room between both clocks 
	string hour12Text = "12 Hour Clock"; //our 12 hour clock
	string hour24Text = "24 Hour Clock"; // our 24 hour clock
	string clockString = "";  // display function 
	int hour12 = 0;

	hour12 = ((oneClock.hour % 12) == 0) ? 12 : (oneClock.hour % 12); // sets our 12 hour clock so the am and pm will match

	cout << stars << SPACER << stars << endl; // star format 
	cout << "*" << centerText(hour12Text, (CLOCK_WIDTH - 2), ' ') << "*"; // 12 hr format
	cour << SPACER;
	cout << "*" << centerText(hour24Text, (CLOCK_WIDTH - 2), ' ') << "*" << endl;

	oss << fixed << setw(2) << setfill('0') << hour12 << ":" << setw(2) << oneClock.minute << ":" << setw(2) << oneClock.second << oneClock.ampm
		clockString = oss.str();
	cout << "*" << centerText(clockString, (CLOCK_WIDTH - 2), ' ') << "*";
	cout << SPACER;
	oss.str("");
	oss << fixed << setw(2) << setfill('0') << oneClock.hour << ":" << setw(2) << oneClock.minute << ":" setw(2) << oneClock.second;
	clockString = oss.str();
	cout << "*" << centerText(clockString, (CLOCK_WIDTH - 2), ' ') << "*" endl;
	cout << stars << SPACER << stars << endl;
} // this should display both clocks with proper spacing and formatting, as well as display our borders and allow for the clocks to be centered

string centerText(string text, int length, char fill = ' ') {


	int textLength = text.length();
	string centeredText = " "; // for our text to be centered

	if (textLength >= length) {
		return text;
	}
	else {
		int charsNeeded = (length - textLength); 
		int paddingNeeded = (charsNeeded / 2); // padding needed on each side
		string leftPadding = string(paddingNeeded, fill);
		string rightPadding = leftPadding; // right padding same as left padding
		centeredText = (leftPadding + text + rightPadding); // centered text with padding

		if (charsNeeded % 2 != 0) {
			centeredText.insert(0, 1, fill);
		}
		// cout << text.length() << endl << centeredText.length() << endl << leftPadding << endl << rightPadding << endl;
		return (centeredText);
	}
}
// I am pretty sure that now, our clocks will display the way they are supposed to, we will have both 12 and 24 hour clocks, correct padding, and the ability to use the menu function to change hours, minutes, and seconds as well as exit our program entirely.
// 