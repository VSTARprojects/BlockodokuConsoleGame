#ifndef GRID_H
#define GRID_H

#include<Block.h>

class Grid {
    int row_size, col_size;
    vector<vector<char>> grid;
public:
    Grid() {
        row_size = col_size = 9;
        grid.resize(row_size, vector<char> (col_size));
        clear();
    }
    void clear();
    void display();
};

void Grid :: clear() {
    for(int i = 0; i < row_size; i ++) {
        for(int j = 0; j < col_size; j ++) {
            grid[i][j] = ' ';
        }
    }
}

void Grid :: display() {
    for(int j = 0; j < 9; j ++) {
        cout << "__";
    }
    cout << "________";
    cout << endl << endl;
    for(int i = 0; i < row_size; i ++) {
        if(i == 3 || i == 6) cout << endl;
        cout << "| ";
        for(int j = 0; j < 3; j ++) {
            cout << grid[i][j] << " ";
        }
        cout << "| ";
        for(int j = 0; j < 3; j ++) {
            cout << grid[i][j] << " ";
        }
        cout << "| ";
        for(int j = 0; j < 3; j ++) {
            cout << grid[i][j] << " ";
        }
        cout << "| ";
        cout << endl;
        if(i != 2 && i != 5 && i != 8) continue;
        for(int j = 0; j < 9; j ++) {
            cout << "__";
        }
        cout << "________";
        cout << endl;
    }
    cout << endl;
}


#endif // GRID_H
