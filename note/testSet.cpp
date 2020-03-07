#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> a;
    a.insert(99);
    a.insert(100);
    a.erase(99);

    for(auto i : a) {
        cout << i << endl;
    }

    return 0;
}
