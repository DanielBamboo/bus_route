#include <iostream>
#include <map>
using namespace std;

int main() {
    pair<int, int> a(1,2);
    cout << a.first << a.second;
    cout << endl;
    map<int, int> ab;
    ab[1] = 2;
    ab[2] = 3;

    cout << ab.count(1) << endl;
    cout << ab.count(3) << endl;
    return 0;
}
