#include "BinarySearchTree.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "CSVparser.hpp"

using namespace std;
//Struct for holding courses read from csv file
struct Course;
//Internal structure for tree node
struct Node;

//Default constructor: root is equal to nullptr as no nodes exist at the begining of the tree's creation
BinarySearchTree::BinarySearchTree() {
    Node* root = nullptr;
}

//Traverse the tree in order recursively
void BinarySearchTree::InOrder(Node* node) {
	if (node == nullptr){
		return;
	}
    //Recursively check left nodes
	this->InOrder(node->leftNode);
	cout << node->course.title << " " << node->course.courseId << " ";
	for(int i=0; i < node->course.prerequisites.size(); i++){
          if(i==0){
               cout << "Prerequisites: ";
          }
          cout << node->course.prerequisites.at(i) << " ";
     }
     cout << endl;
     //Recursively check right nodes
     this->InOrder(node->rightNode);
}

//Insert a bid
void BinarySearchTree::Insert(Course course) {
    Node* node = new Node;
    node->course = course;
    //Adds root
	if(this->root == nullptr){
		this->root = node;
		
        node->leftNode = nullptr;
		node->rightNode = nullptr;
	}
	else{
		//Begins at root of tree
		Node* currNode  = this->root;
        //Loops until null pointer is found and then inserts
		while(currNode != nullptr){
            //Compares nodes, else searches children
			if(node->course.courseId < currNode->course.courseId){
				if(currNode->leftNode == nullptr){
					currNode->leftNode = node;
					currNode = nullptr;
				}
				else{
					currNode = currNode->leftNode;
				}
                }
			else{
				if(currNode->rightNode == nullptr){
					currNode->rightNode = node;
					currNode = nullptr;
                 } 
                 else{
				    currNode = currNode->rightNode;
                 }
            }
        }
    }
}	
//Remove a course
void BinarySearchTree::Remove(string courseKey) {
	//nullptr because the root has not parent
	Node* parentNode = nullptr;
	Node* currNode = this->root;

	while(currNode != nullptr){

		//If node found
		if(currNode->course.courseId == courseKey){
   			//If no children
			if(currNode->leftNode == nullptr && currNode->rightNode == nullptr){
				//If the parent is a null pointer because currNode is the root
				if(parentNode == nullptr){
					this->root = nullptr;
				}
				else if(parentNode->leftNode == currNode){
					parentNode->leftNode = nullptr;
				}
				else{
					parentNode->rightNode = nullptr;
				}
			}
			//Remove node with just a left child
			//Replaces node with child
			else if(currNode->rightNode == nullptr){
				if(parentNode == nullptr){
					this->root = currNode->leftNode;
				}
				else if(parentNode->leftNode == currNode){
					parentNode->leftNode = currNode->leftNode;
				}
				else{
					parentNode->rightNode = currNode->leftNode;
				}
			}
			//Remove node with just a right child
			//Replaces node with child
			else if(currNode->leftNode == nullptr){
				if(parentNode == nullptr){
					this->root = currNode->rightNode;
				}
				else if(parentNode->leftNode == currNode){
					parentNode->leftNode = currNode->rightNode;
				}
				else{
					parentNode->rightNode = currNode->rightNode;
				}
			}
			//Removes node with both left and right children
			else{
				//The successor is the leftmost child of the right node
				Node* successorNode = currNode->rightNode;
				while(successorNode->leftNode != nullptr){
                    
	                cout << "3" << endl;
					successorNode = successorNode->leftNode;
				}
			Node* successorCopy = successorNode;

            //Remove successor node and resplace current node with its data
			this->Remove(successorNode->course.courseId);
			currNode->course = successorCopy->course;
			}
			//Return upon removal
			return;
		}
		//Search from right node
		else if(currNode->course.courseId < courseKey){
			parentNode = currNode;
			currNode = currNode->rightNode;
		}
		//Search from left node
		else{
			parentNode = currNode;
			currNode = currNode->leftNode;
		}
	}
	//This happens if the node is not found
	cout << "Node not found: " << endl;
	return;
}

//Search for a course in binary search tree using the same logic as removal, but returning a course object rather than deleting one
Course BinarySearchTree::Search(string courseId) {
	Node* currentNode = this->root;
	while(currentNode != nullptr){
		if(courseId == currentNode->course.courseId){
			return currentNode->course;
		}
		else if(courseId < currentNode->course.courseId){
			currentNode = currentNode->leftNode;
		}
		else{
			currentNode = currentNode->rightNode;
		}
		//Course not found	
	}
    Course course;
    return course;
}


