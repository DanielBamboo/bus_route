// TODO
// 可以造一个映射，因为矩阵有差不多一半的空间被浪费了
// 这个映射可以是一个类
//
// 关于为什么要用数组我想说没想到什么好的数据结构可以方便地复制和删除并且占用空间小
// 换用vector了
// addEdge用可变参数?
// 变为setPath
#ifndef __SET_PATH_H__
#define __SET_PATH_H__

#include <vector>
#include <set>
#include <iostream>
#include <climits>
#include <algorithm>
using std::set;
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
    // TODO
    // 这个加号得改，也就是删除的是lhs的末尾还是rhs的开头
    const Path operator +(const Path & rhs) const {
        Path tmp(*this);
        if(tmp.edge.back().vex == rhs.edge.front().vex) {
            if(tmp.edge.back().route_num == rhs.edge.front().route_num) {
                copy(rhs.edge.begin()+1, rhs.edge.end(), back_inserter(tmp.edge));
            } else {
                copy(rhs.edge.begin(), rhs.edge.end(), back_inserter(tmp.edge));
            }
        }
        return tmp;
    }

    bool operator < (const Path &rhs) const  {
        //return lhs.len() < rhs.len();
        if(this->len() == rhs.len()) {
            for(int i = 0; i < this->len(); i++) {
                if(this->edge[i].vex != rhs.edge[i].vex) {
                    return this->edge[i].vex < rhs.edge[i].vex;
                } else if(this->edge[i].route_num != rhs.edge[i].route_num){
                    return this->edge[i].route_num < rhs.edge[i].route_num;
                }
            }
        } else {
            return this->len() < rhs.len();
        }
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
    

private:
    vector<Edge> edge;
};

// 我觉得乘号比较合适
const set<Path> operator * (const set<Path> &lhs, const set<Path> &rhs);


class Dis {
public:
    int value;
    set<Path> path;
    bool initialized;

    // methods
    Dis() : initialized(false), value(initialized) {}

    void addPath(const Path &t) {
        path.insert(t);
    }

    void addPath(const set<Path> &t) {
        std::set_union(std::begin(path), std::end(path),
                       std::begin(t), std::end(t),
                       inserter(path, std::begin(path)));
    }


    void assignPath(const set<Path> &other) {
        path = other;
    }

    void assignReversedPaths(const Dis & other) {
        path.clear();
        for(auto i : other.path) {
            path.insert(i.reversePath());
        }
    }
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
