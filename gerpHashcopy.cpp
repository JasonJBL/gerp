/*
 gerpHash.cpp
 Jason Singer and Jake Merritt
* Contains: Defintions of the gerpHash class
*           This class contains a hash table for gerp words, as well as the
  word struct
* Part of: Project 4 assignment "Grep" for Comp 15 
*/

#include "gerpHash.h"
using namespace std;

////////////////////////////////////////////////////////////////////
// Constructor + Destructor
////////////////////////////////////////////////////////////////////

/*
 * name:      gerpHash constructor
 * purpose:   constructs gerpHash object and allocates memory for hashtable
 * arguments: none
 * returns:   n/a
 * effects:   makes new gerpHash object
 */
gerpHash::gerpHash() {
    numEntrys = 0;
    loadFactor = 0;
    arraySize = 50;
    hashTable = new list<H_node>[arraySize];

}


/*
 * name:      gerpHash destructor
 * purpose:   recycles memory used by gerpHash object
 * arguments: none
 * returns:   none
 * effects:   recycles memory taken by hashtable
 */
gerpHash::~gerpHash() {
    delete [] hashTable;
}

////////////////////////////////////////////////////////////////////
// insertWord + helper funcs
////////////////////////////////////////////////////////////////////

/*
 * name:      insertWord
 * purpose:   puts a Word struct into the hashTable
 * arguments: a Word struct
 * returns:   none
 * effects:   puts Word into hashTable, changes loadFactor
 */
void gerpHash::insertWord(Word &value) {
    string key = toLower(value.wordKey);
    int index = function(toLower(key)) % arraySize;
    if (hashTable[index].empty()) { //case one: bucket is empty O(1)
        vector<Word> variations;
        H_node node{toLower(value.wordKey), variations};
        hashTable[index].push_back(node);
        hashTable[index].front().variations.push_back(value);
    } //case 2: bucket is not empty (chaining or repeat)
    else{
        list<H_node>::iterator it = hashTable[index].begin();
        while (toLower(value.wordKey) != it->ikey 
              and it != hashTable[index].end()) {
            it++;
        }
        if (toLower(value.wordKey) == it->ikey) { //O(1) if no collisions
            insertHelper(value, it);
        }
        else {

            vector<Word> variations;
            H_node node{toLower(value.wordKey), variations};
            node.variations.push_back(value);
            hashTable[index].push_back(node);
        } 
        //  if (value.wordKey == "scientist" or value.wordKey == "Scientist"){
        //     cerr << it->variations.size() << endl;
        // }
    }
    numEntrys++;
    loadFactor = numEntrys / arraySize;
    if (loadFactor > .7){
        expand();
    }
}

/*
 * name:      insertHelper
 * purpose:   Helper function that detirmines if word is new variation of
 *            existing ikey or another instance of existing case sensitive key
 * arguments: A word struct
 * returns:   n/a
 * effects:   word ends up inserted in hash table
 */
void gerpHash::insertHelper(Word &value, list<H_node>::iterator &it){
    int i = 0;
    int numVars = it->variations.size();
    while (i != numVars and value.wordKey != it->variations[i].wordKey){
        i++;
    }
    if (i == numVars){
       it->variations.push_back(value);
       
    }
    else {
        it->variations[i].instances.push_back(value);
    }
}

 


////////////////////////////////////////////////////////////////////
// getSensitive + getInsensitive
////////////////////////////////////////////////////////////////////

/*
 * name:      getSensitive
 * purpose:   return Word struct that corresponds to given key
 * arguments: string w/key from query
 * returns:   a pointer to a Word struct
 * effects:   n/a
 */
Word *gerpHash::getSensitive(string &key) {
    //get index for the given key
    int index = function(toLower(key)) % arraySize;
  
    //declare iteraor and then at the index in hash, iterate through 
    //the list of H_nodes until the key matches key in the H_Node 
    //O(1) if no chaining in best case
    list<H_node>::iterator it = hashTable[index].begin();
    while(toLower(key) != it->ikey and it != hashTable[index].end()) {
        it++;
    }
    cerr << "size: " << it->variations.size() << endl;
    //if the query is not in hash table, return null
    if (it == hashTable[index].end()) {
        return nullptr;
    }

    //iterate through the variations of the key until correct variation
    //Worst case O(n) where n is number of variations 
    int i = 0;
    while (key != it->variations.at(i).wordKey){
        i++;
        if (i >= int(it->variations.size())){
            return nullptr;
        }
    }
    //make a pointer to the word that we have found, return it
    Word *wordAt;
    wordAt = &it->variations.at(i);
    return wordAt;
}

/*
 * name:      getInsenstive
 * purpose:   return vector of Word structs that corresponds to given key
 * arguments: the key from the query
 * returns:   a pointer to a vector of Word structs
 * effects:   n/a
 */
vector<Word> *gerpHash::getInsensitive(string &key) {
    //get index for the given key
    int index = function(toLower(key)) % arraySize;
    
    //declare iteraor and then at the index in hash, iterate through 
    //the list of H_nodes until the key matches key in the H_Node 
    list<H_node>::iterator it = hashTable[index].begin();
    while(toLower(key) != it->ikey and it == hashTable[index].end()) {
        it++;
    }
    
    //if the query is not in hash table, return null
    if (it == hashTable[index].end()) {
        return nullptr;
    }
    cerr << "gotten size" << it->variations.size() << endl;
    cerr << it->variations.at(0).wordKey << endl;
    //make a pointer to variatorns vector we have found, return it
    vector<Word> *v_p;
    v_p = &it->variations;   
    return v_p;
}

////////////////////////////////////////////////////////////////////
// expand
////////////////////////////////////////////////////////////////////

/*
 * name:      expand
 * purpose:   expands hashTable when load factor is > .7
 * arguments: n/a
 * returns:   n/a
 * effects:   hash table becomes larger with more empty buckets
 */
void gerpHash::expand(){
    int newSize = arraySize * 2 + 2;
    list<H_node> *hash = new list<H_node>[newSize];

    for (int i = 0; i < arraySize; i++){
            for (list<H_node>::iterator it = hashTable[i].begin(); 
                                   it != hashTable[i].end(); it++) {
                vector<Word> v;
                int newIndex = function(it->ikey) % newSize;
                for (int j = 0; j < int(it->variations.size()); j++){
                    v.push_back(it->variations.at(j));
                }
                H_node node{it->ikey, v};
                hash[newIndex].push_back(node);
            }
        hash[i] = hashTable[i];
    }
    delete [] hashTable;
    hashTable = hash;
    arraySize = newSize;
    loadFactor = numEntrys / arraySize;
}

////////////////////////////////////////////////////////////////////
// test insert function for chaining
////////////////////////////////////////////////////////////////////

/*
 * name:      insertWordForceChaining
 * purpose:   function that forces the hash to chain
 * arguments: A word struct
 * returns:   n/a
 * effects:   Note: function only used for testing
 */
void gerpHash::insertWordForceChaining(Word value) {
    int index = 5;
    if (hashTable[index].empty()) { //case one: bucket is empty
        vector<Word> variations;
        H_node node{toLower(value.wordKey), variations};
        hashTable[index].push_back(node);
        hashTable[index].front().variations.push_back(value);
    } //case 2: bucket is not empty
    else{
        list<H_node>::iterator it = hashTable[index].begin();
        while (toLower(value.wordKey) != it->ikey 
              and it != hashTable[index].end()) 
        {
            it++;
        }
        if (toLower(value.wordKey) == it->ikey) {
            it->variations.push_back(value);
        }
        else {
            vector<Word> variations;
            H_node node{toLower(value.wordKey), variations};
            node.variations.push_back(value);
            hashTable[index].push_back(node);
        } 
    }
    numEntrys++;
    loadFactor = numEntrys / arraySize;
    if (loadFactor > .7){
        expand();
    }
}

