#include <iostream>
#include <time.h>
#include <algorithm>
#include <cstring>
#include "CSVparser.hpp"

#include <limits>

#include "LinkedList.hpp"
#include "BinarySearchTree.hpp"
#include "HashTable.hpp"

#include <vector>


//Standard namespace
using namespace std;

//Forward declaration
double strToDouble(string str, char ch);

//Display the bid information to the console (std::out)
//@param course struct containing the course
void displayCourse(Course course) {
     cout << course.title << " " << course.courseId << " ";
	//Prints prerequisites if present
     for(int i=0; i < course.prerequisites.size(); i++){
          if(i==0){
               cout << "Prerequisites: ";
          }
          cout << course.prerequisites.at(i) << " ";
     }
     cout << endl;
     return;
}

//Loads a CSV file containing academic courses 
//@param csvPath the path to the CSV file to load
//@return a container holding all the courses read
void loadCourses(string csvPath, BinarySearchTree* bst, LinkedList* linkedL, HashTable* hashTableChaining, HashTable* hashTableLinearProbing) {
    //Initialize the CSV Parser using the given path
    cout << "Loading CSV file " << csvPath << endl;
    csv::Parser file = csv::Parser(csvPath);
    int j = 2;
    string check;
    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            // Create a data structure and add to the collection of bids
            Course course;
            course.courseId = file[i][0];
            course.title = file[i][1];
            j = 2;
            check = file[i][2];
            while(j < file[i].size()){
               //Checks to see if there are any prerequisites
               if(check < "NOPREREQ" != 0){
                    course.prerequisites.push_back(file[i][j]);
               }
               j++;
            }
            bst->Insert(course);
            linkedL->append(course);
            hashTableChaining->chaining(course);
            hashTableLinearProbing->linearProbing(course); 
        }
    } 
    catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

//Simple C function to convert a string to a double after stripping out unwanted char
//credit: http://stackoverflow.com/a/24875936
//@param ch The character to strip out
 double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

//The one and only main() method
int main(int argc, char* argv[]) {
    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "Table";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    //Default values if no command line arguments are given
    default:
        csvPath = "courses.csv";
        courseKey = "CSCI400";
    }

    //Define a timer variable
    clock_t ticks;
    //Define a binary search tree, linked list, and two hash tables to hold all bids
    //Binary search tree
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    //Linked list
    LinkedList* linkedL;
    linkedL = new LinkedList();
    //Hash table chain
    HashTable* hashTableChaining;
    hashTableChaining = new HashTable(200/*10*/, 1);
    //Hash table linear probing
    HashTable* hashTableLinearProbing;
    hashTableLinearProbing = new HashTable(200/*10*/, 2);
    
    Course course;
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load classes" << endl;
        cout << "  2. Display All Classes" << endl;
        cout << "  3. Find Class" << endl;
        cout << "  4. Remove From BST" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        
        //Catches input errors (non-integers) and reprints menu
        while (!(cin >> choice)) {
            cout << "\nInvalid option (non-integer) \n\n";
            cout << "Menu:" << endl;
            cout << "  1. Load classes" << endl;
            cout << "  2. Display All Classes" << endl;
            cout << "  3. Find Class" << endl;
            cout << "  4. Remove From BST" << endl;
            cout << "  9. Exit" << endl;
            cout << "Enter choice: ";

            //clears cin flag to allow for reuse
            cin.clear();
            //discards last cin input
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        //Load classes
        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();
            // Complete the method call to load the bids
            loadCourses(csvPath, bst, linkedL, hashTableChaining, hashTableLinearProbing);
            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        //Display classes
        case 2:
            bst->InOrder(bst->root);
            break;

        //Search class
        case 3:
            cout << "Please enter the course number: ";
            cin >> courseKey;

            //Searches for course and records amount of time taken, outputting time taken
            cout << endl << "Binary search tree" << endl;
            ticks = clock();
            course = bst->Search(courseKey);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            //Linked List

            cout << "Linked list" << endl;
            ticks = clock();
            linkedL->search(courseKey);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            //Hash table with chaining

            cout << "Hash table with chaining" << endl;
            ticks = clock();
            hashTableChaining->search(courseKey, 1);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            //Hash table with linear probing

            cout << "Hash table with linear probing" << endl;
            ticks = clock();
            course = hashTableLinearProbing->search(courseKey, 2);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            //If course found
            if (!course.courseId.empty()) {
                displayCourse(course);
              //If course not found
            } else {
            	cout << "Course Id " << courseKey << " not found." << endl;
            }
            break;

        //Removes course from binary search tree
        case 4:
            cout << "Please enter the course number: ";
            cin >> courseKey;

            cout << "Binary search tree" << endl;
            ticks = clock();
            bst->Remove(courseKey);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        //Catches invalid integer input
        default:
            if (choice != 9){
            cout << "\nInvalid integer\n\n";
            }
            break;
        }
        
      
    }
    cout << "Good bye." << endl;
	return 0;
}
