#ifndef CS263_WORD_PUZZLE_VECTOR_EXERCISE_H
#define CS263_WORD_PUZZLE_VECTOR_EXERCISE_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class WordPuzzleSolver {
public:
    /* DO NOT CHANGE the signature of the public functions,
     * otherwise your program will not compile when it is run
     * from my script */
    WordPuzzleSolver();
    void load (ifstream& __input_file_to_read_from__);
    void solve (const string& __algorithm_to_use__);
private:
    vector<vector<char>> the_grid;
    vector<string> the_words;
    pair<int, int> min_max;
    vector<string> solution;

    /* You may add as many private variables and functions here */

    /*
     * Returns the minimum and maximum length of the words in the word list
     * as pair<minimum length, maximum length>
     */
    void getWordLengths();

    /*
     * Solves the puzzle using the triple algorithm. Searches each ordered triple
     * (row, column, direction) for the presence of the word being searched for,
     * then moves on to the next word and repeats. Stores the solution in
     * vector<string> solution
     */
    void triple();

    /*
     * Solves the puzzle using the quadruple algorithm. Checks if each ordered
     * quadruple (row, column, direction, number of characters) is in the word list.
     * Stores the solution in vector<string> solution
     */
    void quadruple();

    /*
     * Checks if a given string is in the word list. Returns the position if found, else -1
     */
    int checkList(string&) const;
};


#endif
