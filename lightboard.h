#ifndef LIGHTBOARD_H
#define LIGHTBOARD_H

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
    int gNumAt(int, int);

  public:
    LightBoard(bool[BOARD_SIZE][BOARD_SIZE]);
    int getNumEdges();
    void writeBoard();
    void writeGroupNums();
    bool trueAt(int, int);
    void toggle(int, int);
};

#endif