#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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

    set<int> s3;

    set_union(begin(s1), end(s1), begin(s2), end(s2), inserter(s2, begin(s2)));

    for(auto i : s2) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}
