#include "findGraph.h"
#include <iostream>

using namespace std;

int main()
{
    CGraph<int, int> algo;
    algo.insertarNodo(4);
    algo.insertarNodo(3);
    algo.insertarNodo(3);
    algo.insertarArista(7, 4, 3, 0);
    algo.insertarArista(6, 4, 3, 0);
    algo.insertarArista(5, 3, 4, 1);
    algo.eliminarArista(5, 3, 3);
    algo.imprimir();
    return 0;
}