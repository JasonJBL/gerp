/*
 *  unit_tests.h
 *  Jason Singer and Jake Merritt
 *  04/14/2023
 *
 *
 *  testing file for gerp proj
 *
 */ 

#include "stringProcessing.h"
#include <cassert>
#include "gerpHash.h"

using namespace std;

//tests string processing function on input w leading and trailing nonalphanum
//chars
void testStringProcessing(){
    string s = "';;];],'test-compsci!!!']'']'";
    string out = stripNonAlphaNum(s);
    assert(out == "test-compsci");
}

//tests string processing on a basic string w only alphanum chars
void testStringProcessingAllAlpha(){
    string s = "ILoveCS15Graders";
    string out = stripNonAlphaNum(s);
    assert(out == "ILoveCS15Graders");
}

//tests string processing on string with no alphanum chars

void testJunk(){
    string s = "%^&*(*&^%$%^&*()(*&^%))";
    string out = stripNonAlphaNum(s);
    assert(out == "");
}

//testing for hashTable. Made array public so that functions can be tested 
//directly. In final submission, these tests won't compile as they try to 
//access private data, which is why it is commented out

/*
//tests insert on a lowercase input
void testInsertInsenitiveKey(){
    gerpHash testTable;
    Word test{"Here", 1, 3,};
    testTable.insertWord(test);
    int index = testTable.function("here") % testTable.arraySize;
    assert(testTable.hashTable[index].front().ikey == "here");

}

//test insert on a case sensitive input
void testInsertSenitiveKey(){
    gerpHash testTable;
    Word test{"Here", 1, 3,};
    testTable.insertWord(test);
    int index = testTable.function("here") % testTable.arraySize;
    assert(testTable.hashTable[index].front().variations[0].at(0).wordKey == 
    "Here");
}

//tests that words with multiple instances are put into the vector correctly
void testHereTwice(){
    gerpHash testTable;
    Word test{"Here", 1, 3};
    testTable.insertWord(test);
    int index = testTable.function("here") % testTable.arraySize;
    Word test2{"Here", 2, 5};
    testTable.insertWord(test2);
    assert(testTable.hashTable[index].front().variations[0].at(0).wordKey == 
    "Here");
    assert(testTable.hashTable[index].front().variations[0].at(0).line == 1);
    assert(testTable.hashTable[index].front().variations[0].at(1).wordKey == 
    "Here");
    assert(testTable.hashTable[index].front().variations[0].at(1).line == 2);
}


//this test will only work on an edited insert function that forces chaining
//tests that chaining is handled correctyl
void testChaining(){
    gerpHash testTable;
    Word test{"Here", 1, 3};
    testTable.insertWordForceChaining(test);
    Word test2{"Chain", 2, 5};
    testTable.insertWordForceChaining(test2);
    assert(testTable.hashTable[5].front().ikey == "here");
    assert(testTable.hashTable[5].back().ikey == "chain");
}


//builds off last test by testing multiple instances in chained bucket
//combines chaining test and test with multiple variations of the same word
void testInsertInChainedBucket(){
    gerpHash testTable;
    Word test{"Here", 1, 3,};
    testTable.insertWordForceChaining(test);
    Word test2{"Chain", 2, 5};
    testTable.insertWordForceChaining(test2);
    Word test3{"ChAIn", 5, 11};
    testTable.insertWordForceChaining(test3);
    assert(testTable.hashTable[5].back().variations[1].at(0).wordKey
     == "ChAIn");
    assert(testTable.hashTable[5].back().variations[1].at(0).line
     == 5);
}

//tests getter for a case sensitive word
void testGetSensitive(){
    gerpHash testTable;
    Word test{"Here", 1, 3, };
    testTable.insertWord(test);
    string s = "Here";
    Word test2{"here", 1, 3};
    testTable.insertWord(test2);
    vector<Word> *w = testTable.getSensitive(s);
    assert(w->at(0).wordKey == "Here");
}

//tests getter for case insnensitive words
void testGetInsensitive(){
    gerpHash testTable;
    for (int i = 0; i < 4; i++){
    Word test{"Scientist", 1, 3};
    testTable.insertWord(test);
    }
    for (int i = 0; i < 4; i++){
    Word test2{"scientist", 1, 3};
    testTable.insertWord(test2);
    }
    //Word test3{"HErE", 1, 3, instances};
   // testTable.insertWord(test3);
    string s = "scientist";
    vector<vector<Word>> *v = testTable.getInsensitive(s);
    assert(v->at(0).at(0).wordKey == "Scientist");
    assert(v->at(1).at(0).wordKey == "scientist");
}

//tests expand function (this was the hardest function to implement so testing
//was very crucial to debugging)

void testExpand(){
    gerpHash testTable;
    vector<Word> instances;
    for (int i = 0; i < 25; i++){
        Word test{"Scientist", 1, 3};
        testTable.insertWord(test);
    }
    for (int i = 0; i < 26; i++){
        Word test{"scientist", 1, 3};
        testTable.insertWord(test);
    }
    string s = "scientist";
    cerr << testTable.getInsensitive(s)->size() << endl;
}
*/