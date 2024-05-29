#include <iostream>

using namespace std;

const int tabSizeY = 7;
const int tabSizeX = 9;

const char AIR = '.';
const char WALL = '#';
const char SAND = 'o';
const char ENTRY = '+';

struct Point {
    int x, y;
};

Point dropSand(char tab[tabSizeY][tabSizeX], Point entryPoint) {
    Point newEntryPoint = entryPoint;

    while (true) {
        if (newEntryPoint.y == 0) {
            tab[newEntryPoint.y][newEntryPoint.x] = AIR;
            break;
        }

        if (tab[newEntryPoint.y - 1][newEntryPoint.x] == AIR) {
            tab[newEntryPoint.y][newEntryPoint.x] = AIR;
            tab[newEntryPoint.y - 1][newEntryPoint.x] = SAND;
            newEntryPoint.y -= 1;
        }
        else if (newEntryPoint.x < tabSizeX - 1 && tab[newEntryPoint.y - 1][newEntryPoint.x + 1] == AIR) {
            tab[newEntryPoint.y][newEntryPoint.x] = AIR;
            tab[newEntryPoint.y - 1][newEntryPoint.x + 1] = SAND;
            newEntryPoint.y -= 1;
            newEntryPoint.x += 1;
        }
        else if (newEntryPoint.x > 0 && tab[newEntryPoint.y - 1][newEntryPoint.x - 1] == AIR) {
            tab[newEntryPoint.y][newEntryPoint.x] = AIR;
            tab[newEntryPoint.y - 1][newEntryPoint.x - 1] = SAND;
            newEntryPoint.y -= 1;
            newEntryPoint.x -= 1;
        }
        else {
            break;
        }
    }

    return newEntryPoint;
}

int main() {
    char tab[tabSizeY][tabSizeX];
    int sandCount = 0;

    for (int i = 0; i < tabSizeY; ++i) {
        for (int j = 0; j < tabSizeX; ++j) {
            tab[i][j] = AIR;
        }
    }

    for (int i = 2; i < 8; ++i) {
        tab[1][i] = WALL;
    }
   
    Point entryPoint = {4, 4};
    tab[entryPoint.y][entryPoint.x] = ENTRY;

    Point newEntryPoint;
    while (true) {
        newEntryPoint = dropSand(tab, entryPoint);

        if (newEntryPoint.y == 0) {
            break;
        }

        if (newEntryPoint.x == entryPoint.x && newEntryPoint.y == entryPoint.y) {
            break;
        }
    }

    tab[entryPoint.y][entryPoint.x] = ENTRY;

    for (int i = tabSizeY - 1; i >= 0; --i) {
        for (int j = 0; j < tabSizeX; ++j) {
            cout << tab[i][j] << ' ';
            if (tab[i][j] == SAND){
                sandCount++;
            }
        }
        cout << endl;
    }
   
    cout << "Ziarenka: " << sandCount << endl;

    return 0;
}
