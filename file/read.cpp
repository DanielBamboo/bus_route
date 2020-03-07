#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// 给一个只有站点其余什么也没有的文件添加必要的信息

int main() {
    vector<string> content;
    queue<int> len_of_each_route;
    set<string> stations_set;
    vector<string> stations_vec;
    ifstream fin("./routeWithNoList.txt", ios_base::in);

    // 公交车路径存取
    queue<int> route_number;
    string line;
    int cnt = 0;
    int station_cnt = 0;
    

    getline(fin, line);
    string::size_type sz;
    route_number.push(std::stoi(line, &sz));

    //我们现在又要开始填坑了，现在的问题在于原文件多了一行路径名称
    while(getline(fin, line)) {
        content.push_back(line);
        if(line != "") {
            station_cnt++;
            int before = stations_set.size();
            stations_set.insert(line);
            int after = stations_set.size();
            if(after == before + 1) {
                stations_vec.push_back(line);
            }
        }
        if(line == "") {
            cnt++; 
            len_of_each_route.push(station_cnt);
            station_cnt = 0;
            getline(fin, line);
            route_number.push(std::stoi(line, &sz));
        }
    }
    len_of_each_route.push(station_cnt);
    cout << "with " << cnt+1 << " routes" << endl;
    fin.close();

    ofstream fout("./routeWithNoList.txt", ios_base::out | ios_base::trunc);
    // 输出全部站点，按添加的顺序来
    fout << stations_set.size() << endl;
    for(auto i : stations_vec) {
        fout << i << endl;
    }
    fout << endl; // 增加美观
    
    //打印有多少条公交线路
    fout << len_of_each_route.size() << endl;

    //开始打印每条线路
    //格式是线路编号->线路长度->线路列表
    bool first = true;
    for(auto i : content) {
        //这个if和else实现的功能是一样的，只不过我为了不在文件开头加一个空行所以加了这个
        if(first) {
            fout << route_number.front() << endl;
            route_number.pop();

            fout << len_of_each_route.front() << endl;
            len_of_each_route.pop();

            first = false;
        } else if ( i == "" ) {
            fout << i << endl;

            fout << route_number.front() << endl;
            route_number.pop();

            fout << len_of_each_route.front() << endl;
            len_of_each_route.pop();
            continue;
        }
        fout << i << endl;
    }
    fout.close();

    //cout << "station_num is " << stations.size();
    return 0;
}
