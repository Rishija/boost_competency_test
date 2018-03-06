#ifndef segtree_h
#define segtree_h

#include <iostream>
#include <math.h>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;

// Expression template
template <class E>
class Expression {
    
public:
    
    auto operator[](size_t i)   const { return static_cast<E const&>(*this)[i]; }
    operator E& ()                    { return static_cast<E&>(*this); }
    operator const E& ()        const { return static_cast<const E&>(*this); }
    size_t size()               const { return static_cast<E const&>(*this).size(); }
};


template <class T>
class Segment_tree : public Expression<Segment_tree<T>> {
    
    vector<T>tree;          // Tree
    function<T(T,T)>objFn;  // Function for queries
    T dontCare;             // default value
    T range_query(size_t start, size_t end, size_t treeStart, size_t treeEnd, size_t pos);
    void update(size_t start, size_t end, size_t pos, size_t index, T value);
    
public:
    
    Segment_tree(vector<T> arr, T dc, function<T(T, T)> fn);
    
    // Initialise tree with expression 'expr'
    template <typename E>
    Segment_tree<T>(Expression<E> const& expr) : tree(expr.size()) {
        for (size_t i = 0; i != expr.size(); ++i) {
            tree[i] = expr[i];
        }
    }
    
    size_t size()       const { return tree.size(); }
    T get_dontCare()    const { return dontCare; }
    
    T range_query(size_t start, size_t end);        // wrapper for range_query()
    void update(size_t index, T value);             // wrapper for update()
    
    void print_tree(size_t root = 0, int space = 0);
    
    T &operator[](size_t i) { return tree[i]; }
    T operator[](size_t i) const { return tree[i]; }
};

// Expression template for + operator
template <class E1, class E2>
class treeSum : public Expression<treeSum<E1, E2> > {
    E1 const& expr1;
    E2 const& expr2;
    
public:
    treeSum(E1 const& u, E2 const& v) : expr1(u), expr2(v) {
        assert(u.size() == v.size());
    }
    
    auto operator[](size_t i) const { return expr1[i] + expr2[i]; }
    size_t size()               const { return expr2.size(); }
};

// Expression template for - operator
template <class E1, class E2>
class treeDiff : public Expression<treeDiff<E1, E2> > {
    E1 const& expr1;
    E2 const& expr2;
    
public:
    treeDiff(E1 const& u, E2 const& v) : expr1(u), expr2(v) {
        assert(u.size() == v.size());
    }
    
    auto operator[](size_t i) const { return expr1[i] - expr2[i]; }
    size_t size()               const { return expr2.size(); }
};

// Expression template for * operator
template <typename E1, typename E2>
class treeMul : public Expression<treeMul<E1, E2> > {
    E1 const& expr1;
    E2 const& expr2;
    
public:
    treeMul(E1 const& u, E2 const& v) : expr1(u), expr2(v) {
        assert(u.size() == v.size());
    }
    
    auto operator[](size_t i) const { return expr1[i] * expr2[i]; }
    size_t size()               const { return expr2.size(); }
};

#endif /* segtree_H */
