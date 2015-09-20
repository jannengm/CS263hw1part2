#include "WordPuzzleSolver.h"
#include <iostream>
#include <iomanip>

WordPuzzleSolver::WordPuzzleSolver() {
    /* add more code here as necessary */
}

void WordPuzzleSolver::load (ifstream& input) {
    int height, width, num_words;
    input >> width >> height;

    the_grid.resize (height, vector<char>(width));

    /* the following nested loops read all the letters and place them
     * into the grid */
    for (int k = 0; k < height; k++) {
        for (int m = 0; m < width; m++) {
            /* "ws" is an I/O manipulator to skip whitespaces */
            input >> ws >> the_grid[k][m];
        }
    }

    input >> num_words;

    string w;
    for (int k = 0; k < num_words; k++)
    {
        input >> w;  /* no ws I/O manip required here */
        the_words.push_back (w);
    }

    /* You may add more code to this function */
    getWordLengths();
}

void WordPuzzleSolver::solve(const string& which) {
/*#ifndef MUTE_ALL_DEBUGGING_OUTPUT
    // Print your DEBUGGING output to clog
    clog << "...for debugging only..." << endl;

    clog << "The board size is " 
        << the_grid.size() << "x" << the_grid[0].size() << endl;
    clog << "and " << the_words.size() << " words to search." << endl << endl;

    for (auto& me : the_words) {   // me is now a string
        clog << me << endl;
    }

#endif*/

    /* Java string "operator==" will be used here */
    if (which == "triple") {
        vector<string> solution = triple();
        for (auto &line : solution)
            cout << line << endl;
    }
    else {
        /* refer to third paragraph of page 2 in textbook */
        vector<string> solution = quadruple();
        for (auto &line : solution)
            cout << line << endl;
    }
}

void WordPuzzleSolver::getWordLengths() {
    min_max.first = the_words[0].length();
    min_max.second = the_words[0].length();

    for (auto& word : the_words) {
        if (word.length() < min_max.first)
            min_max.first = word.length();
        if (word.length() > min_max.second)
            min_max.second = word.length();
    }
}

vector<string> WordPuzzleSolver::triple() const {
    string str;
    int length;
    bool found;
    vector<string> solution;
    const int ROWS = the_grid.size();
    const int COLS = the_grid[0].size();

    for(auto &word: the_words) {
        length = word.length();
        found = false;
        for (int row = 0; row < ROWS && !found; row++) {
            for(int col = 0; col < COLS && !found; col++){
                str = "";
                for (int i = 0; i < length && col + i < COLS; i++) {
                    str += the_grid[row][col + i];
                }

                if (str == word){
                    found = true;
                    solution.push_back(word + " " + to_string(row) + " " + to_string(col) + " ACROSS" );
                    break;
                }

                str = "";
                for (int i = 0; i < length && row + i < ROWS; i++) {
                    str += the_grid[row + i][col];
                }

                if (str == word){
                    found = true;
                    solution.push_back(word + " " + to_string(row) + " " + to_string(col) + " DOWN" );
                    break;
                }
            }
        }
    }

    return solution;
}

vector<string> WordPuzzleSolver::quadruple() const {
    string str;
    int length = min_max.second;
    vector<string> solution;
    const int ROWS = the_grid.size();
    const int COLS = the_grid[0].size();

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            str = "";
            for (int i = 0; i < length && col + i < COLS; i++) {
                str += the_grid[row][col + i];
                if (i >= min_max.first) {   /*Don't check the word_list if the string is too short*/
                    if (checkList(str)) {
                        solution.push_back(str + " " + to_string(row) + " " + to_string(col) + " ACROSS" );
                        break;
                    }
                }
            }

            str = "";
            for (int i = 0; i < length && row + i < ROWS; i++) {
                str += the_grid[row + i][col];
                if (i >= min_max.first) {
                    if (checkList(str)) {
                        solution.push_back(str + " " + to_string(row) + " " + to_string(col) + " DOWN" );
                        break;
                    }
                }
            }
        }
    }
    return solution;
}

bool WordPuzzleSolver::checkList(string& str) const {
    for(auto &word : the_words) {
        if (str == word)
            return true;
    }
    return false;
}
