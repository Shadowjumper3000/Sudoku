#include "main.h"

int sudokuField[9][3][3] = {0};
int fixedNumbers[9][3][3] = {0}; // Array to mark fixed numbers

int main() {
    printf("Welcome to Sudoku!\n");
    do {
        printField();
        acceptInput();
    } while (1);
}

int printField() {
    clearScreen();
    if (DEBUG) {printf("[DEBUG] Printing field\n");}
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf(" -----------------------\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            int val = sudokuField[i][j / 3][j % 3];
            if (fixedNumbers[i][j / 3][j % 3]) {
                printf("\033[1;31m%d \033[0m", val); // Print fixed numbers in red
            } else {
                printf("%d ", val);
            }
        }
        printf("|\n");
    }
    printf(" -----------------------\n");
    return 0;
}

int checkInput(int row, int col, int val) {
    if (val == 0) {
        return 0; // Allow 0 as a valid input
    }

    // Check the row and column
    for (int i = 0; i < 9; i++) {
        if (sudokuField[row - 1][i / 3][i % 3] == val) {
            if (DEBUG) {printf("[DEBUG] Value already exists in row\n");}
            return 1;
        }
        if (sudokuField[i][col - 1][i / 3] == val) {
            if (DEBUG) {printf("[DEBUG] Value already exists in column\n");}
            return 1;
        }
    }

    // Check the 3x3 subgrid
    int startRow = (row - 1) / 3 * 3;
    int startCol = (col - 1) / 3 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudokuField[startRow + i][startCol / 3][startCol % 3 + j] == val) {
                if (DEBUG) {printf("[DEBUG] Value already exists in 3x3 subgrid\n");}
                return 1;
            }
        }
    }
    return 0;
}

int acceptInput() {
    if (DEBUG) {printf("[DEBUG] Accepting input\n");}
    printf("If you wish to solve the field, Enter \"s\"\nOtherwise Enter the column, row and value to change: ");
    int ch = getchar();
    if (ch == 's' || ch == 'S') {
        solveField();
        return 0; // Exit the function after solving the field
    }
    ungetc(ch, stdin); // Put the character back to the input stream
    int row, col, val;
    scanf("%d %d %d", &col, &row, &val);
    if (checkInput(row, col, val)) {
        return 1;
    }
    sudokuField[row - 1][(col - 1) / 3][(col - 1) % 3] = val;
    fixedNumbers[row - 1][(col - 1) / 3][(col - 1) % 3] = (val != 0); // Mark the position as fixed
    clearScreen();
    return 0;
}

int solveField() {
    if (DEBUG) {printf("[DEBUG] Solving field\n");}
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudokuField[i][j / 3][j % 3] == 0) {
                for (int k = 1; k <= 9; k++) {
                    if (!checkInput(i + 1, j + 1, k)) {
                        sudokuField[i][j / 3][j % 3] = k;
                        if (solveField()) {
                            return 1;
                        }
                        sudokuField[i][j / 3][j % 3] = 0;
                    }
                }
                return 0;
            }
        }
    printField();
    }
    return 1;
}