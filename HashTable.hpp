#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "Course.hpp"
#include <vector>
#include <LinkedList.hpp>

//struct HTNode{

//};

//vetor bucket
//struct bucket{
//    int indexKey;
    //vector<Course> bucketContents;
//}


class HashTable{
    public:
            HashTable(int bucketCount, int collisionAlgInt);

            void chaining(Course course);
            void linearProbing(Course course);
            //void quadraticProbing(int hash);

            Course search(std::string courseKey, int searchAlg);
            Course chainingSearch(std::string courseKey);
            Course LPSearch(std::string courseKey);
            //Course QPSearch(std::string courseKey);
            //Course DHSearch(std::string courseKey);

            int moduloHash(std::string courseKey);
            //void multiStringHash(std::string courseKey);
            //void directHash(std::string courseKey);

            std::vector<LinkedList> tableContents;
            int bucketCount;
            int collisionAlg;
};

#endif
