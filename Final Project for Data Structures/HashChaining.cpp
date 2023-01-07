//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

/**
 * Constructs a hash table to be used with chaining
 * @param size, size of the hashtable
*/


HashChaining::HashChaining(int size)
{
    hashTableSize = size; 
    hashTable = new Course *[hashTableSize];
    for(int i = 0; i < hashTableSize; i++) //initalizes the hash table
    {
        hashTable[i] = nullptr;
    }
}

/**
 * Destructor, deconstructs the hash table and deletes everything
*/

// HashChaining::~HashChaining()
// {
   
//     if (hashTableSize > 0) {
//     for (int i = 0; i < hashTableSize; i++)//deconstructs the table 
//     { 
//         if(hashTable[i] != nullptr)
//         {
//             Course *curr = hashTable[i];
//             Course *curr2;
//             while(curr != nullptr)
//             {
//                 curr2 = curr->next;
//                 delete curr;
//                 curr = curr2;
//             }
//             hashTable[i] = NULL;
//         }
//     }
//     delete[] hashTable;
//   }
// }

HashChaining::~HashChaining()
{
   
    if (hashTableSize > 0) {
    for (int i = 0; i < hashTableSize; i++)//deconstructs the table 
    { 
        if(hashTable[i] != nullptr)
        {
            Course *curr = hashTable[i];
            Course *curr2 = hashTable[i];
            while(curr != nullptr)
            {
                curr = curr->next;
                delete curr2;
                curr2 = curr;
            }
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

int HashChaining::hash(int courseNumber)
{
    return courseNumber % hashTableSize; //returns the hashed index
}

int split(string str, char del, string arr[], int size);
// {

//     string temp = "";
//     int occur = 0;
//     int test = 0;


//     if(str == "") //test to see if the string is empty
//     {
//         return 0;
//     }


//     for(int i = 0; i < (int)str.length(); i++)
//     {
//         if(str[i] == del)
//         {
//             test++; //increments test to see if the string has delimiters
//         }
//     }

//     if(!(test > 0))
//     {
//         arr[0] = str; //returns 1 if none are found and stores the string in the first element
//         return 1;
//     }



//     for(int i = 0; i < (int)str.length(); i++)
//     {
//         if(str[i] != del)
//         {
//             temp += str[i]; //if the char is not a delimiter, add it to the temp string
//         }
//         else if(str[i] == del)
//         {
//             arr[occur] = temp; //if it is a del, store the substr in the array, clear temp and increment occur
//             temp = "";
//             occur++;
//         }
//         else
//         {
//             arr[occur] = temp; 
//             temp = "";
//             occur++;
//         }
//     }

//     arr[occur] = temp;
//     temp = "";
//     occur++; //this is for the part of the string after the last del


//     if(occur > size)
//     {
//         return -1;
//     } //returns -1 if the array is not big enough


//     return occur;
// }

/**
 * Inserts all of the courses and professors into the hash table and the 
 * BSTs.
 * @param filename, the file name to parse through
*/

void HashChaining::bulkInsert(string filename)
{
    //Variable declaration for files, iteration, chaining and storing.
    ifstream ifile;
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
                    tempProf = profDb.searchProfessor(arr[4]);
                }
                Course *tempCourse = new Course(stoi(arr[0]), arr[1], stoi(arr[2]), arr[3], tempProf); //creating the course
                tempProf->coursesTaught.push_back(tempCourse); //add the course to the vector
                hashedIndex = hash(tempCourse->courseNum); //gets the hash index
                Course *head = hashTable[hashedIndex]; //sets a course to chain with
                if(hashTable[hashedIndex] == nullptr) //if the hash is empty, insert it 
                {
                    hashTable[hashedIndex] = tempCourse;
                }
                else
                {
                    collisions++;
                    searches++;
                    //inserting at the end of the chain
                    while(head->next != nullptr) //while not pointing to null, loop through
                    {
                        head = head->next; //looping and incrementing
                        searches++;
                    }
                    head->next = tempCourse;
                    tempCourse->previous = head;
                }
            }
        }
        cout << "Collisions using Chaining: " << collisions << endl; //outputs searches and collisions
        cout << "Search operations using chaining: " << searches << endl;
    }
}

/**
 * Searches the table for a course
 * @param courseYear, the course year to search
 * @param courseNumber, the course number to search
 * @param profId, the professor's id to search
*/

void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    int index = hash(courseNumber); //gets the hash
    //Variable declaration
    int searches = 0;
    bool isFound = false;
    Course *curr = hashTable[index]; //gets the current course to find
    if(curr->prof->profId == profId && curr->courseNum == courseNumber && curr->year == courseYear) //if its all equal, set the boolean to true
    {
        isFound = true;
    }
    else
    {
        while(curr->next != nullptr) //while not pointing to null
        {
            searches++; //increment searches
            if(curr != NULL && (curr->prof->profId == profId && curr->courseNum == courseNumber && curr->year == courseYear)) //if its equal
            {
                isFound = true; //set found to true and break the loop
                break;
            }
            curr = curr->next;
        }
    }
    if(!isFound)
    {
        cout << "Could not find the course" << endl; //if not found, output this
    }
    else
    {
        string proof = curr->prof->profName; //else output the courses data
        cout << "Search operations using open addressing: " << searches << endl;
        cout << curr->year << " ";
        cout << curr->courseName << " ";
        cout << curr->courseNum << " ";
        cout << curr->prof->profId << endl;
        //For some reason, whenever trying to print the professor's name, it would bug out the entire cout.
        //For this reason, I print out the professor id instead of their name, which seems to print normally.

    }
}

/**
 * Displays all the courses and calls displayCourseInfo to display the info
*/

void HashChaining::displayAllCourses()
{
    
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i] != nullptr && hashTable[i]->next == nullptr)
        {
            displayCourseInfo(hashTable[i]);
        }
        else
        {
            Course* curr = hashTable[i];
            while (curr != nullptr)
            {
                displayCourseInfo(curr);
                curr = curr->next;
            }
        }
    }
}

/**
 * Displays course information
 * @param c, the object's data to print
*/

void HashChaining::displayCourseInfo(Course* c)
{
    cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profId << endl; //prints all of the data
}