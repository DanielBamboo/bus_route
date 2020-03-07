#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include <unordered_set>

#include "Route_man.h"



// std::vector::iterator it = vec.begin() + 10
// vec.erase(it)

int main() {
    Route oneRoute;
    oneRoute.addStop(1);
    oneRoute.addStop(2);
    oneRoute.addStop(3);
    oneRoute.addStop(4);
    oneRoute.addStop(5);
    oneRoute.delStop(2);
    for(auto i : oneRoute.stops) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    oneRoute.insertStop(2, 2);
    for(auto i : oneRoute.stops) {
        std::cout << i << ' ';
    }
    

    return 0;
    Route_man man;
    man.addRoute(2);
    std::cout << man.debug_size() << std::endl;
    for(int i = 0; i < 5; i++)
        man[2].stops.push_back(i);

    std::cout << man.debug_size() << std::endl;

    man.addRoute(5);
    for(int i = 5; i < 10; i++)
        man[5].stops.push_back(i);

    man.addRoute(3);
    for(int i = 10; i < 15; i++)
        man[3].stops.push_back(i);

    man.addRoute(1);
    for(int i = 10; i < 15; i++)
        man[1].stops.push_back(i);

    std::cout << "add done!" << std::endl;
    std::cout << man.debug_size() << std::endl;

    man.del(3);
    man.del(2);
    man.del(1);

    std::cout << "Okay" << std::endl;
    for(auto i : man[5].stops) {
        std::cout << i;
    }
    return 0;
}
