#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <climits>
#include <unordered_map>
#include <cstdio>
#include <set>
#include <vector>

//TODO
//stations是不是可以删除

#include "./DijkstraForDis.h"
//#include "./Path.h"
//#include "newPath.h"
#include "setPath.h"
#include "./note/Route_man.h"
#include "./file/Read_file_refactor.h"

using namespace std;

/*
struct Route {
    int num;
    vector<int> stations;
};
*/


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


void print_matrix(Dis **a, int size);
void print_num_matrix(Dis **a, int size);
void print_path_num_matrix(Dis **a, int size);


map<int, string> num_to_name;
map<string, int> name_to_num;

//03-07 新建了两个全局变量，为了实现./file/TODO里的需求，即路径与矩阵的映射
map<int, int> route_to_which_matrix;
map<int, int> matrix_target_route;

//取小运算
//取可以直达的两种路径里代价比较小的那一个
//并且combine过后直接使存在路径的情况value = 1，也就是可以直达
//在之后的运算里也用这个新的value作代价了
Dis** combineAs(Dis ***A, int route_num, int size) {
    Dis **res = new Dis*[size];
    for(int i = 0; i < size; i++) {
        res[i] = new Dis[size];
    }

    for(int j = 0; j < size; j++)
        for(int k = 0; k < size; k++)
            res[j][k].value = INT_MAX;

    for(int j = 0; j < size; j++) {
        for(int k = 0; k < size; k++) {
            for(int i = 0; i < route_num; i++) {
                res[j][k] = A[i][j][k].value < res[j][k].value ? A[i][j][k] : res[j][k];
            }
            if(res[j][k].value != INT_MAX && res[j][k].value != 0) {
                res[j][k].value = 1; 
            }
        }
    }
    return res;
}
 

int main() {
    string station_name; 

    const char *filename = "/home/henryw/college/Data_Structure/bus_route/route.txt";
    cout << "目标文件是" << filename << endl;
    ifstream fin(filename, ios_base::in);
    
    int cnt = 0; // 为了给站点名放置下标而设置的标识，每次加一

    int num; // 站点数量
    fin >> num; //输入站点数量
    
    for(int i = 0; i < num; i++) {
        fin >> station_name;
        num_to_name[cnt++] = station_name;
    }

    // 从num_to_name构建name_to_num
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
    fin >> route_num;

    //Route *routes = new Route[route_num]; // 储存所有线路
    //replaced with Route_man
    
    Route_man<Route> route_man;

    //
    set<int> stations; // 保存所有站点
    cout << "route_num = " << route_num << endl;

    //如果这里要被分开成为一个函数，那么返回Dis *** 以及 传入fin
    //定义数组
    //int ***A = new int**[route_num];
    Dis ***A = new Dis**[route_num];

    //读取数据，作一些初始化工作，对角线是0，没有连通是无穷大
    ////////////////////////////////////////////////////////////////////

    for(int i = 0; i < route_num; i++) {

        //A[i] = new int*[num];
        A[i] = new Dis*[num];

        for(int j = 0; j < num; j++) {
            //A[i][j] = new int[num];
            A[i][j] = new Dis[num];
            //memset(A[i][j], 0, num * sizeof(int));
            for(int k = 0; k < num; k++) {
                A[i][j][k].value = INT_MAX;
            }
        }

        //初始化对角线
        for(int k = 0; k < num; k++)
            A[i][k][k].value = 0;

        int NoDot; // No.
        fin >> NoDot;
        //03-07 原来之前我已经发现了这一点，也就是我今天在./file/TODO里提到的那个需求，为read.cpp加入一个读取编号的功能
        route_to_which_matrix[NoDot] = i;
        matrix_target_route[i] = NoDot;

        route_man.addRoute(NoDot);
        cout << route_man.debug_size() << "debug size" << endl;

        int route_len;
        fin >> route_len;
        string front_name, behind_name; //要实现更新节点，需要记录下前一个和后一个，然后用map获取需要更新的坐标
        //更新邻接矩阵
        //由于我们只有一个单向的路线，所以在用它来更新邻接矩阵的时候需要记下前一个，不然指针跳到下一个可就没办法知道前一个是什么了，从而没办法更新A[][]
        fin >> front_name;

        //routes[i].stations.push_back(name_to_num[front_name]);
        //replaced with route_man
        route_man[NoDot].addStop(name_to_num[front_name]);
        

        stations.insert(name_to_num[front_name]);

        for(int k = 1; k < route_len; k++) {
            fin >> behind_name; 
            
            //routes[i].stations.push_back(name_to_num[behind_name]);
            //replaced with route_man
            route_man[NoDot].addStop(name_to_num[behind_name]);

            stations.insert(name_to_num[behind_name]);
            
            A[i][name_to_num[front_name]][name_to_num[behind_name]].value = A[i][name_to_num[behind_name]][name_to_num[front_name]].value = 1;
            front_name = behind_name;
        }
    }

    fin.close();

    for(auto i : route_to_which_matrix) {
        cout << "route " << i.first << endl;
        for(auto j : route_man[i.first].stops) {
            cout << num_to_name[j] << endl;
        }
        cout << endl;
    }

    string target;
    while(true) {
        do {
            cout << "请输入你要查询的公交站(q退出)：";
            cin >> target;
            cout << "输入了(" << target << ")" << endl;
        } while(target != "q" && name_to_num.count(target) == 0);

        if(target == "q") break;

        cout << "查询 " << name_to_num[target] << "号站点" << endl;

        for(int i = 0; i < route_num; i++) {
            for(int j = 0; j < num; j++) {
                if(A[i][name_to_num[target]][j].value == 1) {
                    cout << matrix_target_route[i] << " 路" << endl;
                    break;
                }
            }
        }
    }

    int cmd;
    cout << "进入编辑模式" << endl;
    cout << "你想做什么？删除某一条路径(0)、更改某一条路径(1)、增加一条新的路径(2):";
    cin >> cmd;
    switch(cmd) {
        case 0:
        {
            int delRoute;
            cout << "输入要删除的路径的编号: ";
            // 这边可以做成选择界面
            // 每次删除之后都需要重新构建矩阵
            cin >> delRoute;

            route_man.del(delRoute);
            cout << "删除完成" << endl;
        }

            break;
        case 1:
        {
            int target_route;
            cout << "输入要更改的路径的编号: ";
            cin >> target_route;
            
            while(!route_man.check_index_legal(target_route)) {
                cout << "输入有误，再次输入: ";
                cin >> target_route;
            }

            //增加一条站点还是删除一个站点
            int cnt2 = 0;
            for(auto i : route_man[target_route].stops) {
                cout << num_to_name[i] << "(" << ++cnt2 << ") ";
            }
            cout << endl;

            int cmd2;
            cout << "删除某个站点(0), 增加一个站点(1)，输入: ";
            cin >> cmd2;
            int target_index;

            if(cmd2 == 0) {
                cout << "输入要删除的站点的下标: ";
                cin >> target_index;
                route_man[target_route].delStop(target_index);
            } else if(cmd2 == 1) {
                cout << "输入要增加的站点的名字和要插入的位置: ";
                string newStop;
                cin >> newStop >> target_index;
                num_to_name[cnt++] = newStop;
                name_to_num[newStop] = cnt-1;
                cout << "新的站点编号为" << cnt-1 << endl;
                route_man[target_route].insertStop(cnt-1, target_index);
            }

            cout << "修改之后: ";
            bool first = true;
            for(auto i : route_man[target_route].stops) {
                if(!first) {
                    cout << " -- ";
                } else {
                    first = false;
                }
                cout << num_to_name[i];
            }
            cout << endl;
        }
            
            break;
        case 2:
        {
            int insertRoute;
            cout << "输入要新增的路径的编号: ";
            // 每次删除之后都需要重新构建矩阵
            cin >> insertRoute;
            
            if(route_man.check_index_legal(insertRoute)) {
                cout << "路径已经存在，请重新输入: ";
                cin >> insertRoute;
            }

            route_man.addRoute(insertRoute);
            
            vector<int> newStops;

            cout << "请输入" << insertRoute << "路公交的站点数量: ";
            int newStopsNum;
            cin >> newStopsNum;

            cout << "请依次输入站点名字";
            string newStop;
            while(newStopsNum--) {
                cin >> newStop;
                num_to_name[cnt++] = newStop;
                name_to_num[newStop] = cnt-1;
                newStops.push_back(cnt-1);
                cout << "新增站点[" << newStop << "] 编号为" << cnt-1 << endl;
            }

            route_man[insertRoute].stops = newStops;

            cout << "创建完成:";
            bool first = true;
            for(auto i : route_man[insertRoute].stops) {
                if(!first) {
                    cout << " -- ";
                } else {
                    first = false;
                }
                cout << num_to_name[i];
            }
            cout << endl;


        }
            break;

        default:
            break;
    }

    cout << "此时有" << route_man.debug_size() << "路公交" << endl;

    
    ofstream fout;
    fout.open(filename);

    // 将修改写入文件
    auto man_it = route_man.begin();
    auto man_it_end = route_man.end();

    bool firstIt = true;

    for(man_it; man_it != man_it_end; man_it++) {
        if(!firstIt) {
            fout << endl;
        } else {
            firstIt = false;
        }
        fout << (*man_it).num << endl;
        for(auto i : (*man_it).stops) {
            fout << num_to_name[i] << endl;
        }
    }

    cout << "开始写入文件" << endl;
    

    Read_file_refactor file_refactor;
    file_refactor(filename);
    
    

    
    return 0;
    ////////////////////////////////////////////////////////////////////

    /*
    int size = num_to_name.size();
    int **A1 = new int*[size];
    for(int i = 0; i < size; i++) {
        A1[i] = new int[size];
        memset(A1[i], 0, size * sizeof(int));
    }
    */

    //Dijkstra算法好像也要修改了
    //TODO
    //重写一个Dijkstra for Dis
    //
    //调用dijkstra算法，算出来每个矩阵的直达情况，然后给出距离
    for(int i = 0; i < route_num; i++) {
        Dijkstra(A[i], num, i);
    }

    for(int i = 0; i < route_num; i++) {
        print_num_matrix(A[i], num);
        printf("///////////////////////////////\n");
    }     

    for(int i = 0; i < route_num; i++) {
    //for(int i = 0; i < 1; i++) {
        cout << "route:" << i+1 << endl;
        print_matrix(A[i], num);
    }

    //输出路线信息，检查是否正确
    unordered_map<pair<int, int>, int, pair_hash> reach;
    for(int i = 0; i < route_num; i++) {
        for(int j = 0; j < num; j++) {
            for(int k = 0; k < num; k++) {
                if(A[i][j][k].value != 0 && A[i][j][k].value != INT_MAX) {
                    if(reach.count(pair<int,int>(j,k)) == 0 && reach.count(pair<int,int>(k,j)) == 0)
                            reach[pair<int, int>(j,k)] = A[i][j][k].value;
                }
            }
        }
        for(auto it = reach.begin(); it != reach.end(); it++) {
            cout << num_to_name[(it->first).first] << "---" << num_to_name[(it->first).second] << " with a distance " << it->second << endl;
        }
        
        //TODO
        //这边也得改
        print_matrix(A[i], num);
        reach.clear();
    }
    //改用新的输出路线的方式
    
    //参考论文里面，对所有A[i]，算出来一个min矩阵，也就是min[i][j] = min(A[k][i][j], k = 0, 1, 2, 3...
    //num是公交站的数量，在这里size和num说的是同一个东西
    Dis **B =  
        combineAs(A, route_num, num);

    Dijkstra(B, num, -1);
    cout << "after combination and Dijstra algorithm: \n";
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++)
            if(B[i][j].value != INT_MAX)
                cout << B[i][j].value << ' ';
            else
                cout << "∞" << ' ';
        cout << endl;
    }

    Dis **D = B;
    
    print_matrix(D, num);
    cout << "print path num matrix" << endl;
    print_path_num_matrix(D, num);
    
    


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
void print_matrix(Dis **B, int num) {
    
    //这个矩阵是35 × 35，下标是[0-34][0-34]
    //直接输出出来
    
    for(int i = 0; i < num; i++) {
        //for(int j = 0; j < num; j++) {
        //更改为上半片区
        for(int j = i; j < num; j++) {
            if(B[i][j].value == INT_MAX || B[i][j].value == 0) continue;
            cout << "position [" << num_to_name[i] << "][" << num_to_name[j] << "] :" << endl;
            cout << "有" << B[i][j].path.size() << "条路径" << endl;
            for(auto onePath : B[i][j].path) {
                for(auto edge : onePath) {
                    cout << num_to_name[edge.vex] << "(" << edge.route_num+1 << "号线) --> ";
                }
                cout << endl << "|" << endl;
            }
            cout << "\n\n";
        }
    }

}

void print_num_matrix(Dis **a, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(a[i][j].value != INT_MAX)
                cout << a[i][j].value << ' ';
            else
                cout << "∞ ";
        }
        cout << endl;
    }
}

void print_path_num_matrix(Dis **a, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%2ld ", a[i][j].path.size());            
        }
        printf("\n");
    }
}
