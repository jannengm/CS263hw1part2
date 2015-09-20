#include "WordPuzzleSolver.h"
#include <iostream>
#include <iomanip>

WordPuzzleSolver::WordPuzzleSolver() {
    /* add more code here as necessary */
}

void WordPuzzleSolver::load (ifstream& input) {
    int height, width, num_words;
    input >> height >> width;

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

    clog << "Shortest word: " << min_max.first << endl;
    clog << "Longest word: " << min_max.second << endl;

    clog << "First row is: " << getRow(0) << endl;
    clog << "First column is: " << getColumn(0) << endl;

#endif*/

    /* Java string "operator==" will be used here */
    if (which == "triple") {
        triple();
    }
    else {
        /* refer to third paragraph of page 2 in textbook */
        quadruple();
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

void WordPuzzleSolver::triple() const {
    string str;
    int length;

    for(auto &word: the_words) {
        length = word.length();
        for (int row = 0; row < the_grid.size(); row++) {
            for(int col = 0; col < the_grid[0].size(); col++){
                str = "";
                for (int i = 0; i < length &&
                        col + i < the_grid[0].size(); i++) {
                    str += the_grid[row][col + i];
                }

                if (str == word){
                    cout << word << " " << row << " " << col
                    << " ACROSS" << endl;
                    break;
                }

                str = "";
                for (int i = 0; i < length &&
                                row + i < the_grid.size(); i++) {
                    str += the_grid[row + i][col];
                }

                if (str == word){
                    cout << word << " " << row << " " << col
                    << " DOWN" << endl;
                    break;
                }
            }
        }

    }
}

/*void WordPuzzleSolver::triple() const {
    int pos;

    for (auto &word : the_words) {
        for (int row = 0; row < the_grid.size(); row++) {
            string line = getRow(row);
            if ((pos = line.find(word)) != string::npos) {
                cout << word << " " << row << " " << pos << " ACROSS" << endl;
                break;
            }
        }

        for (int col = 0; col < the_grid[0].size(); col++) {
            string line = getColumn(col);
            if ((pos = line.find(word)) != string::npos) {
                cout << word << " " << pos << " " << col << " DOWN" << endl;
                break;
            }
        }
    }
}*/

string WordPuzzleSolver::getRow(int row) const {
    string result = "";
    for(int col = 0; col < the_grid[0].size(); col++) {
        result += the_grid[row][col];
    }

    return result;
}

string WordPuzzleSolver::getColumn(int col) const {
    string result = "";
    for(int row = 0; row < the_grid[0].size(); row++) {
        result += the_grid[row][col];
    }

    return result;
}

void WordPuzzleSolver::quadruple() const {
    string str;
    int length = min_max.second;
    for (int row = 0; row < the_grid.size(); row++) {
        for (int col = 0; col < the_grid[0].size(); col++) {
            str = "";
            for (int i = 0; i < length &&
                            col + i < the_grid[0].size(); i++) {
                str += the_grid[row][col + i];
                if (i >= min_max.first) {
                    if (checkList(str)) {
                        cout << str << " " << row << " " << col
                        << " ACROSS" << endl;
                        break;
                    }
                }
            }

            str = "";
            for (int i = 0; i < length &&
                            row + i < the_grid.size(); i++) {
                str += the_grid[row + i][col];
                if (i >= min_max.first) {
                    if (checkList(str)) {
                        cout << str << " " << row << " " << col
                        << " DOWN" << endl;
                        break;
                    }
                }
            }
        }
    }
}

bool WordPuzzleSolver::checkList(string& str) const {
    for(auto &word : the_words) {
        if (str == word)
            return true;
    }
    return false;
}
