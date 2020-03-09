#include <iostream>

using namespace std;

class R {
    public:
        void operator() (const int a) {
            cout << a << endl;
        }
};

int main() {
    R r;
    r(2);
    return 0;
}
