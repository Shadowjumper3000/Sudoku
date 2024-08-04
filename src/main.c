#include "main.h"

int sudokuField[9][3][3] = {
    {{7, 9, 4}, {0, 8, 0}, {0, 3, 2}},
    {{0, 2, 1}, {4, 0, 0}, {5, 9, 0}},
    {{3, 0, 5}, {0, 0, 0}, {0, 0, 4}},
    {{1, 3, 9}, {0, 6, 5}, {0, 2, 0}},
    {{0, 0, 0}, {2, 4, 3}, {0, 0, 0}},
    {{0, 4, 0}, {7, 0, 1}, {0, 0, 0}},
    {{4, 5, 3}, {0, 0, 0}, {8, 0, 0}},
    {{0, 6, 7}, {0, 5, 0}, {3, 0, 9}},
    {{0, 0, 8}, {3, 0, 0}, {0, 5, 0}}
};
int fixedNumbers[9][3][3] = {
    {{7, 9, 4}, {0, 8, 0}, {0, 3, 2}},
    {{0, 2, 1}, {4, 0, 0}, {5, 9, 0}},
    {{3, 0, 5}, {0, 0, 0}, {0, 0, 4}},
    {{1, 3, 9}, {0, 6, 5}, {0, 2, 0}},
    {{0, 0, 0}, {2, 4, 3}, {0, 0, 0}},
    {{0, 4, 0}, {7, 0, 1}, {0, 0, 0}},
    {{4, 5, 3}, {0, 0, 0}, {8, 0, 0}},
    {{0, 6, 7}, {0, 5, 0}, {3, 0, 9}},
    {{0, 0, 8}, {3, 0, 0}, {0, 5, 0}}
};


int inputting = 1;

int main() {
    do {
        printf("Welcome to Sudoku!\n");
        printField();
        //acceptField();
        do {
            printField();
            acceptInput();
        } while (inputting);
    solveField();
    printField();
    } while (loop());
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

int acceptField() {
    if (DEBUG) {printf("[DEBUG] Accepting input\n");}
    printf("Enter the Sudoku field (9x9 grid, use 0 for empty cells, fix any mistakes later):\n");
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int val;
            scanf("%d", &val);
            if (val < 0 || val > 9) {
                printf("Invalid input. Please enter numbers between 0 and 9.\n");
                return 1;
            }
            sudokuField[i][j / 3][j % 3] = val;
            fixedNumbers[i][j / 3][j % 3] = (val != 0); // Mark the position as fixed
            printField();
        }
    }
    
    clearScreen();
    return 0;
}

int acceptInput() {
    if (DEBUG) {printf("[DEBUG] Accepting input\n");}
    printf("If you wish to solve the field, Enter three 0's\nOtherwise Enter the row, column and value to change: ");

    int row, col, val;
    if (scanf("%d %d %d", &row, &col, &val) != 3) {
        printf("Invalid input. Please enter row and column between 1 and 9, and value between 0 and 9.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return 1;
    }
    if (row == 0 && col == 0 && val == 0) {
        inputting = 0;
        return 0;
    }
    if (row < 1 || row > 9 || col < 1 || col > 9 || val < 0 || val > 9) {
        printf("Invalid input. Please enter row and column between 1 and 9, and value between 0 and 9.\n");
        return 1;
    }

    row--, col--;
    sudokuField[row][col / 3][col % 3] = val;
    fixedNumbers[row][col / 3][col % 3] = (val != 0);
    while (getchar() != '\n'); // Clear the input buffer
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
    }
    return 1; // Return 1 when the puzzle is solved
}
