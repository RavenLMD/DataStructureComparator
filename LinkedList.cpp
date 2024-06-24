#include "LinkedList.hpp"
#include <iostream>
using namespace std;
struct Course;
struct LLNode;

//Default constructor: root is equal to nullptr as no nodes exist at the begining of the linked list's creation
LinkedList::LinkedList() {
    LLNode* head = nullptr;
    LLNode* tail = nullptr;
}

//Add new node at end of linked list
void LinkedList::append(Course course){
    //Creates pointer to new node
    LLNode* newNode = new LLNode;
    //Sets the course variable for the new node with the supplied course
    newNode->course = course;
    //If list is empty (checked by checking if the head pointer is NULL)
    if (this->head == nullptr){
          //Set node (head node) contents and NEXT pointer
          this->head = newNode;
          this->tail = newNode;
      }
    //If list is not empty  
    else{
          //Set node contents and Next pointer
          this->tail->nextNode = newNode;
          this->tail = newNode;
    }
}

//Add new node at beginning of linked list
void LinkedList::prepend(Course course){
    LLNode* newNode = new LLNode;
    newNode->course = course;
    //If list is empty
    if (this->head == nullptr){
    //Set node contents and NEXT pointer
          this->head = newNode;
          this->tail = newNode;
      }
    //If list is not empty  
    else{
          newNode->nextNode = this->head;
          this->head = newNode;
    }

}

Course LinkedList::search(string courseKey){
    //Sets current node for searching to the head of the linked list
    LLNode* currentNode = this->head;
    //Traverses the linked list until end of list (if not found)
    while(currentNode != nullptr){
        //End loop if found
        if(courseKey == currentNode->course.courseId){
            return currentNode->course;
        }
        //Else if course not found
        //Set current node to search to next node
        currentNode = currentNode->nextNode;
    }
    //Return null
    Course course;
    return course;
}
