#include <Grid.h>



void change_pos(int& x, int& y, char ch, Grid* grid) {
    int px = x, py = y;

    while(1) {
        switch(ch) {
        case 'l':
            y -= 1;
            break;
        case 'r':
            y += 1;
            break;
        case 'u':
            x -= 1;
            break;
        case 'd':
            x += 1;
            break;
        }

        if((x >= 9) || (y >= 9) || (x < 0) || (y < 0) || (ch == 'w')) {
            system("cls");
            grid -> display();
            cout << "Enter l, r, u, d to do Left, Right, Up or Down: \t";
            cin >> ch;
        } else break;
    }
}

void place_block(Grid* grid, Block* block) {
    char ch;
    int x = 0, y = 0;

    while(1) {
        bool is_possible = grid -> is_possible(block, x, y);

        if(is_possible) {
            grid -> place_block(x, y, block);

            do {
                system("cls");
                grid -> display();
                cout << "Enter l, r, u, d, f to do Left, Right, Up, Down or fix: \t";
                fflush(stdin);
                cin >> ch;
            } while(ch != 'l' && ch != 'r' && ch != 'u' && ch != 'd' && ch != 'f');

            if(ch == 'f') {
                    grid -> fix_block(x, y, block);
                    grid -> handle_blast_case();
                    return;
            }

            grid -> remove_block(x, y, block);
            change_pos(x, y, ch, grid);
        } else {
            char past = grid -> grid[x][y];
            grid -> grid[x][y] = '*';
            system("cls");
            grid -> display();
            int px = x, py = y;

             char ch;
             do {
                system("cls");
                grid -> display();
                cout << "Enter l, r, u, d, f to do Left, Right, Up, Down: \t";
                fflush(stdin);
                cin >> ch;
            } while(ch != 'l' && ch != 'r' && ch != 'u' && ch != 'd');

            change_pos(x, y, ch, grid);
            grid -> grid[px][py] = past;
        }
    }
}

void start() {

    Grid* grid = new Grid;

    // b1, b2, b3 are the 3 blocks the user needs to choose from
    Block* b1 = get_block();
    Block* b2 = get_block();
    Block* b3 = get_block();


    while(1) {

        int ch;
        do {
            system("cls");
            grid -> display();
            display_blocks(b1, b2, b3);

            cout << "Enter the number of the block 1 or 2 or 3 or -1 to exit\t";
            cin >> ch;
        } while(ch != 1 && ch != 2 && ch != 3 && ch != - 1);

        if(ch == -1) {
            grid -> display_score();
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            exit(0);
        }

        Block* selected_block;
        if(ch == 1) {
            selected_block = b1;
            b1 = get_block(); // replace the taken block with a new one
        } else if(ch == 2) {
            selected_block = b2;
            b2 = get_block();
        } else {
            selected_block = b3;
            b3 = get_block();
        }

        place_block(grid, selected_block);
    }
}


int main() {

    start();

    return 0;
}
