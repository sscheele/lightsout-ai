#include "lightboard.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int makeBestMove(LightBoard*);

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
    int currEdgeNum = l.getNumEdges();
    cout << currEdgeNum << '\n';
    l.writeBoard(); 
    while (currEdgeNum > 0){
        currEdgeNum = makeBestMove(&l);
        cout << "Reached " << currEdgeNum << " edges\n";
    }
    cout << currEdgeNum << " edges, done!\n";
    l.writeBoard();
    return 0;
}

int makeBestMove(LightBoard *l){
    int minEdgeNum = l->getNumEdges();
    int minEdgeRow = -1;
    int minEdgeCol = -1;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            l->toggle(row, col);
            int n = l->getNumEdges();
            if (n <= minEdgeNum) {
                minEdgeNum = n;
                minEdgeRow = row;
                minEdgeCol = col;
            }
            l->toggle(row, col);
        }
    }
    if (minEdgeRow == -1) return 1;
    l->toggle(minEdgeRow, minEdgeCol);
    return minEdgeNum;
}