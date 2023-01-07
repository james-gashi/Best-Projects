//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

/**
    Constructor, initalizes the root to a nullptr.
*/

ProfBST::ProfBST()
{
    root = nullptr;
}

/**
    Destructor helper, deletes all professor objects
    @param Professor object
*/

void fireProfs(Professor* curr)
{
    if(curr != NULL)
    {
        fireProfs(curr->left);
        fireProfs(curr->right);

        delete curr;
        curr = NULL;
    }
}

/**
    Destructor, deletes all professor objects
*/

ProfBST::~ProfBST()
{
    fireProfs(root);
}

/**
    A helper to add professor objects to the BST.
    @param currNode, a professor object to loop through the BST
    @param profident, the passed professor ID
    @param profN, passed professor name
    @return The added professor
*/

Professor* addProfHelper(Professor* currNode, string profident, string profN)
{
    if(currNode == NULL){
        //return createNode(data);
        Professor* prof = new Professor(profident, profN);
        return prof;
    }
    else if(currNode->profId < profident){
        currNode->right = addProfHelper(currNode->right, profident, profN);
    }
    else if(currNode->profId > profident){
        currNode->left = addProfHelper(currNode->left, profident, profN);
    }
    return currNode;

}

/**
    Adds a professor object with the helper
    @param profID, the professor's ID
    @param profName, the professor's name
*/

void ProfBST::addProfessor(string profId, string profName)
{
    root = addProfHelper(root, profId, profName);
}

/**
    A helper for getting a professor from the BST
    @param curr, a professor object used to traverse the BST
    @param profident, the professor's ID
    @return returns the professor we're looking for
*/


Professor* getProfHelper(Professor* curr, string profident)
{
    if(curr == NULL)
    {
        return NULL;
    }
    if(curr->profId < profident)
    {
        return getProfHelper(curr->right, profident);
    }
    if(curr->profId > profident)
    {
        return getProfHelper(curr->left, profident);
    }
    return curr;
}

/**
 * Searches the BST for a professor to return
 * @param profId, the ID of the professor we want
 * @return the professor
*/


Professor* ProfBST::searchProfessor(string profId)
{
    return getProfHelper(root, profId);
}

/**
 * Calls the search function to find the professor, and passes it to displayProfessorInfo to display the information
 * @param profId, the professor's ID
*/


void ProfBST::publicSearchProfessor(string profId)
{
    Professor *curr = searchProfessor(profId);
    displayProfessorInfo(curr);
}

/**
 * displays the professor's information
 * @param p, the professor who we take the info from
*/


void ProfBST::displayProfessorInfo(Professor* p)
{
    if(p == NULL)
    {
        cout << "Professor not found" << endl; //if the professor is not found, display this message and end the function
        return;
    }
    cout << "Name: " << p->profName << endl; //display the name
    for(int i = 0; i < p->coursesTaught.size(); i++) //loop through the vector and print the courses the professor teaches
    {
        cout << "- " << p->coursesTaught.at(i)->courseNum << ": " << p->coursesTaught.at(i)->courseName << ", " << p->coursesTaught.at(i)->year << endl;
    }
}
