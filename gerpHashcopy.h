/*
 gerpHash.h
 Jason Singer and Jake Merritt
* Contains: Declarations of the gerpHash class
*           This class contains a hash table for gerp words, as well as the
  word struct
* Part of: Project 4 assignment "Grep" for Comp 15 
*/

#ifndef gerpHash_H
#define gerpHash_H
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "toLower.h"


struct Word {
    std::string wordKey;
    int line;
    int path;
    std::vector<Word> instances;
};
struct H_node {
        std::string ikey;
        std::vector<Word> variations;
    };

class gerpHash {
    public:

    gerpHash();
    ~gerpHash();

    void insertWord(Word &key);
    void insertWordForceChaining(Word value);

    Word *getSensitive(std::string &key);
    std::vector<Word> *getInsensitive(std::string &key);

    std::list<H_node> *hashTable;
    std::hash<std::string> function;

    int arraySize;

    private:
    
    int numEntrys;
    int loadFactor;

    void expand();

    void insertHelper(Word &value, std::list<H_node>::iterator &it);

};
#endif