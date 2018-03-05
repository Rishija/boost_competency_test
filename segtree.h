#ifndef segtree_h
#define segtree_h

#include <iostream>
#include <math.h>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;

template <class T>
class Segment_tree {
    
    vector<T>tree;
    function<T(T,T)>objFn;
    T dontCare;
    T range_query(size_t start, size_t end, size_t treeStart, size_t treeEnd, size_t pos);
    void update(size_t start, size_t end, size_t pos, size_t index, T value);
    
public:
    
    Segment_tree(vector<T> arr, T dc, function<T(T, T)> fn);
    size_t size() { return tree.size(); }
    T range_query(size_t start, size_t end);
    void update(size_t index, T value);
    void print_tree(size_t root = 0, int space = 0);
    T &operator[](size_t i) { return tree[i]; }
};

#endif /* segtree_H */
