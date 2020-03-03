#include <iostream>

using namespace std;

class A {
public:
    A(int v = 0) : value(v) {}

    
    A &operator = (const A & rhs) {
        value = rhs.value;
    }
    

    A operator +(const A & rhs) {
        A a;
        cout << "operator+\n";
        a.value = value + rhs.value;
        cout << "key\n";
        return a;
    }
    int V() {
        return value;
    }
private:
    int value;
};

int main() {
    A a1(2);
    A a2(3);
    A a3(1);
    a3 = a1 + a2;
    cout << a3.V() << endl;
} 
    
