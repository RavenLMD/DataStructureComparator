#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <string>
#include <algorithm>
#include <vector>
#include "Course.hpp"
//Declarations
struct Node{
    Course course;
    //Creates pointers to parents and children
    Node *leftNode = nullptr;
    Node *rightNode = nullptr;
    Node *parentNode = nullptr;
};

//Binary Search Tree class definition
class BinarySearchTree {
    public:
        BinarySearchTree();
        //virtual ~BinarySearchTree();
        void InOrder(Node* node);
        void Insert(Course course);
        void Remove(std::string courseKey);
        Course Search(std::string courseKey);
        void InOrder();
        Node* root;
};
#endif
