#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>

#include "./DijkstraForDis.h"
#include "./Path.h"

using namespace std;

//TODO
//加入记录路径的功能

/*
int arc[6][6] = {
    0, INT_MAX, 1, 1, 1, INT_MAX,
    INT_MAX, 0, 1, INT_MAX, 1, 1,
    1, 1, 0, 1, 1, 1,
    1, INT_MAX, 1, 0, 1, INT_MAX,
    1, 1, 1, 1, 0, 1,
    INT_MAX, 1, 1, INT_MAX, 1, 0
};
*/
void Dijkstra(Dis **arc, int begin, int size);

void Dijkstra(Dis **arc, int size) {
    for(int i = 0; i < size; i++) {
        Dijkstra(arc, i, size);
    }
}

void Dijkstra(Dis **arc, int begin, int size) {
    int count = 0;
    //bool visited[size];
    bool *visited = new bool[size];
    memset(visited, 0, size*sizeof(bool));

    //wait, wait, 这个路径是不是可以用矩阵乘法来做？
    //回忆一下离散数学的内容
    //这个for应该是每个Matrix第一次初始化的时候调用的，后期combine之后再进行Dijkstra肯定不能像这样初始化了
    //所以是不是可以增加一个判断语句，即进入Dijkstra的条件，增加一个参数
    for(int i = 0; i < size; i++) {
        (arc[begin][i].path)->addEdge(begin, route_num);
        (arc[begin][i].path)->addEdge(i, route_num);
    }

    while(count < size) {
        //cout << "count is " << count << endl;
        int min_i = 0;
        int min = INT_MAX;
        for(int i = 0; i < size; i++) {
            if(!visited[i] && arc[begin][i].value < min) {
                min = arc[begin][i].value;
                min_i = i;
            }
        }
        visited[min_i] = true;
        /*
        cout << "min = " << min << " min_i = " << min_i << endl;
        */
        ++count;
        for(int i = 0; i < size; i++) {
            if(!visited[i] && arc[begin][min_i].value != INT_MAX && arc[min_i][i].value != INT_MAX)
                if( arc[begin][i].value > arc[begin][min_i].value + arc[min_i][i].value ) {
                    arc[begin][i].value = arc[begin][min_i].value + arc[min_i][i].value;    
                    // 更改路径
                    *(arc[begin][i].path) = *(arc[begin][min_i].path) + *(arc[min_i][i].path);
                } 
                //如果相等，那么就增加一条路径
                else if( arc[begin][i].value > arc[begin][min_i].value + arc[min_i][i].value ) {
                    arc[begin][i].addPath( *(arc[begin][min_i].path) + *(arc[min_i][i].path) );
                }
                /*
                printf("update arc[%d][%d] = arc[%d][%d] + arc[%d][%d] \n", begin, i, begin, min_i, min_i, i); 
                */
            }
        }
    }
    //update the colum
    for(int i = 0; i < size; i++) {
        arc[i][begin] = arc[begin][i];
    }
    delete[] visited; 
}

/*
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
*/
