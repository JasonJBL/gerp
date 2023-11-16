/*
 FSTreeTraversal.cpp
 Jason Singer and Jake Merritt
* Contains: Delceration of the gerp class
*           This class contains the building of the file index and handles
*           queries as inpout and produces output based on these queries
* Part of: Project 4 assignment "Gerp" for Comp 15 Fall 2018
*/

#ifndef GERP_H
#define GERP_H
#include "FSTree.h"
#include "gerpHash.h"
#include "stringProcessing.h"


class Gerp {
    public:

    Gerp(std::string directory, std::string outputFileName);
    ~Gerp();

    void run(std::ofstream &ofile);

    private:

    std::vector<std::string> pathIndex;


    void tree(std::string directory_name);
    void fsTreeTraversal_helper(DirNode *currNode, std::string path);
    std::string getLineOfText(int line, int pIndex);

    void search();
    void wordByword(std::istream &input, int pIndex);

    void printInsensitive(std::ofstream &ofile, std::string &key);
    void printSensitive(std::ofstream &ofile, std::string &key);
    
    gerpHash hashTable;
    int maxLineSize = 0;
};

#endif