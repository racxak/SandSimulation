#include <iostream>

using namespace std;

const char AIR = '.';
const char WALL = '#';
const char SAND = 'o';
const char ENTRY = '+';

struct Point {
    int x, y;
};

Point dropSand(char** tab, int tabSizeY, int tabSizeX, Point entryPoint) {
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

void fillRectangle(char** tab, int tabSizeY, int tabSizeX, int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            if (i >= 0 && i < tabSizeX && j >= 0 && j < tabSizeY) {
                tab[j][i] = WALL;
            }
        }
    }
}

int main() {
    int tabSizeY, tabSizeX;
    while (true) {
        cout << "Enter height and width of the map (for example 10 10): ";
        cin >> tabSizeY >> tabSizeX;

        if (tabSizeY >= 5 && tabSizeY <= 100 && tabSizeX >= 5 && tabSizeX <= 100) {
            break; 
        } else {
            cout << "Enter values between 5 and 100 for height and width of the map." << endl;
        }
    }

    char** tab = new char*[tabSizeY];
    for (int i = 0; i < tabSizeY; ++i) {
        tab[i] = new char[tabSizeX];
    }

    int sandCount = 0;

    for (int i = 0; i < tabSizeY; ++i) {
        for (int j = 0; j < tabSizeX; ++j) {
            tab[i][j] = AIR;
        }
    }

char command;
    cout << "Enter rectangles (format: r x1 y1 x2 y2). Enter s (format: x y) to set the start position and start the simulation." << endl;
    Point entryPoint = {-1, -1}; 

    while (cin >> command) {
        if (command == 'r') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            fillRectangle(tab, tabSizeY, tabSizeX, x1, y1, x2, y2);
        } else if (command == 's') {
            int x, y;
            cin >> x >> y;
            while (true) {
                if (x >= 0 && x < tabSizeX && y >= 0 && y < tabSizeY) {
                    break; 
                } else {
                    cout << "Enter values that will fit in the map area." << endl;
                    cin >> x >> y;
                }
            }
            entryPoint = {x, y};
            tab[entryPoint.y][entryPoint.x] = ENTRY;
            break; 
        } else {
            cout << "Invalid command. Use 'r' for rectangles and 's' for start position." << endl;
        }
    }

    Point newEntryPoint;
    while (true) {
        newEntryPoint = dropSand(tab, tabSizeY, tabSizeX, entryPoint);

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

    for (int i = 0; i < tabSizeY; ++i) {
        delete[] tab[i];
    }
    delete[] tab;

    return 0;
}
