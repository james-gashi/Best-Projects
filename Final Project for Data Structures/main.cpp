//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/*
    
*/

int main (int argc, char* argv[])
{
    /*
    A try and catch statement to test if the input is correct.
    */
    try
    {
        stoi(argv[2]);
    }
    catch(exception &err)
    {
        cout << "Invalid number of arguents." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return 0;
    }
    /*
    Neccessary variable declarations
    */
    string temp1;
    string temp2;
    string temp3;
    HashOpenAddressing open(stoi(argv[2]));
    HashChaining chain(stoi(argv[2]));
    int choice = 0;
    /*
    A do-while loop which runs the menu.
    I chose a do while instead of a regular while
    so that it is guarenteed to run once to prevent
    errors.
    */
    do
    {
        cout << "=======Main Menu=======\n" << endl;
        cout << "1. Populate hash tables" << endl;
        cout << "2. Search for a course" << endl;
        cout << "3. Search for a professor" << endl;
        cout << "4. Display all courses" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
        /*
        A switch statement that handles the main menu choices.
        */
        switch (choice)
        {
            /*
            If the choice was 1, populate the hash tables.
            */
        case 1:
            cout << "[OPEN ADDRESSING] Hash table populated\n" << "--------------------------------------" << endl;
            open.bulkInsert(argv[1]);
            cout << "[CHAINING] Hash Table Populated\n" << "-------------------------------" << endl;
            chain.bulkInsert(argv[1]);
            break;
            /*
            If the choice was 2, prompt the user to input
            the necessary info and search for the course.
            */
        case 2:
            cout << "Enter the course year (e.g. 2021):" << endl;
            cin >> temp1;
            cout << "Enter a course number  (e.g. 2270):" << endl;
            cin >> temp2;
            cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
            cin >> temp3;
            cout << "[OPEN ADDRESSING] Search for a course\n" << "---------------------------------" << endl;
            open.search(stoi(temp1), stoi(temp2), temp3);
            cout << "[CHAINING] Search for a course\n" << "---------------------------------" << endl;
            chain.search(stoi(temp1), stoi(temp2), temp3);
            break;
            /*
            If the choice was 3, ask for the professor's ID,
            search for the professor and then present the information.
            */
        case 3:
            cout << "Enter a Professor's ID (e.g. nscollan0):" << endl;
            cin >> temp1;
            cout << "[OPEN ADDRESSING] Search for a professor\n" << "---------------------------------" << endl;
            open.profDb.publicSearchProfessor(temp1);
            break;
            /*
            If the choice was 4, ask the user their preferred hashing method,
            and display all the courses using that method.
            */
        case 4:
            cout << "Which hash table would you like to display courses for (O = Open Addressing, C = Chaining)?" << endl;
            cin >> temp1;
            if(temp1 == "O" || temp1 == "o")
            {
                cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
                open.displayAllCourses();
            }
            else if(temp1 == "C" || temp1 == "c")
            {
                cout << "[CHAINING] displayAllCourses()" << endl;
                chain.displayAllCourses();
            }
            break;
            /*
            If the choice was anything else, default to exiting the code.
            */
        default:
            if(choice != 5)
            {
                choice = 5;
                cout << "Please enter a number from one to five" << endl;
            }
            break;
        }
    } while (choice != 5);

    return 0;
}