#ifndef BLOCK_H
#define BLOCK_H

#include<iostream>
#include <vector>
#include <utility> // for pair
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;


class Block {
private:
    int x, y; // coordinates on the grid
protected:
    vector<vector<char>> shape;
public:
    int type;
    void set_position(int x, int y) {
        this -> x = x;
        this -> y = y;
    }
    pair<int, int> get_position() {
        return make_pair(x, y);
    }
    vector<vector<char>> get_shape() {
        return shape;
    }
    void display();
};

void Block :: display() {
    for(auto row : shape) {
        for(char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

/**

===============================
Blocks used are:
1. Single
2. Two horizontal, aka call it hor_bar
3. Two vertical, aka it ver_bar
4. 4 blocks square, aka square
5. L shaped, aka l
6. Mirror of L ,aka mirror_l
7. Inverted T shaped - 3 blocks horizontally + 1 block above the middle one, aka inv_t
8. T shaped - 3 blocks horizontally + 1 block below the middle one, aka t
9. Weird Z block, aka z

===============================

**/


class Block_single: public Block {
public:
    Block_single() {
        set_shape();
        type = 0;
    }
    void set_shape() {
        shape.push_back({'o'});
    }
};

class Block_hor_bar: public Block {
public:
    Block_hor_bar() {
        set_shape();
        type = 1;
    }
    void set_shape() {
        shape.push_back({'o', 'o', 'o'});
    }
};

class Block_ver_bar: public Block {
public:
    Block_ver_bar() {
        set_shape();
        type = 2;
    }
    void set_shape() {
        shape.push_back({'o'});
        shape.push_back({'o'});
        shape.push_back({'o'});
    }
};

class Block_square: public Block {
public:
    Block_square() {
        set_shape();
        type = 3;
    }
    void set_shape() {
        shape.push_back({'o', 'o'});
        shape.push_back({'o', 'o'});
    }
};

class Block_l: public Block {
public:
    Block_l() {
        set_shape();
        type = 4;
    }
    void set_shape() {
        shape.push_back({'o'});
        shape.push_back({'o', 'o'});
    }
};

class Block_mirror_l: public Block {
public:
    Block_mirror_l() {
        set_shape();
        type = 5;
    }
    void set_shape() {
        shape.push_back({' ' , 'o'});
        shape.push_back({'o', 'o'});
    }
};

class Block_t: public Block {
public:
    Block_t() {
        set_shape();
        type = 6;
    }
    void set_shape() {
        shape.push_back({'o', 'o', 'o'});
        shape.push_back({' ' , 'o'});
    }
};

class Block_inv_t: public Block {
public:
    Block_inv_t() {
        set_shape();
        type = 7;
    }
    void set_shape() {
        shape.push_back({' ' , 'o'});
        shape.push_back({'o', 'o', 'o'});
    }
};

class Block_z: public Block {
public:
    Block_z() {
        set_shape();
        type = 8;
    }
    void set_shape() {
        shape.push_back({'o', 'o'});
        shape.push_back({' ' , 'o'});
        shape.push_back({' ' , 'o', 'o'});
    }
};




// utility functions -----------



Block* get_block() {
    Block* b;
    int c = rand() % 9;
    switch(c) {
    case 0:
        b = new Block_single;
        break;
    case 1:
        b = new Block_hor_bar;
        break;
    case 2:
        b = new Block_ver_bar;
        break;
    case 3:
        b = new Block_l;
        break;
    case 4:
        b = new Block_mirror_l;
        break;
    case 5:
        b = new Block_square;
        break;
    case 6:
        b = new Block_t;
        break;
    case 7:
        b = new Block_inv_t;
        break;
    case 8:
        b = new Block_z;
        break;
    }
    return b;
}

void display_blocks(Block* b1, Block* b2, Block* b3) {

    cout << "1." << endl;
    b1 -> display();
    cout << endl << endl;

    cout << "2." << endl;
    b2 -> display();
    cout << endl << endl;

    cout << "3." << endl;
    b3 -> display();
    cout << endl;

}

#endif // BLOCK_H
