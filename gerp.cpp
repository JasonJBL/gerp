/*
 gerp.cpp
 Jason Singer and Jake Merritt
* Contains: Defintions of the gerp class
*           This class contains the main object of the program. a Gerp
takes in the input directory, traverses through it, fills the hash table
in the gerpHash class, and then provides the query loop to facilitate searches.

* Part of: Project 4 assignment "Gerp" for Comp 15 
*/
#include "gerp.h"
#include <sstream>
#include <fstream>
using namespace std;
////////////////////////////////////////////////////////////////////
// Constructor + Destructor
////////////////////////////////////////////////////////////////////

/*
 * name:      Gerp constructor
 * purpose:   makes a gerp object filled with the files of a directory
 * arguments: string w/ name of directory and string w/ output file name
 * returns:   n/a
 * effects:   builds an object
 */
Gerp::Gerp(string directory, string outputFileName) {
    //building tree of every file in directory -- paths into vecotr
    tree(directory);
    //search through every filec
    search();
    ofstream ofile(outputFileName);
    run(ofile);   
}

/*
 * name:      Gerp deconstructor
 * purpose:   destorys a gerp object
 * arguments: n/a
 * returns:   n/a
 * effects:   destorys a gerp object
 */
Gerp::~Gerp() {
    
}



////////////////////////////////////////////////////////////////////
// run function
////////////////////////////////////////////////////////////////////

/*
 * name:      run
 * purpose:   query loop for program
 * arguments: none
 * returns:   none
 * effects:   sends program output to output file
 */
void Gerp::run(ofstream &ofile) {
    bool still_gerping = true;
    string query;
    string wordToGet;

    while (still_gerping) {
        cout << "Query? ";
        cin >> query;
        if (query == "@i" or query == "@insensitive") {
            cin >> wordToGet;
            printInsensitive(ofile, wordToGet);
        }
        else if (query == "@q" or query == "@quit") {
            still_gerping = false;
            cout << "Goodbye! Thank you and have a nice day." << endl;
        }
        else if (query == "@f") {
                cin >> wordToGet;
                ofile.close();
                ofile.open(wordToGet);
        }
        else {
            printSensitive(ofile, query);
        }
    }
}


////////////////////////////////////////////////////////////////////
// print functions + helpers
////////////////////////////////////////////////////////////////////

/*
 * name:      printSensitive
 * purpose:   prints out a sensitive search of a word
 * arguments: output stream and reference to a string
 * returns:   n/a
 * effects:   prints out correctly formatted output
 */
void Gerp::printSensitive(std::ofstream &ofile, string &key0) {
    string key = stripNonAlphaNum(key0);
    vector<Word> *hold = hashTable.getSensitive(key);
    if (hold == nullptr) {
        ofile << key << " Not Found. Try with @insensitive or @i." << endl;
    }
    else {
        bool print;
        int numInstances = hold->size();
        for (int i = 0; i < numInstances; i++) {
            print = true;
            if (i != 0){
                if (hold->at(i).line == hold->at(i - 1).line){
                    print = false;
                }
            }
            if (print){
                ofile << pathIndex[hold->at(i).path] << ":";
                ofile << hold->at(i).line << ": ";
                ofile << getLineOfText(hold->at(i).line, 
                      hold->at(i).path);
                ofile << endl;
            }
        }
    }
}

/*
 * name:      printInsensitive
 * purpose:   prints out an insensitive search of a word
 * arguments: output stream and reference to a string
 * returns:   n/a
 * effects:   prints out correctly formatted output
 */
void Gerp::printInsensitive(std::ofstream &ofile, string &key0) {
    string key = stripNonAlphaNum(key0);
    vector<vector<Word>> *variations = hashTable.getInsensitive(key);
    if (variations == nullptr) {
        ofile << key << " Not Found." << endl;
    }
    else {
        int numVars = variations->size();
        for (int i = 0; i < numVars; i++){
            printSensitive(ofile, variations->at(i).at(0).wordKey);
        }
    }
}



////////////////////////////////////////////////////////////////////
// search + helper funcs
////////////////////////////////////////////////////////////////////


/*
 * name:      search
 * purpose:   for every file in directory, search through each word
 * arguments: none
 * returns:   none
 * effects:   calls the wordByword function
 */
void Gerp::search() {
    int numFiles = pathIndex.size(); 
    for (int i = 0; i < numFiles; i++){
        ifstream infile(pathIndex.at(i));
        wordByword(infile, i);
        infile.close();
    }
}

/*
 * name:      wordByword
 * purpose:   for each word in each file, make a Word
 * arguments: input stream for a file
 * returns:   none
 * effects:   makes nodes that will go in gerpHash object
 */
void Gerp::wordByword(istream &input, int pIndex) {
    string text;
    string file_word;
    int line = 1;
    while (getline(input, text)) {
        istringstream lineOfText(text);
        while (lineOfText >> file_word) {
            file_word = stripNonAlphaNum(file_word);
            if (file_word == ""){
                continue;
            }
            Word value = {file_word, line, pIndex};
            hashTable.insertWord(value);
        }
        line++;
    }
    if (line > maxLineSize){
        maxLineSize = line;
    }
}

/*
 * name:      getLineOfText
 * purpose:   gets the line of text that a word is on
 * arguments: integer with line that the word is on and integer that
 * arguments: corresponds to a path
 * returns:   string w/ the line that the word is on
 * effects:   n/a
 */
string Gerp::getLineOfText(int line, int pIndex){
    ifstream infile(pathIndex.at(pIndex));
    string lineOfText;
    for (int i = 1; i <= line; i++){
        getline(infile, lineOfText);
    }
    return lineOfText;
}

////////////////////////////////////////////////////////////////////
// tree traversal functions
////////////////////////////////////////////////////////////////////

/*
 * name:      tree
 * purpose:   wrapper fucntion - makes a tree then calls helper to fill it
 * arguments: string containing directory name
 * returns:   none
 * effects:   builds tree out of direcory and subdirectories
 */
void Gerp::tree(string directory_name) {
    FSTree tree = FSTree(directory_name);
    DirNode *root = tree.getRoot();
    fsTreeTraversal_helper(root, root->getName());
}

/*
 * name:      fsTreeTraversal_helper
 * purpose:   helper function - fills in tree
 * arguments: pointer to a DirNode, string to store path
 * returns:   none
 * effects:   builds a vector filled with all the paths to files from
 *            the directory
 */
void Gerp::fsTreeTraversal_helper(DirNode *currNode, string path) {
    //base case #1: recursed too far
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
            pathIndex.push_back(path + "/" + currNode->getFile(i));
        }
    }
    //recursive case: add node name to path, then recurse to children
    for (int i = 0; i < currNode->numSubDirs(); i++) {
        fsTreeTraversal_helper(currNode->getSubDir(i), 
        path + "/" + currNode->getSubDir(i)->getName());
    }
}
