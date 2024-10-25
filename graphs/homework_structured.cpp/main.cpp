#include "graph.cpp"
#include "zadatak1.cpp"
#include "zadatak2.cpp"
#include "zadatak3.cpp"
#include "zadatak4.cpp"
#include "zadatak5.cpp"
#include "zadatak6.cpp"

int main()
{
    cout << "--------------- ZADATAK 1\n\n";
    // put s-t (reachability)

    Graph directedGraph5(5, true);
    directedGraph5.addEdge(0, 1);
    directedGraph5.addEdge(1, 2);
    directedGraph5.addEdge(2, 3);
    directedGraph5.addEdge(1, 3);
    directedGraph5.addEdge(1, 4);

    // 0-1-3
    cout << "Put od 0 do 3: ";
    directedGraph5.pathFromTo(0, 3);
    cout << endl;

    // Ne postoji
    cout << "Put od 3 do 0: ";
    directedGraph5.pathFromTo(3, 0);
    cout << endl;

    cout << "--------------- ZADATAK 2\n\n";
    // detekcija ciklusa (neusmjeren graf)

    Graph undirectedGraph6(6, false);
    undirectedGraph6.addEdge(0, 1);
    undirectedGraph6.addEdge(1, 2);
    undirectedGraph6.addEdge(2, 0); // ciklus 0-1-2
    undirectedGraph6.addEdge(2, 4);
    undirectedGraph6.addEdge(3, 4);
    undirectedGraph6.addEdge(4, 5);
    undirectedGraph6.addEdge(5, 3); // ciklus 3-4-5

    // Imaju dva ciklusa (gore navedena).
    undirectedGraph6.cycle_detection_undirected();
    undirectedGraph6.printCycles();
    cout << endl;

    cout << "--------------- ZADATAK 3\n\n";
    // komponente povezanosti (neusmjeren graf)

    Graph undirectedGraph8(8, false);
    undirectedGraph8.addEdge(0, 1);
    undirectedGraph8.addEdge(1, 2);
    undirectedGraph8.addEdge(3, 4);
    undirectedGraph8.addEdge(5, 6);
    undirectedGraph8.addEdge(6, 7);

    // Tri komponente: 0-1-2, 3-4, 5-6-7
    undirectedGraph8.findComponents();
    cout << endl;

    cout << "--------------- ZADATAK 4\n\n";
    // topološko sortiranje (usmjeren graf)

    Graph directedGraph6(6, true);
    directedGraph6.addEdge(5, 2);
    directedGraph6.addEdge(5, 0);
    directedGraph6.addEdge(4, 0);
    directedGraph6.addEdge(4, 1);
    directedGraph6.addEdge(2, 3);
    directedGraph6.addEdge(3, 1);

    cout << "Topolosko sortiranje: ";
    directedGraph6.topologicalSort();
    cout << endl;

    // Isti graf ali pravimo ciklus sada kako bismo ga detektovali topološkim sortom
    directedGraph6.addEdge(3, 5);

    cout << "Topolosko nad ciklicnim grafom:" << endl;
    directedGraph6.topologicalSort();
    cout << endl;

    cout << "--------------- ZADATAK 5\n\n";

    Graph directedForDrawing(7, true);
    directedForDrawing.addEdge(0, 1);
    directedForDrawing.addEdge(1, 3);
    directedForDrawing.addEdge(1, 4);
    directedForDrawing.addEdge(1, 5);
    directedForDrawing.addEdge(0, 2);
    directedForDrawing.addEdge(2, 5);
    directedForDrawing.addEdge(0, 6);
    directedForDrawing.addEdge(6, 2);

    cout << "Adjacency list of directed:\n";
    directedForDrawing.printAdjacencyList();

    // konvertovan
    Graph gDraw = directedForDrawing.convertToUndirected();
    cout << "\nAdjacency list of undirected:\n";
    gDraw.printAdjacencyList();

    // dodjeljujemo koordinate
    gDraw.assignCoordinatesUsingBFS();
    cout << "\nCoordinates:\n";
    gDraw.printCoordinates();

    // crtamo graf
    cout << "\nDrawing the graph..." << endl;
    gDraw.drawGraph();

    directedForDrawing.drawInstantly();

    cout << "--------------- ZADATAK 6\n\n";

    Graph undirectedEuler(6, false);
    undirectedEuler.addEdge(0, 1);
    undirectedEuler.addEdge(0, 2);
    undirectedEuler.addEdge(0, 3);
    undirectedEuler.addEdge(1, 3);
    undirectedEuler.addEdge(2, 3);
    undirectedEuler.addEdge(3, 4);
    undirectedEuler.addEdge(3, 5);
    undirectedEuler.addEdge(4, 5);
    undirectedEuler.findEulerCircuit();

    Graph directedEuler(5, true);
    directedEuler.addEdge(0, 1);
    directedEuler.addEdge(1, 2);
    directedEuler.addEdge(2, 0);
    directedEuler.addEdge(1, 4);
    directedEuler.addEdge(4, 1);
    directedEuler.addEdge(0, 3);
    directedEuler.addEdge(3, 4);
    directedEuler.findEulerCircuit();

    cout << "--------------- ZADATAK 7\n\n";

    return 0;
}
