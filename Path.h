// 深复制
// TODO
// 可以造一个映射，因为矩阵有差不多一半的空间被浪费了
// 这个映射可以是一个类
//
// 关于为什么要用数组我想说没想到什么好的数据结构可以方便地复制和删除并且占用空间小
// 换用vector了
// addEdge用可变参数?
#ifndef __PATH_H__
#define __PATH_H__

#include <vector>
using std::vector;

struct Edge {
    int route_num;
    int vex;
    Edge(int vex, int route_num) {
        this->vex = vex;
        this->route_num = route_num;
    }
};


class Path {
public:
    Path(const Path & rhs) {
        edge.assign(edge.begin(), edge.end());
    }
    Path() {
        next = nullptr;
    }
    ~Path() {
        
    }

    //如果有多条路径怎么办？
    //也就是在加法的时候，前面是两条路径，后面是2条路径，那么应该是2*2组合成4条才对
    Path & operator = (const Path & rhs) {
        //删除其他的path
        Path *i = this->next;
        Path *tmp = nullptr;
        while(i) {
            tmp = i->next;
            delete i;
            i = tmp;
        }
        
        next = nullptr;
        edge.assign(edge.begin(), edge.end());
    }
    // TODO
    // 让这个类可以被迭代器遍历
    //
    // 到底是哪个加法要做文章？
    
    Path operator +(const Path & rhs) {
        Path tmp(*this);
        copy(rhs.edge.begin(), rhs.edge.end(), back_inserter(tmp.edge));
        return tmp;
    }

    void addEdge(int vex, int route_num) {
        edge.push_back(Edge(vex, route_num));
    }
    
    Path *next;
private:
    vector<Edge> edge;
    //copy(v1.begin(), v1.end(), back_inserter(v2));
};


class Dis {
public:
    //析构的时候依次调用path的析构函数(delete)就可以了
    bool visited;
    int value;
    Path *path;

    // methods
    void addPath(const Path & rhs) {
        Path *new_path = new Path(rhs);
        //用头接法比较节省事件
        new_path->next = path;
        path = new_path;
    }

    Dis() {
        path = new Path();
        path->next = nullptr;
        visited = false;
        // -1 <--> unassignment
        value = -1;
    }

    Dis(const Dis & rhs) {
        path = new Path(*(rhs.path)); 
    }

    Dis & operator = (const Dis & rhs) {
        Path *tmp = path;
        while(path) {
            tmp = path->next;
            delete path;
            path = tmp;
        }
        path = new Path(*(rhs.path));
    }

    ~Dis() {
        Path *tmp = path;
        while(path) {
            tmp = path->next;
            delete path;
            path = tmp;
        }
    }
};
#endif

