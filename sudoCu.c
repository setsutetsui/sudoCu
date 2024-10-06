#include <stdio.h>
#include <ncurses.h>
#include <string.h>

int menu() {
    int choice = 0;
    int key;
    const char *options[4] = {"New Game", "Load Game", "Settings", "Exit"};

    WINDOW *menuwin = newwin(10, 60, 1, 1);
    box(menuwin, 0, 0);
    keypad(menuwin, TRUE);

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
                return choice;
        }
    }
}

int[9][9] generateBoard() {
    int board[9][9];
    return board;
}

void newGame() {
    board = generateBoard();
}

int main() {
    static int board[9][9];
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int gameState = menu();

    clear();
    refresh();

    switch(gameState) {
        case 0:
            
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

    endwin();

    return 0;
}