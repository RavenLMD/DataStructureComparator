#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <string>
#include <algorithm>
#include <vector>
#include "Course.hpp"

//struct Course;
struct LLNode{
    Course course;
    LLNode *nextNode = nullptr;
};

class LinkedList {
        public:
                LinkedList();
                void append(Course course);
                void prepend(Course course);
                Course search(std::string courseKey);
                int test();
                LLNode* head;
                LLNode* tail;
};
#endif
