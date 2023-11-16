#include <cctype>
#include "stringProcessing.h"

using namespace std;

/*
 * name:      stripNonAlphaNum
 * purpose:   strips non alphanumeric chars from a string.
 * arguments: reference to a string
 * returns:   a string
 * effects:   see purpose
 */
string stripNonAlphaNum(string &input){
    int length = input.length();
    bool isParsing = false;
    bool foundStart = false;
    int indexStart = -1;
    int indexEnd = -1;
    for (int i = 0; i < length; i++){
        if (isalnum(input[i]
        ) and !isParsing and !foundStart){
            isParsing = true;
            indexStart = i;
            foundStart = true;
        }
        if(!isalnum(input[i]) and isParsing){
            indexEnd = i;
            isParsing = false;
        }
        //case where non alnum chars are in middle of string
        else if (isalnum(input[i]) and !isParsing and foundStart){
            isParsing = true;
        }
    }
    if (indexStart == -1){
        return "";
    }
    if (isParsing){
        indexEnd = length;
    }
    return input.substr(indexStart, indexEnd - indexStart);
}
