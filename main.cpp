/*
 main.cpp
 Jason Singer and Jake Merritt
* Contains: the main runner of gerp - uses gerp class to run program
*           
* Part of: Project 4 assignment "Grep" for Comp 15 
*/
#include <fstream>
#include "gerp.h"
using namespace std;

void abort(string error_message);

template<typename streamtype>
void open_or_die(streamtype &stream, string file_name);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        abort("Usage: ./gerp inputDirectory outputFile");
    }
      else {
        ifstream instream;

        open_or_die(instream,  argv[1]);

        Gerp my_gerp(argv[1], argv[2]);
      }
    return 0;
}

/*
 * name:      abort
 * purpose:   sends error message and then ends game
 * arguments: a string with an error message
 * returns:   nothjing
 * effects:   ends the program
 */
void abort(string error_message) {
  cerr << error_message << endl;
  exit(EXIT_FAILURE);
}

/*
 * Try to open the given file.
 * Abort on failure.
 * If the function returns, caller can assume stream is open.
 * By using a template, we gain modularity: this function will work
 * for ifstreams *and* ofstreams.
 */

/*
 * name:      open_or_die
 * purpose:   tries to open a file, aborts if this does not work
 * arguments: takes in a template stream and a file name
 * returns:   none
 * effects:   calls abort function if the stream did not open the file
 */
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open())
        abort("Error: could not open file " + file_name);
}



