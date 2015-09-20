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

    /* You may add as many private variables and functions here */

    /*
     * Returns the minimum and maximum length of the words in the word list
     * as pair<minimum length, maximum length>
     */
    void getWordLengths();

    /*
     * Solves the puzzle using the triple algorithm. Searches each ordered triple
     * (row, column, direction) for the preseence of the word being searched for,
     * then moves on to the next word and repeats. Returns a vector of strings
     * containing the solution.
     */
    vector<string> triple() const;

    /*
     * Solves the puzzle using the quadruple algorithm. Checks if each ordered
     * quadruple (row, column, direction, number of characters) is in the word list.
     * Returns a vector of strings containing the solution.
     */
    vector<string> quadruple() const;

    /*
     * Checks if a given string is in the word list. Returns true if found,
     * else false.
     */
    bool checkList(string&) const;
    
    /*
     * From a starting position in the grid given by row and col, the function checks 
     * if the characters that follow horizontally make up the given word. If they do,
     * the function returns true, else false.
     */ 
    bool foundH (const string& word, int row, int col);
    
    /*
     * From a starting position in the grid given by row and col, the function checks 
     * if the characters that follow vertically make up the given word. If they do,
     * the function returns true, else false.
     */ 
    bool foundV (const string& word, int row, int col);
    
    /*
     * Goes through the entire grid until it finds the given word, using the foundH
     * and foundV functions.
     */ 
    void find (const string& word);
};


#endif
