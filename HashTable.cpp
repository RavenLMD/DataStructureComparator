#include "HashTable.hpp"

#include "LinkedList.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//CONSTRUCTOR
HashTable::HashTable(int bucketCount, int collisionAlgInt){
        vector<LinkedList> tableContents (bucketCount);
        int collisionAlg = collisionAlgInt;
        this->collisionAlg = collisionAlg;

        LinkedList emptyLL;
        emptyLL.head = nullptr;
        
        fill(tableContents.begin(), tableContents.end(), emptyLL);

        this->tableContents = tableContents;
        
        this->bucketCount = bucketCount;
}

//Collisions
//Add to hash table using chaining
void HashTable::chaining(Course course){
        Course searchedCourse = this->chainingSearch(course.courseId);

        //if course not found
        if(searchedCourse.courseId.empty()){
            LinkedList bucketForInsertion = this->tableContents.at(this->moduloHash(course.courseId));

            LLNode* newNode = new LLNode;
            newNode->nextNode = nullptr;
            newNode->course = course;

            //Add to bucket
            this->tableContents.at(this->moduloHash(course.courseId)).append(course);
        }
}

//Add to hash table using linear probing
void HashTable::linearProbing(Course course){
    int bucketIndex = moduloHash(course.courseId);
    int bucketsProbed = 0;

    while(bucketsProbed < this->bucketCount){
            if(this->tableContents[bucketIndex].head == nullptr){
                tableContents[bucketIndex].append(course);
                return;
            }
            //Increment index of buckets
            bucketIndex = (bucketIndex + 1) % this->bucketCount;
            bucketsProbed++;
    }    
    //If no free buckets
    cout << "Could not add" << endl;
}

Course HashTable::search(string key, int collisionAlgInt){
        Course course;
        switch(collisionAlgInt){
        case 1:
                course = chainingSearch(key);
                return course;
        case 2:
                course = LPSearch(key);
                return course;
       
        }
        return course;
}

//Search with chaining
Course HashTable::chainingSearch(string courseKey){
    LinkedList bucketForSearching = this->tableContents[this->moduloHash(courseKey)];

    //Searches linked list bucket by courseKey
    Course foundCourse = bucketForSearching.search(courseKey);
    return foundCourse;
}

//Linear probing search
Course HashTable::LPSearch(string courseKey){
    int bucketIndex = moduloHash(courseKey);
    int bucketsProbed = 0;

    //Search with linear probing
    while((this->tableContents[bucketIndex].head != nullptr) && (bucketsProbed < this->bucketCount) ){
            if((this->tableContents[bucketIndex].head != nullptr) && (tableContents[bucketIndex].head->course.courseId == courseKey)){
            return tableContents[bucketIndex].head->course;
        }
            //Increment index of buckets
            bucketIndex = (bucketIndex + 1) % bucketCount;
            bucketsProbed++;
    }   
    //Return empty course if not found
    Course course;
    return course;
}

//Hash function
int HashTable::moduloHash(string courseKey){
        //turn courseCode into int
        int number = courseKey[1] * courseKey[4]; 
        return number % 10;//this->bucketCount;
}


