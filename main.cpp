#include "lightboard.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    bool lights[BOARD_SIZE][BOARD_SIZE];
    srand(time(NULL));
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            lights[row][col] = false;
            if (rand() % 2)
                lights[row][col] = true;
        }
    }
    LightBoard l(lights);
    cout << l.getNumEdges() << '\n';
    l.writeBoard();
    return 0;
}