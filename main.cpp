#include <Grid.h>
#include<windows.h>

bool place_block(Grid* grid, Block* block) {
    /*
    TODO:
    Implement this here or user another header file if needed

    return false if it is possible to place the block, that is where the game ends
    */
    return true;
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
            grid -> display();
            display_blocks(b1, b2, b3);

            cout << "Enter the number of the block 1 or 2 or 3" << endl;
            cin >> ch;

            system("cls");

        } while(ch != 1 && ch != 2 && ch != 3);

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

        if(! place_block(grid, selected_block)) {
            // calculate and update the score and exit
        }
    }

}


int main() {

    start();

    return 0;
}
