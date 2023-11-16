#include "toLower.h"

using namespace std;

/*
 * name:      toLower
 * purpose:   makes all chars in a string lowercase
 * arguments: reference to a string
 * returns:   a string
 * effects:   see purpose
 */
string toLower(string &input) {
    string lowercase;
    int length = input.length();
    for (int i = 0; i < length; i++){
        if (isupper(input[i])){
            char c = tolower(input[i]);
            lowercase += c;
        }
        else {
            lowercase += input[i];
        }
    }
    return lowercase;
}