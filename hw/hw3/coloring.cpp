#include <fstream>
#include <iostream>
#include <map>

using namespace std;

bool isValid(char** cont_map, int row, int col, int rows, int cols, map<char, int>& country_color) {
    /* make sure that all the adjecent cells either, dont exist, are from the same
     * country dont have an assigned color, or have an assigned color that is
     * different from the current cell */
    if (row - 1 >= 0 && cont_map[row][col] != cont_map[row - 1][col]
        && country_color.find(cont_map[row - 1][col]) != country_color.end()
        && country_color[cont_map[row][col]] == country_color[cont_map[row - 1][col]])
        return false;
    if (col - 1 >= 0 && cont_map[row][col] != cont_map[row][col - 1]
        && country_color.find(cont_map[row][col - 1]) != country_color.end()
        && country_color[cont_map[row][col]] == country_color[cont_map[row][col - 1]])
        return false;
    if (row + 1 < rows && cont_map[row][col] != cont_map[row + 1][col]
        && country_color.find(cont_map[row + 1][col]) != country_color.end()
        && country_color[cont_map[row][col]] == country_color[cont_map[row + 1][col]])
        return false;
    if (col + 1 < cols && cont_map[row][col] != cont_map[row][col + 1]) {
        if ((country_color.find(cont_map[row][col + 1]) != country_color.end())
            && country_color[cont_map[row][col]] == country_color[cont_map[row][col + 1]])
            return false;
    }
    return true;
}

bool solve_map(char** cont_map, int row, int col, int rows, int cols, map<char, int>& country_color) {
    // base case
    if (col == cols) {
        // if reach the end of the row move to the start if the next one
        return solve_map(cont_map, row + 1, 0, rows, cols, country_color);
    }
    if (row == rows) {
        // if we get to the last row return true because we have reached the end of the map
        return true;
    }
    if (country_color.find(cont_map[row][col]) == country_color.end()) {
        // try all color possibilities
        for (int i = 1; i < 5; i++) {
            country_color[cont_map[row][col]] = i;
            /* try each color by setting the color in the map and then re-running
             * solve_map on the same cell */
            if (solve_map(cont_map, row, col, rows, cols, country_color)) {
                // if we find something that works then return true
                return true;
            }
        }
        /* if one of the colors work we know we messed up when assigning a
         * previous country's color so we erase the current countries color from
         * the map and backtrack */
        country_color.erase(cont_map[row][col]);
        return false;
    }
    /* if current cell's country has been assigned check for vailidty, if valid
     * continue through the map, otherwise return false */
    if (isValid(cont_map, row, col, rows, cols, country_color)) {
        return solve_map(cont_map, row, col + 1, rows, cols, country_color);
    }
    return false;
}

int main(int argc, char* argv[]) {
    // parse input from file
    if (argc < 2) {
        cout << "Please provide a map file" << endl;
        return 0;
    }

    ifstream infile(argv[1]);
    if (infile.fail()) {
        cout << "Invalid input file" << endl;
        return 0;
    }
    int num_continents_;
    int cols_;
    int rows_;
    infile >> num_continents_ >> rows_ >> cols_;
    if (infile.fail()) {
        cout << "Invalid input file" << endl;
        return 0;
    }
    // generate char** map
    char** cont_map_ = new char*[rows_];
    for (int i = 0; i < rows_; i++) {
        char* row = new char[cols_];
        infile >> row;
        cont_map_[i] = row;
        if (infile.fail()) {
            cout << "Invalid input file" << endl;
            return 0;
        }
    }

    // generate country name-> color map
    map<char, int> country_color_;

    // call recursive function
    solve_map(cont_map_, 0, 0, rows_, cols_, country_color_);

    /* this part doesn't really matter, I just wanted to reassign the
     * coloring numbers so that A had 1, and new colors should up in ascending numerical order */
    map<int, int> country_color_reset_order;
    int current_color = 1;
    for (int i = 0; i < num_continents_; i++) {
        if (country_color_reset_order.find(country_color_[((char)'A' + i)]) == country_color_reset_order.end()) {
            country_color_reset_order[country_color_[((char)'A' + i)]] = current_color;
            current_color++;
        }
    }

    // display results
    for (int i = 0; i < num_continents_; i++) {
        cout << (char)('A' + i) << " " << country_color_reset_order[country_color_[((char)'A' + i)]] << endl;
    }
    return 0;
}