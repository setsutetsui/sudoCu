#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu() {
    int choice = 0;
    int key;
    const char *options[4] = {"New Game", "Load Game", "Settings", "Exit"};

    WINDOW *menuwin = newwin(10, 60, 1, 1);
    box(menuwin, 0, 0);
    keypad(menuwin, TRUE);

    // Hide the cursor
    curs_set(0);

    while (1) {
        mvwprintw(menuwin, 1, 2, "sudoCu");

        for (int i = 0; i < 4; i++) {
            if (i == choice) {
                wattron(menuwin, A_BOLD);
                wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i + 3, 2, options[i]);
                wattroff(menuwin, A_BOLD);
                wattroff(menuwin, A_REVERSE);
            } else {
                mvwprintw(menuwin, i + 3, 2, options[i]);
            }
        }

        wrefresh(menuwin);
        key = wgetch(menuwin);

        switch(key) {
            case KEY_UP:
                choice = (choice == 0) ? 3 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == 3) ? 0 : choice + 1;
                break;
            case '\n': // Enter key
                delwin(menuwin);
                return choice;
        }
    }
}

int (*generateBoard())[9] {
    static int board[9][9];

    srand(time(NULL));
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = rand() % (9 - 1 + 1) + 1; // Initialize with some values
        }
    }

    return board;
}

void drawSudokuGrid() {
    // Draw the main grid
    for (int i = 0; i <= 18; i++) {
        for (int j = 0; j <= 36; j++) {
            if (i % 6 == 0 && j % 12 == 0) {
                mvaddch(i, j, '+');
            } else if (i % 6 == 0) {
                mvaddch(i, j, '-');
            } else if (j % 12 == 0) {
                mvaddch(i, j, '|');
            }
        }
    }
}

void drawSudokuNumbers(int (*board)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mvprintw(i * 2 + 1, j * 4 + 1, " %d", board[i][j]);
        }
    }
}

void newGame() {
    int (*board)[9] = generateBoard();
    clear();

    drawSudokuGrid();
    drawSudokuNumbers(board);

    refresh();
    getch(); // Wait for user input before returning
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int gameState = menu();

    clear();
    refresh();

    switch(gameState) {
        case 0:
            newGame();
            break;
        case 1:
            printw("Load Game");
            break;
        case 2:
            printw("Settings");
            break;
        case 3:
            printw("Exit");
            break;
    }

    refresh(); // Refresh the standard screen to show the output
    getch(); // Wait for user input before exiting

    endwin(); // End ncurses mode

    return 0;
}