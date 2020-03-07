#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

int main() {
    vector<int> *vecArray = new vector<int>[5];
    for(int i = 0; i < 5; i++) {
        vecArray[i].push_back(i);
    }
    for(int i = 0; i < 5; i++) {
        cout << vecArray[i].front() << endl;
    }
}
