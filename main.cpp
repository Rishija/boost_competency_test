#include "segtree.h"

template <class T>
Segment_tree<T>::Segment_tree(vector<T> arr, T dc, function<T(T, T)> fn) : dontCare(dc), tree( 2*pow(2, ceil(log2(arr.size()))) - 1 ), objFn(fn){
    
    size_t size = tree.size(), i = size/2;
    for(size_t j = 0; j < arr.size(); ++i, ++j)
        tree[i] = arr[j];
    
    while(i < size){
        tree[i] = dontCare;
        ++i;
    }
    
    i = 0;
    for(size_t j = size/2 - 1; i < size/2 ; --j, ++i)
        tree[j] = objFn(tree[2*j+1], tree[2*j+2]);
}


template<class T>
void Segment_tree<T>::print_tree(size_t root, int tabs)
{
    if(root < tree.size()) {
        tabs += 3;
        print_tree(2*root + 2, tabs);
        
        cout<<endl;
        for (int i = 3; i < tabs; i++)
            cout<<"\t";
        cout<<tree[root];
        
        print_tree(2*root + 1, tabs);
    }
}

template <class T>
T Segment_tree<T>::range_query(size_t start, size_t end)  {
    
    assert(start <= end && "Invalid query");
    return range_query(start, end, 0, tree.size()/2, 0);
}

template <class T>
T Segment_tree<T>:: range_query(size_t start, size_t end, size_t arrStart, size_t arrEnd, size_t pos) {
    
    // current range completely lies between the given range
    if((arrStart >= start && arrEnd <= end))
        return tree[pos];
    
    if(start > arrEnd || end < arrStart)
        return dontCare;
    
    size_t mid = (arrStart + arrEnd)/2;
    
    return objFn(range_query(start, end, arrStart, mid , 2*pos + 1), range_query(start, end, mid + 1, arrEnd, 2*pos + 2));
}

template <class T>
void Segment_tree<T>::update(size_t index, T value) {
    
    assert(index >=0 && index <= tree.size()/2 && "Invalid index");
    update(0, tree.size()/2, 0, index, value);
}

template<class T>
void Segment_tree<T>::update(size_t start, size_t end, size_t pos, size_t index, T value){
    
    if(start == end){
        tree[tree.size()/2 + start] = value;
        return;
    }
    
    size_t mid = (start + end)/2;
    index <= mid ? update(start, mid, 2*pos + 1, index, value) : update(mid + 1, end, 2*pos + 2, index, value) ;
    
    tree[pos] = objFn(tree[2*pos + 1], tree[2*pos + 2]);
}


int main(){
    
    vector<int>a={5,3,8,9,1,4};
    Segment_tree<int> myTree(a, INT_MAX, [](const int &a, const int &b) {
        return a < b ? a : b ;
    });
    myTree.print_tree();
    cout<<myTree.range_query(0, 5)<<endl;
    cout<<myTree.range_query(1, 5)<<endl;
    cout<<myTree.range_query(1, 4)<<endl;
    cout<<myTree.range_query(3, 3)<<endl;
    cout<<myTree.range_query(2, 5)<<endl;
    cout<<myTree.range_query(1, 3)<<endl;
    cout<<myTree.range_query(5, 5)<<endl;
    cout<<myTree.range_query(4, 5)<<endl;
    cout<<myTree.range_query(3, 4)<<endl;
    
    myTree.update(5, 15);
    myTree.print_tree();
    cout<<myTree.range_query(0, 5)<<endl;
    cout<<myTree.range_query(1, 5)<<endl;
    cout<<myTree.range_query(1, 4)<<endl;
    cout<<myTree.range_query(3, 3)<<endl;
    cout<<myTree.range_query(2, 5)<<endl;
    cout<<myTree.range_query(1, 3)<<endl;
    cout<<myTree.range_query(5, 5)<<endl;
    cout<<myTree.range_query(4, 5)<<endl;
    cout<<myTree.range_query(3, 4)<<endl;
    
    return 0;
}
