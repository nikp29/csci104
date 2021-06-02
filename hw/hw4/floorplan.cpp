#include "avlbst.h"
#include <cstring>
#include <fstream>
#include <iostream>
// #include <map> commentted out bc we dont need anymore maps!
#include <sstream>
#include <vector>

using namespace std;

struct Rectangle {
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef AVLTree<int, Rectangle> InputMapType;
typedef AVLTree<int, std::pair<int, int>> OutputMapType;

// Allowed global variables: the dimensions of the grid
int n;  // X-dim size
int m;  // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    os << p.first << "," << p.second;
    return os;
}

void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output) {
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it) {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool>>& grid) {
    for (int x = x1; x < x1 + r.length; x++) {
        for (int y = y1; y < y1 + r.height; y++) {
            grid[x][y] = !grid[x][y];
        }
    }
}
void turn(Rectangle& r) {
    // flips the rectangle's length and height
    int foo = r.height;
    r.height = r.length;
    r.length = foo;
}
bool checkRect(int x1, int y1, const Rectangle& r, vector<vector<bool>>& grid) {
    // go through every cell in the proposed rectangle and check if it will fit in the allotted space
    // without infringing on another tile's territory
    if (y1 + r.height > m || x1 + r.length > n)
        return false;
    for (int x = x1; x < x1 + r.length; x++) {
        for (int y = y1; y < y1 + r.height; y++) {
            // if we ever find a space on the grid that is true we know that it has already
            // been allocated so we can't place our tile here bc it will overlap
            if (grid[x][y])
                return false;
        }
    }
    return true;
}
// TODO: Write your backtracking search function here
bool placeTiles(
        InputMapType::iterator it, vector<vector<bool>>& grid, InputMapType& inputMap, OutputMapType& outputMap) {
    // if we've placed all the tiles that means we've gotten to the end of
    // input map so celebrate and return true
    if (inputMap.end() == it) {
        // base case
        return true;
    }

    // iterate through the grid testing if each index can work
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            InputMapType::iterator next = it;
            // first check in the initial rect config
            if (checkRect(x, y, it->second, grid)) {
                flip(x, y, it->second, grid);
                // add tile to outfile
                outputMap.insert(make_pair(it->first, pair<int, int>(x, y)));
                if (placeTiles(++next, grid, inputMap, outputMap)) {
                    return true;
                } else {
                    // if we couldn't fit the rectangle, then remove it, and unflip
                    outputMap.remove(it->first);
                    flip(x, y, it->second, grid);
                }
            }
            // turn the rectangle and try again
            turn(it->second);
            if (checkRect(x, y, it->second, grid)) {
                flip(x, y, it->second, grid);
                // add tile to outfile
                outputMap.insert(make_pair(it->first, pair<int, int>(x, y)));
                if (placeTiles(++next, grid, inputMap, outputMap)) {
                    return true;
                } else {
                    // if we couldn't fit the rectangle, then remove it, and unflip
                    outputMap.remove(it->first);
                    flip(x, y, it->second, grid);
                }
            }
        }
    }
    // if we weren't able to place this rectangle then we return false, because we have failed
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool>> grid;

    for (int i = 0; i < n; i++) {
        grid.push_back(vector<bool>(m, false));
    }
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here
    solution_exists = placeTiles(input.begin(), grid, input, output);

    if (!solution_exists) {
        ofile << "No solution found.";
    } else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}