#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define SIZE 9  // Sudoku grid size
#define NUM_THREADS 9

int sudoku[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

pthread_mutex_t mutex;  // Mutex for synchronization

// Function to check if placing a number is valid
bool isValid(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (sudoku[i + startRow][j + startCol] == num)
                return false;
    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int row, int col) {
    if (row == SIZE) return true;
    if (col == SIZE) return solveSudoku(row + 1, 0);
    if (sudoku[row][col] != 0) return solveSudoku(row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            sudoku[row][col] = num;
            if (solveSudoku(row, col + 1)) return true;
            sudoku[row][col] = 0;
        }
    }
    return false;
}

// Thread function to solve different sections
void* solveSection(void* arg) {
    int row = *(int*)arg;

    pthread_mutex_lock(&mutex);
    solveSudoku(row, 0);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Function to print the Sudoku grid
void printSudoku() {
    printf("\nSolved Sudoku:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rows[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    // Create threads to solve different parts
    for (int i = 0; i < NUM_THREADS; i++) {
        rows[i] = i;
        pthread_create(&threads[i], NULL, solveSection, &rows[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printSudoku();
    return 0;
}
