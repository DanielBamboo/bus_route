#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <climits>
#include <unordered_map>

#include "./Dijkstra.h"

using namespace std;


struct pair_hash
{
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

void print_matrix(int **a, int size);
map<int, string> num_to_name;
map<string, int> name_to_num;

//取小运算
int** combineAs(int ***A, int route_num, int size) {
    int **res = new int*[size];
    for(int i = 0; i < size; i++) {
        res[i] = new int[size];
    }

    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            res[j][k] = INT_MAX;

    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++) {
            for(int i = 0; i < route_num; i++) {
                res[j][k] = std::min(A[i][j][k], res[j][k]);
            }
            if(res[j][k] != INT_MAX && res[j][k] != 0) {
                res[j][k] = 1; 
            }
        }
    return res;
}
 

int main() {
    string station_name; 
    int cnt = 0;
    int num;
    cin >> num;
    cout << "num =" << num << endl;
    for(int i = 0; i < num; i++) {
        std::cin >> station_name;
        num_to_name[cnt++] = station_name;
    }

    map<int, string>::iterator end = num_to_name.end();
    for(auto it = num_to_name.begin(); it != end; it++) {
        cout << it->first << " " << it->second << endl;
        name_to_num[it->second] = it->first;
    }

    map<string, int>::iterator end2 = name_to_num.end();
    for(auto it = name_to_num.begin(); it != end2; it++) {
        cout << it->first << ' ' << it->second << endl;
    }

    
    int route_num;
    cin >> route_num;
    cout << "route_num = " << route_num << endl;

    int ***A = new int**[route_num];
    for(int i = 0; i < route_num; i++) {
        A[i] = new int*[num];
        for(int j = 0; j < num; j++) {
            A[i][j] = new int[num];
            //memset(A[i][j], 0, num * sizeof(int));
            for(int k = 0; k < num; k++) {
                A[i][j][k] = INT_MAX;
            }
        }

        //初始化对角线
        for(int k = 0; k < num; k++)
            A[i][k][k] = 0;

        int NoDot; // No.
        cin >> NoDot;
        int route_len;
        cin >> route_len;
        string front_name, behind_name; //要实现更新节点，需要记录下前一个和后一个，然后用map获取需要更新的坐标
        cin >> front_name;
        for(int k = 1; k < route_len; k++) {
            cin >> behind_name; 
            A[i][name_to_num[front_name]][name_to_num[behind_name]] = A[i][name_to_num[behind_name]][name_to_num[front_name]] = 1;
            front_name = behind_name;
        }
    }

    /*
    int size = num_to_name.size();
    int **A1 = new int*[size];
    for(int i = 0; i < size; i++) {
        A1[i] = new int[size];
        memset(A1[i], 0, size * sizeof(int));
    }
    */



    //调用dijkstra算法
    for(int i = 0; i < route_num; i++) {
        Dijkstra(A[i], num);
    }

    //输出路线信息，检查是否正确
    unordered_map<pair<int, int>, int, pair_hash> reach;
    for(int i = 0; i < route_num; i++) {
        for(int j = 0; j < num; j++) {
            for(int k = 0; k < num; k++) {
                if(A[i][j][k] != 0 && A[i][j][k] != INT_MAX) {
                    if(reach.count(pair<int,int>(j,k)) == 0 && reach.count(pair<int,int>(k,j)) == 0)
                            reach[pair<int, int>(j,k)] = A[i][j][k];
                }
            }
        }
        for(auto it = reach.begin(); it != reach.end(); it++) {
            cout << num_to_name[(it->first).first] << "---" << num_to_name[(it->first).second] << " with a distance " << it->second << endl;
        }
        
        print_matrix(A[i], num);
        reach.clear();
    }
    
    //参考论文里面，对所有A[i]，算出来一个min矩阵，也就是min[i][j] = min(A[k][i][j], k = 0, 1, 2, 3...
    int **B =  
        combineAs(A, route_num, num);

    Dijkstra(B, num);

    cout << "after combination and Dijstra algorithm: \n";
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++)
            if(B[i][j] != INT_MAX)
                cout << B[i][j] << ' ';
            else
                cout << "∞" << ' ';
        cout << endl;
    }

    


    // destruct
    for(int k = 0; k < route_num; k++) {
        for(int i = 0; i < num; i++) {
            delete[] A[k][i];
        }
        delete[] A[k];
    }
    delete[] A;

    return 0;
}

//打印矩阵的信息
void print_matrix(int **a, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j <= size; j++) {
            /*
            if(a[i][j] != 0 && a[i][j] != INT_MAX) {
                cout << '[' << i << ']' << '[' << j << ']' << '\n';
                cout << num_to_name[i] << "--" << num_to_name[j] << endl;
            }
            */
        }
    }
    cout << endl << "///////////////////////////////////////////////////////////////" << endl;
}

