#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>

using namespace std;
const int size = 6;
int arc[6][6] = {
    0, INT_MAX, 1, 1, 1, INT_MAX,
    INT_MAX, 0, 1, INT_MAX, 1, 1,
    1, 1, 0, 1, 1, 1,
    1, INT_MAX, 1, 0, 1, INT_MAX,
    1, 1, 1, 1, 0, 1,
    INT_MAX, 1, 1, INT_MAX, 1, 0
};

void Dijkstra(int begin) {
    int count = 0;
    bool visited[size];
    memset(visited, 0, size*sizeof(bool));
    while(count < size) {
        cout << "count is " << count << endl;
        int min_i = 0;
        int min = INT_MAX;
        for(int i = 0; i < size; i++) {
            if(!visited[i] && arc[begin][i] < min) {
                min = arc[begin][i];
                min_i = i;
            }
        }
        visited[min_i] = true;
        cout << "min = " << min << " min_i = " << min_i << endl;
        ++count;
        for(int i = 0; i < size; i++) {
            if(!visited[i] && arc[min_i][i] != INT_MAX &&
                arc[begin][i] > arc[begin][min_i] + arc[min_i][i]) {
                arc[begin][i] = arc[begin][min_i] + arc[min_i][i];    
                printf("update arc[%d][%d] = arc[%d][%d] + arc[%d][%d] \n", begin, i, begin, min_i, min_i, i); 
            }
        }
    }
    //update the colum
    for(int i = 0; i < size; i++) {
        arc[i][begin] = arc[begin][i];
    }
    
}

int main() {
    cout << (arc[5][0] == INT_MAX) << endl;
    cout << "begin" << endl;
    for(int i = 0; i < size; i++) {
        Dijkstra(i);
        for(int i = 0; i<size; i++) {
            for(int j = 0; j < size; j++) {
                if(arc[i][j] == INT_MAX) {
                    cout << "W ";
                } else {
                    cout << arc[i][j] << ' ';
                }
            }
            cout << endl;
        }
        cout << "/////////////////////////" << endl;
    }
    return 0;
}
