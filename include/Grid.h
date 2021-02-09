#ifndef GRID_H
#define GRID_H

#include<Block.h>

class Grid {
    int row_size, col_size;
    int score;
public:
    vector<vector<char>> grid;
    Grid() {
        row_size = col_size = 9;
        grid.resize(row_size, vector<char> (col_size));
        clear();
        score = 0;
    }
    void clear();
    void display();

    bool is_single(int, int);
    bool is_hor_bar(int, int);
    bool is_ver_bar(int, int);
    bool is_l(int, int);
    bool is_mirror_l(int, int);
    bool is_square(int, int);
    bool is_t(int, int);
    bool is_inv_t(int, int);
    bool is_z(int, int);
    bool is_possible(Block*, int, int); // Block, position

    void place_block(int, int, Block*);
    void remove_block(int, int, Block*);
    void fix_block(int, int, Block*);
    void fill_block(int, int, Block*, char);

    void fill_single(int x, int y, char);
    void fill_hor_bar(int x, int y, char);
    void fill_ver_bar(int x, int y, char);
    void fill_l(int x, int y, char);
    void fill_mirror_l(int x, int y, char);
    void fill_square(int x, int y, char);
    void fill_t(int x, int y, char);
    void fill_inv_t(int x, int y, char);
    void fill_z(int x, int y, char);

    void highlight(int, int);

    void handle_blast_case();
    vector<int> get_full_rows();
    vector<int> get_full_cols();
    void handle_full_sqs(int&);

    void update_score(int);
    void display_score();

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
        for(int j = 3; j < 6; j ++) {
            cout << grid[i][j] << " ";
        }
        cout << "| ";
        for(int j = 6; j < 9; j ++) {
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



/* =============================== BLAST CASE ==================================== */



vector<int> Grid :: get_full_rows() {
    vector<int> full_rows;
    for(int i = 0; i < row_size; i ++) {
        int is_full = 1;
        for(int j = 0; j < col_size; j ++) {
            is_full &= (grid[i][j] == 'o');
        }
        if(is_full) full_rows.push_back(i);
    }
    return full_rows;
}

vector<int> Grid :: get_full_cols() {
    vector<int> full_cols;
    for(int i = 0; i < col_size; i ++) {
        int is_full = 1;
        for(int j = 0; j < row_size; j ++) {
            is_full &= (grid[j][i] == 'o');
        }
        if(is_full) full_cols.push_back(i);
    }
    return full_cols;
}

void Grid :: handle_full_sqs(int &count) {
    for(int i = 0; i < row_size; i += 3) {
        for(int j = 0; j < col_size; j += 3) {
            int is_full = 1;
            for(int m = 0; m < 3; m ++) {
                for(int n = 0; n < 3; n ++) {
                    is_full &= (grid[i + m][j + n] == 'o');
                }
            }
            if(is_full) {
                count ++;
                for(int m = 0; m < 3; m ++) {
                    for(int n = 0; n < 3; n ++) {
                        grid[i + m][j + n] = ' ';
                    }
                }
            }
        }
    }
}

void Grid :: handle_blast_case() {
    static int score = 0;
    int count = 0;
    vector<int> rows_blast = get_full_rows();
    vector<int> cols_blast = get_full_cols();
    handle_full_sqs(count);
    for(int r : rows_blast) {
            count ++;
            for(int j = 0; j < col_size; j ++) {
                    grid[r][j] = ' ';
            }
    }
    for(int c : cols_blast) {
            count ++;
            for(int j = 0; j < row_size; j ++) {
                    grid[j][c] = ' ';
            }
    }
    if(count > 0) {
        system("cls");
        cout << "sweet...\t+" << count * 10 << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        score += count * 10;
        update_score(score);
        this -> score = score;
    }
}



/* ====================== IS POSSIBLE =========================== */



bool Grid :: is_possible(Block* b, int x, int y) {
    switch(b -> type) {
    case 0:
        return is_single(x, y);
    case 1:
        return is_hor_bar(x, y);
    case 2:
        return is_ver_bar(x, y);
    case 3:
        return is_square(x, y);
    case 4:
        return is_l(x, y);
    case 5:
        return is_mirror_l(x, y);
    case 6:
        return is_t(x, y);
    case 7:
        return is_inv_t(x, y);
    case 8:
        return is_z(x, y);
    }
}

bool Grid :: is_single(int x, int y) {
    return grid[x][y] == ' ';
}

bool Grid :: is_hor_bar(int x, int y) {
    if(y >= col_size - 2) return false;
    return grid[x][y] == ' ' && grid[x][y + 1] == ' ' && grid[x][y + 2] == ' ';
}

bool Grid :: is_ver_bar(int x, int y) {
    if(x >= row_size - 2) return false;
    return grid[x][y] == ' ' && grid[x + 1][y] == ' ' && grid[x + 2][y] == ' ';
}

bool Grid :: is_square(int x, int y) {
    if(x >= row_size - 1 || y >= col_size - 1) return false;
    int possible = true;
    for(int i = 0; i < 2; i ++) {
        for(int j = 0; j < 2; j ++) {
            possible &= (grid[x + i][y + j] == ' ');
        }
    }
    return possible;
}

bool Grid :: is_l(int x, int y) {
    if(x + 1 >= row_size || y + 1 >= col_size) return false;
    return grid[x][y] == ' ' && grid[x + 1][y] == ' ' && grid[x + 1][y + 1] == ' ';
}

bool Grid :: is_mirror_l(int x, int y) {
    if(y == 0 || x + 1 >= row_size) return false;
    return grid[x][y] == ' ' && grid[x + 1][y - 1] == ' ' && grid[x + 1][y] == ' ';
}

bool Grid :: is_t(int x, int y) {
     if(y == 0 || x + 1 >= row_size || y + 1 >= col_size) return false;
     return grid[x][y] == ' ' && grid[x + 1][y - 1] == ' ' && grid[x + 1][y] == ' ' && grid[x + 1][y + 1] == ' ';
}

bool Grid :: is_inv_t(int x, int y) {
    if(x + 1 >= row_size || y + 1 >= col_size || y == 0) return false;
    return grid[x][y] == ' ' && grid[x + 1][y - 1] == ' ' && grid[x + 1][y] == ' ' && grid[x + 1][y + 1] == ' ';
}

bool Grid :: is_z(int x, int y) {
    if(x + 2 >= row_size || y + 2 >= col_size) return false;
    return grid[x][y] == ' ' && grid[x][y + 1] == ' ' && grid[x + 1][y + 1] == ' ' && grid[x + 2][y + 1] == ' ' && grid[x + 2][y + 2];
}



/* ======================= FILL BLOCKS: PLACE, REMOVE, FIX ============================ */



void Grid :: place_block(int x, int y, Block* b) {
    fill_block(x, y, b, '*');
}

void Grid :: remove_block(int x, int y, Block* b) {
    fill_block(x, y, b, ' ');
}

void Grid :: fix_block(int x, int y, Block* b) {
    fill_block(x, y, b, 'o');
}

void Grid :: fill_block(int x, int y, Block* b, char ch) {
     switch(b -> type) {
    case 0:
        fill_single(x, y, ch);
        break;
    case 1:
        fill_hor_bar(x, y, ch);
        break;
    case 2:
        fill_ver_bar(x, y, ch);
        break;
    case 3:
        fill_square(x, y, ch);
        break;
    case 4:
        fill_l(x, y, ch);
        break;
    case 5:
        fill_mirror_l(x, y, ch);
        break;
    case 6:
        fill_t(x, y, ch);
        break;
    case 7:
        fill_inv_t(x, y, ch);
        break;
    case 8:
        fill_z(x, y, ch);
        break;
    }
}

void Grid :: fill_single(int x, int y, char ch) {
    grid[x][y] = ch;
}

void Grid :: fill_hor_bar(int x, int y, char ch) {
    grid[x][y] = grid[x][y + 1] = grid[x][y + 2] = ch;
}

void Grid :: fill_ver_bar(int x, int y, char ch) {
    grid[x][y] = grid[x + 1][y] = grid[x + 2][y] = ch;
}

void Grid :: fill_square(int x, int y, char ch) {
    grid[x][y] = grid[x + 1][y] = grid[x][y + 1] = grid[x + 1][y + 1] = ch;
}

void Grid :: fill_l(int x, int y, char ch) {
    grid[x][y] = grid[x + 1][y] = grid[x + 1][y + 1] = ch;
}

void Grid :: fill_mirror_l(int x, int y, char ch) {;
    grid[x][y] = grid[x + 1][y - 1] = grid[x + 1][y] = ch;
}

void Grid :: fill_t(int x, int y, char ch) {
     grid[x][y] = grid[x + 1][y - 1] = grid[x + 1][y] = grid[x + 1][y + 1] = ch;
}

void Grid :: fill_inv_t(int x, int y, char ch) {
    grid[x][y] = grid[x + 1][y - 1] = grid[x + 1][y] = grid[x + 1][y + 1] = ch;
}

void Grid :: fill_z(int x, int y, char ch) {
    grid[x][y] = grid[x][y + 1] = grid[x + 1][y + 1] = grid[x + 2][y + 1] = grid[x + 2][y + 2] = ch;
}

/* ============================= SCORE ================================= */


void Grid :: update_score(int score) {
    int high_so_far;
    fstream fstr;
    fstr.open("high_score.txt", ios :: in);
    fstr >> high_so_far;
    fstr.close();
    if(score > high_so_far) {
        fstr.open("high_score.txt", ios :: out);
        fstr << score;
        fstr.close();
    }
}

void Grid :: display_score() {
    system("cls");
    cout << "Score: " << score << endl;
     int high_so_far;
    fstream fstr;
    fstr.open("high_score.txt", ios :: in);
    fstr >> high_so_far;
    cout << "High Score: " << high_so_far << endl;
    if(score == high_so_far) {
        cout << "Made it, Ma! Top of the world!" << endl;
    } else {
        cout << "Instead of giving up, TRY AGAIN!" << endl;
    }
}

#endif // GRID_H
