/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>

using namespace std;


Labirinth::Labirinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labirinth[i][j] = values[i][j];

    this->initializeVisited();
}


void Labirinth::initializeVisited() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;
}


void Labirinth::printLabirinth() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << labirinth[i][j] << " ";

        cout << endl;
    }
}


bool Labirinth::findGoal(int x, int y) {
    // check if already visited
    if (!visited[x][y])
        visited[x][y] = true;
    else
        return false;

    if (labirinth[x][y] == 2) // check if is solution
        return true;
    else if (labirinth[x][y] == 0)  // check if it is wall
        return false;
    else    // check up, down , left, right
        return (findGoal(x+1,y) || findGoal(x-1,y) || findGoal(x,y+1) || findGoal(x,y-1));

}

/* 1.b) Tempo de execução no pior caso (pesquisa exaustiva do espaço de estados) é determinado pela dimensão do espaço
 * de estados, que muitas vezes é exponencial.
 */
