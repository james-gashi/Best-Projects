<img src="https://www.colorado.edu/cs/profiles/express/themes/ucb/images/cu-boulder-logo-text-black.svg" alt="CU Boulder Logo" width="500">

# CSCI 2270: Data Structures <br/> University Courses Database Project

## Introduction
The objective of this project is to write an application that reads a list of University courses from a data file and then inserts them into two separate hash tables. The first hash table will use the Open Addressing collision resolution scheme and the second hash table will use the Chaining collision resolution scheme. Users should be able to search the hash tables for a specific course number or display all of the courses. It’s your objective to compare and contrast the hashing collision resolution methods. Additionally, the application should maintain a list of courses taught by each professor by using a binary search tree data structure. Users should be able to search for a professor and view all of the courses taught by the Professor.

## Getting Started
1. Download the project pdf writeup located within this starter repo.<br/>
2. Download the PowerPoint slide deck [Getting Started With GitHub Classroom Workflow](https://docs.google.com/presentation/d/1B0yZb6twQ_NVL8PripCL7AkeIKSrR8_M/edit?usp=sharing&ouid=115561230768383364768&rtpof=true&sd=true).<br/>
3. Download the [GitHub presentation slide deck](https://drive.google.com/file/d/12mMxMGRrpnkSuz08FUlvkhC-9WJ4JHns/view?usp=sharing) created by Asa Ashraf.<br/>
4. View the GitHub lecture videos [Part I](https://drive.google.com/file/d/1P4iqEbt9Nx68-Nq0FxxpdBZCrbkx5cN3/view?usp=sharing) and [Part II](https://drive.google.com/file/d/1EFYq_qJsV3QNcx_W86nz2KFpQUhSn9jF/view?usp=sharing) given by Asa Ashraf.

## Disclaimer
Students are not allowed to share this code or make it public at any time, even after the course has completed.


## README Post-production edits
1. I think that chaining collision resolution is much better than quadratic probing. The real point of difference is that with chaining
you can insert new items at the head of the linked list, which is much faster than popping around the hash table with quadratic probing.
When you set up chaining to insert at the tail is when its a closer competition between chaining and quadratic probing. 

2. The BST is the best data structure for that kind of organization, however one could use priority queues with max heaps to
prioritize professors with higher amounts of courses, which would slightly improve on searching for more popular professors
but the BST is best for searching for any kind of professor.

3. I could probably utilize recursion more throughout the program in order to cut down on any processing time. Besides this, focusing on
one collision resolution strategy would decrease the overall bloat of the program, which would be optimal if working in a job-like setting.
