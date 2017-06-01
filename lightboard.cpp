#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

const int BOARD_SIZE = 6;

struct Light
{
    bool isOn;
    int groupNum;
};

class LightBoard
{
    Light lights[BOARD_SIZE][BOARD_SIZE];
    void markGroups();
    void markAround(int, int, int);

  public:
    LightBoard(bool[BOARD_SIZE][BOARD_SIZE]);
    int getNumEdges();
    void writeBoard();
    bool trueAt(int, int);
};

LightBoard::LightBoard(bool l[BOARD_SIZE][BOARD_SIZE])
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            Light tmp = 0;
            tmp.isOn = l[r][c];
            tmp.groupNum = -1;
            lights[r][c] = tmp;
        }
    }

    //memcpy(lights, l, BOARD_SIZE * BOARD_SIZE * sizeof(bool));
}

void LightBoard::markGroups()
{
    int groupNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (!lights[r][c].isOn || lights[r][c].groupNum != -1)
                continue;
            markAround(r, c, groupNum);
            groupNum++;
        }
    }
}

void LightBoard::markAround(int r, int c, int groupNum){
    lights[r][c].groupNum = groupNum;
    if (lights[r-1][c].isOn) markAround(r-1, c, groupNum);
    if (lights[r+1][c].isOn) markAround(r+1, c, groupNum);
    if (lights[r][c-1].isOn) markAround(r, c-1, groupNum);
    if (lights[r][c+1].isOn) markAround(r, c+1, groupNum);
}

bool LightBoard::trueAt(int r, int c)
{
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
        return false;
    return lights[r][c].isOn;
}

int LightBoard::getNumEdges()
{
    int total = 0;
    //all vals start as 0
    int vertices[BOARD_SIZE + 1][BOARD_SIZE + 1] = {-1};
    int groupNum = 0 for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (lights[row][col])
            {
                //only flip if no element across diagonal FROM SAME GROUP
                if (!(trueAt(row - 1, col - 1) && lights[row-1][col-1].groupNum == lights[row][col].groupNum)){
                    vertices[row][col] = lights[row][col].groupNum;
                }
                    
                if (!trueAt(row + 1, col - 1))
                    vertices[row + 1][col] = !vertices[row + 1][col];
                if (!trueAt(row + 1, col + 1))
                    vertices[row + 1][col + 1] = !vertices[row + 1][col + 1];
                if (!trueAt(row - 1, col + 1))
                    vertices[row][col + 1] = !vertices[row][col + 1];
            }
        }
    }
    //yes, this could probably be done in better O(n) time, but the code looks nice this way
    for (int r = 0; r < BOARD_SIZE + 1; r++)
    {
        for (int c = 0; c < BOARD_SIZE + 1; c++)
        {
            if (vertices[r][c])
                total++;
        }
    }
    return total;
}

void LightBoard::writeBoard()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (trueAt(row, col))
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << '\n';
    }
}

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
