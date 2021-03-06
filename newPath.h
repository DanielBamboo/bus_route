// 深复制
// TODO
// 可以造一个映射，因为矩阵有差不多一半的空间被浪费了
// 这个映射可以是一个类
//
// 关于为什么要用数组我想说没想到什么好的数据结构可以方便地复制和删除并且占用空间小
// 换用vector了
// addEdge用可变参数?
#ifndef __NEW_PATH_H__
#define __NEW_PATH_H__

#include <vector>
#include <iostream>
#include <climits>
using std::cout;
using std::endl;
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

    /*
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
    // 让这个类可以被迭代器遍历 done
    //
    // 到底是哪个加法要做文章？
    //
    // 这个加号得改，也就是删除的是lhs的末尾还是rhs的开头
    
    */
    const Path operator +(const Path & rhs) const {
        Path tmp(*this);
        copy(rhs.edge.begin()+1, rhs.edge.end(), back_inserter(tmp.edge));
        return tmp;
    }

    void addEdge(int vex, int route_num) {
        edge.push_back(Edge(vex, route_num));
    }

    vector<Edge>::iterator begin() {
        return edge.begin();
    }
    
    vector<Edge>::iterator end() {
        return edge.end();
    }

    
    Path reversePath() {
        Path reverPath;
        vector<Edge>::reverse_iterator r_iter;
        for(r_iter = edge.rbegin(); r_iter != edge.rend(); r_iter++) {
            reverPath.edge.push_back(*r_iter);
        }
        return reverPath;
    }

    int len() const {
        return edge.size(); 
    }
    

    /*
    Path *next;
    */
//private:
    vector<Edge> edge;
    //copy(v1.begin(), v1.end(), back_inserter(v2));
};

// 我觉得乘号比较合适
const vector<Path> operator * (const vector<Path> &lhs, const vector<Path> &rhs);


class Dis {
public:
    //析构的时候依次调用path的析构函数(delete)就可以了
    //bool visited;
    int value;
    vector<Path> path;
    bool initialized;

    // methods
    
    Dis() : initialized(false) {
        value = INT_MAX; 
    }
    


    void addPath(const Path &t) {
        path.push_back(t);
    }

    void addPath(const vector<Path> &t) {
        
        //cout << "addPath" << endl;
        //copy(t.begin(), t.end(), back_inserter(this->path));
        path.insert(path.end(), t.begin(), t.end());
        //cout << "addPath done!" << endl;
    }

    // ! 这个好像有点问题，不应该这么写？
    void combinePath(const Dis &other) {
        this->path = this->path * other.path;
    }

    void assignPath(const vector<Path> &other) {
        //path.clear();
        path = other;
    }

    void assignReversedPaths(const Dis & other) {
        path.clear();
        for(auto i : other.path) {
            path.push_back(i.reversePath());
        }
    }

    

    /*
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
    */
};


/*
const vector<Path> operator * (const vector<Path> &lhs, const vector<Path> &rhs) {
    vector<Path> res;
    for(int i = 0; i < lhs.size(); i++) {
        for(int j = 0; j < rhs.size(); j++) {
            res.push_back(lhs[i] + rhs[j]); 
        }
    }
    return res;
}
*/
#endif
