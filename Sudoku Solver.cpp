//Sudoku Solver
#include <iostream>
using namespace std;
// Display Sudoku
void displayGrid(int grid[9][9])
{
    cout << "\n===== Sudoku Solution =====\n";
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << grid[row][col] << " ";

            if ((col + 1) % 3 == 0)
                cout << "  ";
        }
        cout << endl;
        if ((row + 1) % 3 == 0)
            cout << endl;
    }
}
// Check if number can be placed
bool isSafe(int grid[9][9], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (grid[row][i] == num)
            return false;
    }
    // Check column
    for (int i = 0; i < 9; i++)
    {
        if (grid[i][col] == num)
            return false;
    }
    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}
// Solve Sudoku using backtracking
bool solveSudoku(int grid[9][9])
{
    int row = -1;
    int col = -1;
    bool emptyCell = false;
    // Find an empty cell
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                emptyCell = true;
                break;
            }
        }
        if (emptyCell)
            break;
    }
    // If there is no empty cell, Sudoku is solved
    if (!emptyCell)
        return true;
    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            // Recursively solve remaining cells
            if (solveSudoku(grid))
                return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }
    return false;
}
int main()
{
    int grid[9][9] =
    {
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
    cout << "===== Sudoku Solver =====\n";
    cout << "\nOriginal Sudoku:\n";
    displayGrid(grid);
    if (solveSudoku(grid))
    {
        cout << "\nSudoku solved successfully!\n";
        displayGrid(grid);
    }
    else
    {
        cout << "\nNo solution exists for this Sudoku.\n";
    }
    return 0;
}
