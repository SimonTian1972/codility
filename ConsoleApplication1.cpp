#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <iostream>
using namespace std;




#include <stdio.h>
#include <stdbool.h>


bool can_go(int** visit, bool* game_matrix, int rows, int cols, int from_row,
    int from_column, int to_row, int to_column, int rowStep, int colStep) {
    if (from_row < 0 || from_row >= rows) {
        return false;
    }
    if (from_column < 0 || from_column >= cols) {
        return false;
    }
    if (visit[from_row][from_column] != 0) {
        return false;
    }
    visit[from_row][from_column] = 1;

    if ((game_matrix + from_row * cols)[from_column] == false) {
        return false;
    }
    if (from_row == to_row && from_column == to_column) {
        return true;
    }

    if (can_go(visit, game_matrix, rows, cols, from_row + rowStep,
        from_column, to_row, to_column, rowStep, colStep) == true) {
        return true;
    }

    if (can_go(visit, game_matrix, rows, cols, from_row,
        from_column + colStep, to_row, to_column, rowStep, colStep) == true) {
        return true;
    }

    
    return false;
}


bool can_travel_to1(bool* game_matrix, int rows, int cols, int from_row,
    int from_column, int to_row, int to_column)
{
    int** visit = (int **)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visit[i] = (int*)calloc(cols, sizeof(int));
    }
    int rowStep;
    if ((to_row - from_row) == 0) {
        rowStep = 0;
    } else {
        rowStep = (to_row - from_row) / abs(to_row - from_row);
    }
    int colStep;
    if (to_column - from_column == 0) {
        colStep = 0;
    }
    else {
        colStep = (to_column - from_column) / abs(to_column - from_column);
    }
    bool ret = true;
    if (from_row != to_row && from_column != to_column) {
        ret = false;
    } else if (from_row == to_row){
        for (int c = from_column; c != to_column; c = c + colStep) {
            if (game_matrix[from_row * cols + c] == false) {
                ret = false;
                break;
            }
        }
    } else {
        for (int r = from_row; r != to_row; r = r + rowStep) {
            if (game_matrix[r*cols + from_column] == false) {
                ret = false;
                break;
            }
        }
    }

    if (game_matrix[to_row * cols + to_column] == false)
    {
        ret = false;
    }

    // Write your code here
    for (int i = 0; i < rows; i++) {
        free(visit[i]);
    }
    free(visit);
    return ret;
}


#include <stdio.h>
#include <stdbool.h>


bool can_travel_to(bool* game_matrix, int rows, int cols, int from_row,
    int from_column, int to_row, int to_column)
{
    if (to_row < 0 || to_row >= rows || to_column < 0 || to_column >= cols)
    {
        return false;
    }

    if (from_row < 0 || from_row >= rows || from_column < 0 || from_column >= cols)
    {
        return false;
    }
    if (game_matrix[to_row * cols + to_column] == false) {
        return false;
    }

    if (game_matrix[from_row * cols + from_column] == false) {
        return false;
    }

    bool ret = true;
    if (from_row == to_row && from_column == to_column) {
        return true;
    } if (from_row != to_row && from_column != to_column) {
        return false;
    } else if (from_row == to_row) {
        int colStep = (to_column - from_column) / abs(to_column - from_column);
        for (int c = from_column; c != to_column; c = c + colStep) {
            if (game_matrix[from_row * cols + c] == false) {
                ret = false;
                break;
            }
        }
    } else { // from_column == to_column
        int rowStep = (to_row - from_row) / abs(to_row - from_row);
        for (int r = from_row; r != to_row; r = r + rowStep) {
            if (game_matrix[r * cols + from_column] == false) {
                ret = false;
                break;
            }
        }
    }

    return ret;
}


#ifndef RunTests
int main()
{
    bool game_matrix[6][6] = {
        {false, true,  true,  false, false, false},
        {true,  true,  true,  false, false, false},
        {true,  true,  true,  true,  true,  true},
        {false, true,  true,  false, true,  true},
        {false, true,  true,  true,  false, true},
        {false, false, false, false, false, false},
    };

    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 4, 2)); // true, Valid move
    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 3, 2)); // false, Can't travel through land
    printf("%d\n", can_travel_to((bool*)game_matrix, 6, 6, 3, 2, 2, 2)); // false, Out of bounds
}
#endif




