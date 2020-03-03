#include <iostream>
#include "newPath.h"
using namespace std;

int main() {
    Dis a;
    Dis b;
    Path for_a;
    for_a.addEdge(2, 1);
    for_a.addEdge(3, 1);
    a.addPath(for_a);
    Path for_a2;
    for_a2.addEdge(3, 2);
    for_a2.addEdge(4, 5);
    a.addPath(for_a2);

    Path for_b;
    for_b.addEdge(4, 2);
    for_b.addEdge(5, 3);
    b.addPath(for_b);

    Path for_b2;
    for_b2.addEdge(1, 1);
    for_b2.addEdge(2, 3);
    b.addPath(for_b2);

    a.combinePath(b);
    cout << "////////////////////////////////////////////" << endl;
    cout << a.path.size() << endl;
    for(auto i : a.path) {
        for(auto j : i) {
            cout << j.vex << ' ';
        }
        cout << endl;
    }


    return 0;
}
