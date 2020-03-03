#include <iostream>
#include "newPath.h"
#include <vector>

const vector<Path> operator * (const vector<Path> &lhs, const vector<Path> &rhs) {
    vector<Path> res;
    for(int i = 0; i < lhs.size(); i++) {
        for(int j = 0; j < rhs.size(); j++) {
            res.push_back(lhs[i] + rhs[j]);
        }
    }
    return res;
}

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

    Dis c;
    c.assignPath(a.path * b.path);
    cout << "////////////////////////////////////////////" << endl;
    cout << c.path.size();
    for(auto i : c.path) {
        for(auto j : i) {
            cout << j.vex << ' ';
        }
        cout << endl;
    }


    vector<Path> res = a.path * b.path;
    cout << "////////////////////////////////////////////" << endl;
    cout << res.size() << endl;
    for(auto i : res) {
        for(auto j : i) {
            cout << j.vex << ' ';
        }
        cout << endl;
    }


    return 0;
}
