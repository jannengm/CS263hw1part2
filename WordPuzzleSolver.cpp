#include "WordPuzzleSolver.h"
#include <iostream>
#include <iomanip>

WordPuzzleSolver::WordPuzzleSolver() {
    /* add more code here as necessary */
}

void WordPuzzleSolver::load (ifstream& input) {
    int height, width, num_words;
    input >> width >> height;

    the_grid.resize(height, vector<char>(width));

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
    for (int k = 0; k < num_words; k++) {
        input >> w;  /* no ws I/O manip required here */
        the_words.push_back(w);
    }

    /* You may add more code to this function */
    getWordLengths();
    solution.resize(the_words.size());
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
        triple();
        for (auto &line : solution)
            cout << line << endl;
    }
    else {
        /* refer to third paragraph of page 2 in textbook */
        quadruple();
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

void WordPuzzleSolver::triple() {
    string str;
    int length;
    bool found;
    const int ROWS = the_grid.size();
    const int COLS = the_grid[0].size();

    for(int i = 0; i < the_words.size(); i++) {
        length = the_words[i].length();
        found = false;
        for (int row = 0; row < ROWS && !found; row++) {
            for(int col = 0; col < COLS && !found; col++){
                str = "";
                for (int i = 0; i < length && col + i < COLS; i++) {
                    str += the_grid[row][col + i];
                }

                if (str == the_words[i]){
                    found = true;
                    solution[i] = the_words[i] + " " + to_string(row) + " " + to_string(col) + " ACROSS";
                    break;
                }

                str = "";
                for (int i = 0; i < length && row + i < ROWS; i++) {
                    str += the_grid[row + i][col];
                }

                if (str == the_words[i]){
                    found = true;
                    solution[i] = the_words[i] + " " + to_string(row) + " " + to_string(col) + " DOWN";
                    break;
                }
            }
        }
    }
}

void WordPuzzleSolver::quadruple() {
    string str;
    int length = min_max.second;
    int pos;
    const int ROWS = the_grid.size();
    const int COLS = the_grid[0].size();

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            str = "";
            for (int i = 0; i < length && col + i < COLS; i++) {
                str += the_grid[row][col + i];
                if (i >= min_max.first - 1) {   /*Don't check the word_list if the string is too short*/
                    if ( (pos = checkList(str)) != -1) {
                        str = str + " " + to_string(row) + " " + to_string(col) + " ACROSS" ;
                        solution[pos] = str;
                        break;
                    }
                }
            }

            str = "";
            for (int i = 0; i < length && row + i < ROWS; i++) {
                str += the_grid[row + i][col];
                if (i >= min_max.first - 1) {
                    if ( (pos = checkList(str)) != -1) {
                        str = str + " " + to_string(row) + " " + to_string(col) + " DOWN" ;
                        solution[pos] = str;
                        break;
                    }
                }
            }
        }
    }
}

int WordPuzzleSolver::checkList(string& str) const {
    for(int i = 0; i < the_words.size(); i++) {
        if (str == the_words[i])
            return i;
    }
    return -1;
}
