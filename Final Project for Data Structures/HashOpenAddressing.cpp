//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

/**
 * Constructs a hash table to be used with quadratic probing
 * @param size, size of the hashtable
*/


HashOpenAddressing::HashOpenAddressing(int size)
{
    hashTableSize = size;
    hashTable = new Course *[hashTableSize];
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = nullptr;
    }
}
/**
 * Destructor, deconstructs the hash table and deletes everything
*/


HashOpenAddressing::~HashOpenAddressing()
{
    if (hashTableSize > 0) {
    for (int i = 0; i < hashTableSize; i++)//deconstructs the table 
    { 
        if(hashTable[i] != nullptr)
        {
            delete hashTable[i];
        }
    }
    delete[] hashTable;
  }
}

/**
 * Calculates the hash for an index
 * @param courseNumber, gets the course number (e.g. 2270)
 * @return int
*/


int HashOpenAddressing::hash(int courseNumber)
{
    return courseNumber % hashTableSize;
}

/**
 * A split function to parse a file
 * @param str, the string to parse
 * @param del, the delimeter to seperate data
 * @param arr, the array of strings to store the seperate data members in
 * @param size, the size of the array
 * @return int
*/


int split(string str, char del, string arr[], int size)
{

    string temp = "";
    int occur = 0;
    int test = 0;


    if(str == "") //test to see if the string is empty
    {
        return 0;
    }


    for(int i = 0; i < (int)str.length(); i++)
    {
        if(str[i] == del)
        {
            test++; //increments test to see if the string has delimiters
        }
    }

    if(!(test > 0))
    {
        arr[0] = str; //returns 1 if none are found and stores the string in the first element
        return 1;
    }



    for(int i = 0; i < (int)str.length(); i++)
    {
        if(str[i] != del)
        {
            temp += str[i]; //if the char is not a delimiter, add it to the temp string
        }
        else if(str[i] == del)
        {
            arr[occur] = temp; //if it is a del, store the substr in the array, clear temp and increment occur
            temp = "";
            occur++;
        }
        else
        {
            arr[occur] = temp; 
            temp = "";
            occur++;
        }
    }

    arr[occur] = temp;
    temp = "";
    occur++; //this is for the part of the string after the last del


    if(occur > size)
    {
        return -1;
    } //returns -1 if the array is not big enough


    return occur;
}

/**
 * Inserts all of the courses and professors into the hash table and the 
 * BSTs.
 * @param filename, the file name to parse through
*/


void HashOpenAddressing::bulkInsert(string filename)
{

    //Variable declaration for files, iteration, probing and storing.
    ifstream ifile;
    int key = 1;
    int hashedIndex = 0;
    int collisions = 0;
    int searches = 0;
    ifile.open(filename);
    string temp;
    string tempName;
    string arr[7];
    if(ifile.is_open())
    {
        int i = 0; //variable used to skip the first line
        while(getline(ifile, temp))
        {
            key = 1;
            if(i == 0)
            {
                i++; //skips the first line
            }
            else
            {
                split(temp, ',', arr, 7); //parses the file
                tempName.append(arr[5]);
                tempName.append(" "); //constructs the name of the professor into one variable
                tempName.append(arr[6]);
                Professor *tempProf;
                 //course declaration
                /*
                    The following if statements insert professors into the BST and secures the professor variable
                */
                if(profDb.searchProfessor(arr[4]) == NULL) //if the professor has not been added yet
                {
                    profDb.addProfessor(arr[4], tempName); //add them to the BST
                    tempProf = profDb.searchProfessor(arr[4]);
                }
                else //else if the professor is found
                {
                    tempProf = profDb.searchProfessor(arr[4]); //sets the temp prof variable
                }
                Course *tempCourse = new Course(stoi(arr[0]), arr[1], stoi(arr[2]), arr[3], tempProf);
                tempProf->coursesTaught.push_back(tempCourse);
                hashedIndex = hash(tempCourse->courseNum); //gets the hash index 
                if(hashTable[hashedIndex] == nullptr) //if the space isnt taken up, insert it into the hash table
                {
                    hashTable[hashedIndex] = tempCourse;
                    searches--;
                }
                else //else, probe it
                {
                    collisions++;
                    searches--;
                    while(hashTable[hashedIndex] != nullptr) //while the spaces are full
                    {
                        hashedIndex = (hashedIndex + key*key) % hashTableSize; //Preform quadratic probing to get the new index
                        key++; //increment key for the probing
                    }
                }
                hashTable[hashedIndex] = tempCourse; 
                searches += key;
            }
            
        }
    }
    cout << "Collisions using open addressing: " << collisions << endl; //display collisions and searches
    cout << "Seach operations using open addressing " << searches << endl; 
}

/**
 * Searches the table for a course
 * @param courseYear, the course year to search
 * @param courseNumber, the course number to search
 * @param profId, the professor's id to search
*/


void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    int index = hash(courseNumber); //gets the hash
    //Variable declaration
    int counter = 0; 
    int searches = 0;
    bool isFound = false;
    Course *curr = hashTable[index]; //gets the current course to find
    if(curr->prof->profId == profId && curr->courseNum == courseNumber && curr->year == courseYear) //if its all equal, set the boolean to true
    {
        isFound = true;
    }
    else
    {
        while(counter < hashTableSize) //while we haven't looped through the whole table 
        {
            counter++; //increment counter
            searches++; //increment searches
            index = (index + (counter * counter)) % hashTableSize; //quadratic probe the index
            curr = hashTable[index];
            if(curr != NULL && (curr->prof->profId == profId && curr->courseNum == courseNumber && curr->year == courseYear)) //if its all equal, set is found to true and break the while
            {
                isFound = true;
                break;
            }
        }
    }
    if(!isFound)
    {
        cout << "Could not find the course" << endl; // if it was not found, output.
    }
    else
    {
        string proof = curr->prof->profName;
        cout << "Search operations using open addressing: " << searches << endl; //if it was found, output the information
        cout << curr->year << " ";
        cout << curr->courseName << " ";
        cout << curr->courseNum << " ";
        cout << curr->prof->profId << endl;
        //cout << curr->prof->profId << endl;
        //For some reason, whenever trying to print the professor's name, it would bug out the entire cout.
        //For this reason, I print out the professor id instead of their name, which seems to print normally.
        

    }
}

/**
 * Displays all the courses and calls displayCourseInfo to display the info
*/


void HashOpenAddressing::displayAllCourses()
{
    for (int i = 0; i < hashTableSize; i++) //loop through thet hash table and call displaycourseinfo
    {
        displayCourseInfo(hashTable[i]);
    }
}

/**
 * Displays course information
 * @param c, the object's data to print
*/


void HashOpenAddressing::displayCourseInfo(Course* c)
{
	cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profId << endl; //prints all of the data
}