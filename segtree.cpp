#include "segtree.h"

template<class T>
/**
 Constructor
 
 @param arr Input
 @param dc Default value
 @param fn Generic function to be applied to build segment tree
 */
Segment_tree<T>::Segment_tree(vector<T> arr, T dc, function<T(T, T)> fn) : dontCare(dc), tree( 2*pow(2, ceil(log2(arr.size()))) - 1 ), objFn(fn) {
    
    size_t size = tree.size(), i = size/2;
    
    // Fill leaf nodes with given values
    for(size_t j = 0; j != arr.size(); ++i, ++j)
        tree[i] = arr[j];
    
    // Fill rest of the leaves with default value
    while(i < size) {
        tree[i] = dontCare;
        ++i;
    }
    
    // Apply given function to get values of internal and root node
    i = 0;
    for(size_t j = size/2 - 1; i != size/2 ; --j, ++i)
        tree[j] = objFn(tree[2*j+1], tree[2*j+2]);
}


template<class T>
void Segment_tree<T>::print_tree(size_t root, int tabs) {
    if(root < tree.size()) {
        tabs += 3;
        print_tree(2*root + 2, tabs);
        
        cout << endl;
        for (int i = 3; i < tabs; i++)
            cout << "\t";
        cout << tree[root];
        
        print_tree(2*root + 1, tabs);
    }
}


template <class T>
/**
 Wrapper for range_query()
 */
T Segment_tree<T>::range_query(size_t start, size_t end)  {
    
    assert(start <= end && "Invalid query");
    return range_query(start, end, 0, tree.size()/2, 0);
}


template <class T>
/**
 Performs range query in given range
 
 @param start Starting index
 @param end Last index
 @param arrStart Start of segment tree
 @param arrEnd End of segment tree
 @param pos Current position
 @return Value of objective function in given range
 
 Approach: Recursion
 */
T Segment_tree<T>:: range_query(size_t start, size_t end, size_t arrStart, size_t arrEnd, size_t pos) {
    
    // current range completely lies between the given range
    if((arrStart >= start && arrEnd <= end))
        return tree[pos];
    
    // out of bounds
    if(start > arrEnd || end < arrStart)
        return dontCare;
    
    size_t mid = (arrStart + arrEnd)/2;
    
    // search in both the directions
    return objFn(range_query(start, end, arrStart, mid , 2*pos + 1), range_query(start, end, mid + 1, arrEnd, 2*pos + 2));
}


template <class T>
/**
 Wrapper for update()
 */
void Segment_tree<T>::update(size_t index, T value) {
    
    assert(index >=0 && index <= tree.size()/2 && "Invalid index");
    update(0, tree.size()/2, 0, index, value);
}


template<class T>
/**
 Updates the value of given index and propagate the changes till root
 
 @param start Start of segment tree
 @param end End of segment tree
 @param pos Current position
 @param index Index of input to be updated
 @param value New value
 
 Approach: Recursion
 */
void Segment_tree<T>::update(size_t start, size_t end, size_t pos, size_t index, T value) {
    
    if(start == end) {
        tree[tree.size()/2 + start] = value;
        return;
    }
    
    size_t mid = (start + end)/2;
    index <= mid ? update(start, mid, 2*pos + 1, index, value) : update(mid + 1, end, 2*pos + 2, index, value) ;
    
    tree[pos] = objFn(tree[2*pos + 1], tree[2*pos + 2]);
}


template <class E1, class E2>
treeSum<E1,E2> const
operator+(E1 const& u, E2 const& v) {
    return treeSum<E1, E2>(u, v);
}


template <class E1, class E2>
treeDiff<E1,E2> const
operator-(E1 const& u, E2 const& v) {
    return treeDiff<E1, E2>(u, v);
}


template <typename E1, typename E2>
treeMul<E1,E2> const
operator*(E1 const& u, E2 const& v) {
    return treeMul<E1, E2>(u, v);
}
