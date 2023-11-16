/*
 FSTreeTraversal.cpp
 Jason Singer and Jake Merritt
* Contains: Defintions of the FSTree class
*           This class contains an n-ary tree to represent a file system
* Part of: Project 4 assignment "Grep" for Comp 15 Fall 2018
*/

#include <iostream>
#include <fstream>
#include <string>
#include "FSTree.h"
#include "DirNode.h"
#include "gerpHash.h"


void tree(std::string directory_name);
void fsTreeTraversal_helper(DirNode *currNode, std::string path);
void abort(std::string error_message);

/*int main(int argc, char *argv[]) {
    if (argc != 2){ 
        abort("I aborted");
    }
    std::string d_name =  argv[1];
    tree(d_name);
    return 0;
}
*/

int main(){
    gerpHash testTable;
    std::vector<Word> instances;
    Word test{"Here", 1, 3, instances};
    testTable.insertWord(test);
    Word test2{"HERE", 1, 3, instances};
    testTable.insertWord(test2);
    return 0;
}

void abort(std::string error_message) {
  std::cerr << error_message << std::endl;
  exit(EXIT_FAILURE);
}

void tree(std::string directory_name) {
    FSTree tree = FSTree(directory_name);
    DirNode *root = tree.getRoot();
    fsTreeTraversal_helper(root, root->getName());
}

void fsTreeTraversal_helper(DirNode *currNode, std::string path) {
    //base case #1: recursed too far
    std::cerr << "path: " << currNode->getName() << std::endl;
    if (currNode == nullptr) {
        return;
    }
    //base case #2: reached empty files
    if ((currNode->isEmpty())) {
        return;
    }
    //base case #3: if current node has files, print out files
    if (currNode->hasFiles()){
        for (int i = 0; i < currNode->numFiles(); i++) {
            std::cout << path << "/" << currNode->getFile(i) << std::endl; 
        }
    }
    //recursive case: add node name to path, then recurse to children
    for (int i = 0; i < currNode->numSubDirs(); i++) {
        fsTreeTraversal_helper(currNode->getSubDir(i), 
            path + "/" + currNode->getSubDir(i)->getName());
    }
}