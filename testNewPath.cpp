#include <iostream>
#include "setPath.h"
#include <vector>
#include <set>
#include <algorithm>

/*
const vector<Path> operator * (const vector<Path> &lhs, const vector<Path> &rhs) {
    vector<Path> res;
    for(int i = 0; i < lhs.size(); i++) {
        for(int j = 0; j < rhs.size(); j++) {
            res.push_back(lhs[i] + rhs[j]);
        }
    }
    return res;
}
*/

const set<Path> operator * (const set<Path> &lhs, const set<Path> &rhs) {
    set<Path> res;
    for(auto i : lhs) {
        for(auto j : rhs) {
            res.insert(i+j);
        }
    }
    return res;
}


using namespace std;

//把这个迁移到成员函数
/*
bool operator < (const Path &lhs, const Path &rhs) {
    //return lhs.len() < rhs.len();
    if(lhs.len() == rhs.len()) {
        for(int i = 0; i < lhs.len(); i++) {
            if(lhs.edge[i].vex != rhs.edge[i].vex) {
                return lhs.edge[i].vex < rhs.edge[i].vex;
            } else if(lhs.edge[i].route_num != rhs.edge[i].route_num) {
                return lhs.edge[i].route_num < rhs.edge[i].route_num;
            }
        } 
    } else {
        return lhs.len() < rhs.len();
    }
}
*/

int main() {

    /*
    set<int> s1;
    set<int> s2;

    s1.insert(1);
    s1.insert(5);
    s1.insert(41);
    s1.insert(9);

    s2.insert(2);
    s2.insert(4);
    s2.insert(1);
    s2.insert(9);
    s2.insert(19);

    set_union(begin(s1), end(s1), begin(s2), end(s2), inserter(s1, begin(s1)));

    for(auto i : s1) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
    //需要提供一个重载
    */
    /*
    set<Path> path;
    
    Path path1;
    path1.addEdge(4, 1);
    path1.addEdge(3, 1);
    path1.addEdge(2, 1);
    path1.addEdge(1, 1);
    path1.addEdge(0, 1);

    Path path2;
    path2.addEdge(4, 1);
    path2.addEdge(3, 1);
    path2.addEdge(2, 1);
    path2.addEdge(1, 1);
    path2.addEdge(0, 2);

    path.insert(path1);
    path.insert(path2);
    
    cout << "size = " << path.size() << endl;

    */

    


    /*
    return 0;
    */

    cout << "///////////----/////////////\n";
    Dis a;
    Dis b;
    Path for_a;
    for_a.addEdge(2, 1);
    for_a.addEdge(3, 1);
    a.addPath(for_a);
    Path for_a2;
    for_a2.addEdge(2, 1);
    for_a2.addEdge(3, 1);
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
    cout << c.path.size() << endl;
    for(auto i : c.path) {
        for(auto j : i) {
            cout << j.vex << ' ';
        }
        cout << endl;
    }


    set<Path> res = a.path * b.path;
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
