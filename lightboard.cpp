#include <iostream>
#include <cstring>
#include "lightboard.h"

using namespace std;

LightBoard::LightBoard(bool l[BOARD_SIZE][BOARD_SIZE])
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            Light tmp = {};
            tmp.isOn = l[r][c];
            tmp.groupNum = -1;
            lights[r][c] = tmp;
        }
    }
    markGroups();
    //memcpy(lights, l, BOARD_SIZE * BOARD_SIZE * sizeof(bool));
}

void LightBoard::markGroups()
{
    //GROUP NUMBER MEANINGS: -1 empty, 0 unassigned, 1+ assigned
    int groupNum = 1;
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (lights[r][c].isOn) lights[r][c].groupNum = 0;
        }
    }
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (!lights[r][c].isOn || lights[r][c].groupNum > 0)
                continue;
            markAround(r, c, groupNum);
            groupNum++;
        }
    }
}

void LightBoard::markAround(int r, int c, int groupNum)
{
    lights[r][c].groupNum = groupNum;
    if (trueAt(r - 1, c) && gNumAt(r - 1, c) != groupNum)
        markAround(r - 1, c, groupNum);
    if (trueAt(r + 1, c) && gNumAt(r + 1, c) != groupNum)
        markAround(r + 1, c, groupNum);
    if (trueAt(r, c - 1) && gNumAt(r, c - 1) != groupNum)
        markAround(r, c - 1, groupNum);
    if (trueAt(r, c + 1) && gNumAt(r, c + 1) != groupNum)
        markAround(r, c + 1, groupNum);
}

bool LightBoard::trueAt(int r, int c)
{
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
        return false;
    return lights[r][c].isOn;
}

int LightBoard::gNumAt(int r, int c)
{
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
        return -1;
    return lights[r][c].groupNum;
}

int LightBoard::getNumEdges()
{
    int total = 0;
    //all vals start as 0
    int vertices[BOARD_SIZE + 1][BOARD_SIZE + 1];
    for (int r = 0; r < BOARD_SIZE + 1; r++)
    {
        for (int c = 0; c < BOARD_SIZE + 1; c++)
        {
            vertices[r][c] = -1;
        }
    }
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (!lights[row][col].isOn)
                continue;
            int currGroupNum = lights[row][col].groupNum;
            //only flip if no element across diagonal FROM SAME GROUP
            if (!trueAt(row - 1, col - 1) || gNumAt(row - 1, col - 1) != currGroupNum)
            {
                total += vertices[row][col] == currGroupNum ? -1 : 1;
                vertices[row][col] = currGroupNum;
            }
            if (!trueAt(row + 1, col - 1) || gNumAt(row + 1, col - 1) != currGroupNum)
            {
                total += vertices[row + 1][col] == currGroupNum ? -1 : 1;
                vertices[row + 1][col] = currGroupNum;
            }
            if (!trueAt(row + 1, col + 1) || gNumAt(row + 1, col + 1) != currGroupNum)
            {
                total += vertices[row + 1][col + 1] == currGroupNum ? -1 : 1;
                vertices[row + 1][col + 1] = currGroupNum;
            }
            if (!trueAt(row - 1, col + 1) || gNumAt(row - 1, col + 1) != currGroupNum)
            {
                total += vertices[row][col + 1] == currGroupNum ? -1 : 1;
                vertices[row][col + 1] = currGroupNum;
            }
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

void LightBoard::writeGroupNums()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            cout << lights[row][col].groupNum << " ";
        }
        cout << '\n';
    }
}

void LightBoard::toggle(int r, int c)
{
    for (int a = -1; a < 2; a++)
    {
        if (r + a < 0 || r + a >= BOARD_SIZE)
            continue;
        for (int b = -1; b < 2; b++)
        {
            if (c + b < 0 || c + b >= BOARD_SIZE)
                continue;
            if (lights[r+a][c+b].isOn){
                lights[r+a][c+b].isOn = false;
                lights[r+a][c+b].groupNum = -1;
            } else {
                lights[r+a][c+b].isOn = true;
            }
        }
    }
    markGroups();
}
