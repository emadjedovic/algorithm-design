#include "zadatak1.cpp"
#include "zadatak2.cpp"
#include "zadatak3.cpp"
#include "zadatak4.cpp"

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

    cout<<"Topolosko sortiranje: ";
    directedGraph6.topologicalSort();
    cout << endl;

    // Isti graf ali pravimo ciklus sada kako bismo ga detektovali topološkim sortom
    directedGraph6.addEdge(3, 5);

    cout << "Topolosko nad ciklicnim grafom:" << endl;
    directedGraph6.topologicalSort();
    cout << endl;

    return 0;
}
