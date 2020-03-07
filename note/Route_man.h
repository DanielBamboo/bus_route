#ifndef __ROUTE_MAN_H__
#define __ROUTE_MAN_H__

#include <vector>
#include <unordered_set>
#include <iostream>

struct Route {
    std::vector<int> stops;
    int num;
    struct Route *next;
    struct Route *pre;

    Route() :next(nullptr), pre(nullptr) {}
    Route(int num) :num(num) {
        stops.reserve(10);
    }
    void addStop(int index) {
        stops.push_back(index);
    }
    
    //void addStop(...)
    // 删除第index位置的元素，从1数起
    void delStop(int index) {
        std::vector<int>::iterator it = stops.begin();
        stops.erase(it + index - 1);
    }

    //增加编号为num的站点在stops数组的index之前，这个number由map分配，map[cnt++] = string
    void insertStop(int number, int index) {
        stops.insert(stops.begin() + index, number);
    } 
};

// set::erase() 删除特定元素
// route management
class Route_man {
private:
    int num;
    Route *head;
    Route *tail;
    std::unordered_set<int> route_indexes;
public:
    Route_man(): num(0), head(nullptr), tail(nullptr) {

    }

    // 输入线路，返回引用
    Route &operator [] (int route_index) {
        if(!check_index_legal(route_index)) {
            std::cout << "没有这条路" << std::endl;
            exit(0);
        }
        Route *pi = head;
        while(pi) {
            if(pi->num == route_index) {
                break;
            }
            pi = pi->next;
        }
        return *pi;
    }

    size_t size() {
        return num;
    }

    bool check_index_legal(int index) {
        if(route_indexes.count(index) == 0)
            return false;
        return true;
    }

    // 删除某条公交线路
    void del(int route_index) {
        if(!check_index_legal(route_index)) {
            std::cout << "你在尝试删除一条不存在的道路";
            exit(0);
        }
        Route *pi = head;
        while(pi) {
            if(pi->num == route_index) {
                std::cout << "we got that" << std::endl;
                break;
            }
            pi = pi->next;
        }
        if(pi == head) {
            head = head->next;
            head->pre = nullptr;

            delete pi;
        } else if(pi == tail) {
            tail->pre->next = nullptr;
            tail = pi->pre;
            delete pi;
        }else {
            pi->pre->next = pi->next;
            pi->next->pre = pi->pre;
            
            delete pi;
        }
        num--;
        route_indexes.erase(route_index);
    }

    void addRoute(int route_index) {
        route_indexes.insert(route_index);
        Route *newR = new Route(route_index);
        if(tail == nullptr) {
            std::cout << "tail == nullptr" << std::endl;
            if(!newR) exit(0);
            head = newR;
            tail = newR;
        } else {
            tail->next = newR;
            tail->next->pre = tail;
            tail = tail->next;
        }
        tail->next = nullptr;
        num++;
    }

    int debug_size() {
        Route *pi = head;
        int cnt = 0;
        while(pi) {
            cnt++;
            pi = pi->next;
        }
        return cnt;
    }
};

// std::vector::iterator it = vec.begin() + 10
// vec.erase(it)


#endif
