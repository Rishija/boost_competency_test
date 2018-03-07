#define BOOST_TEST_MODULE my_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "segtree.h"
#include "naive.h"

template<class T>
/**
 Constructor
 
 @param arr Input
 @param dc Default value
 @param fn Generic function to be applied to build segment tree
 */
Segment_tree<T>::Segment_tree(vector<T> arr, T dc, function<T(T, T)> fn) : dontCare(dc), tree( 2*pow(2, ceil(log2(arr.size()))) - 1 ), objFn(fn){
    
    size_t size = tree.size(), i = size/2;
    
    // Fill leaf nodes with given values
    for(size_t j = 0; j != arr.size(); ++i, ++j)
        tree[i] = arr[j];
    
    // Fill rest of the leaves with default value
    while(i < size){
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
        
        cout<<endl;
        for (int i = 3; i < tabs; i++)
            cout<<"\t";
        cout<<tree[root];
        
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
void Segment_tree<T>::update(size_t start, size_t end, size_t pos, size_t index, T value){
    
    if(start == end){
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

BOOST_AUTO_TEST_SUITE (test1)

BOOST_AUTO_TEST_CASE(sum_check) {
    
    fstream fp;
    fp.open("testcase1.txt", ios::in);
    int test;
    fp>>test;
    for(int i = 0; i<test; ++i){
        int n, q;
        fp>>n>>q;
        vector<int>v(n);
        for(int i=0; i<n; ++i)
            fp>>v[i];
        
        Segment_tree<int> myTree(v, 0, [](const int &a, const int &b){
            return a+b;
        });
        
        for(int i = 0; i<q; ++i){
            int query;  fp>>query;
            if(query == 1){
                int index, val;
                fp>>index>>val;
                updateSum(v,index,val);
                myTree.update(index, val);
            }
            else{
                int naiveAns, treeAns, l, r;
                fp>>l>>r;
                naiveAns = sum(v,l,r);
                treeAns = myTree.range_query(l,r);
                 BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}

BOOST_AUTO_TEST_CASE(occurence_check){
    fstream fp;
    fp.open("testcase2.txt", ios::in);
    int test;
    fp>>test;
    for(int i = 0; i<test; ++i){
//        cout<<"hola";
        int n, q;
        fp>>n>>q;
        char temp[1000000];
        vector<string>v(n);
        for(int i=0; i<n; ++i){
            fp>>temp;
            v[i] = temp;
        }

        Segment_tree<string> myTree(v, "", [](const string &a, const string &b){
            int cnt1 = count(a.begin(), a.end(), 's'),
            cnt2 =  count(b.begin(), b.end(), 's');
            if(cnt2 > cnt1)
                return b;
            if(cnt2 == cnt1 && b.size() > a.size())
                return b;
            return a;
        });

        for(int j = 0; j<q; ++j){
            fp.ignore();
            int query;  fp>>query;
//            cout<<"query #"<<j<<" query val: "<<query<<endl;
            if(query == 1){
                int index;  fp>>index;
                string val;
                fp>>temp;
                val = temp;
                updateString(v,index,val);
                myTree.update(index, val);
            }
            else{
                int l, r;
                fp>>l>>r;
                string naiveAns, treeAns;
                naiveAns = maxOccurence(v,l,r);
                treeAns = myTree.range_query(l,r);
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}

BOOST_AUTO_TEST_CASE(min_check){
    
    fstream fp;
    fp.open("testcase3.txt", ios::in);
    int test;
    fp>>test;
    for(int i = 0; i<test; ++i){
        int n, q;
        fp>>n>>q;
        vector<double>v(n);
        for(int i=0; i<n; ++i)
            fp>>v[i];
        
        Segment_tree<double> myTree(v, INT_MAX, [](const double &a, const double &b){
            return a < b ? a : b;
        });
        
        for(int i = 0; i<q; ++i){
            int query;  fp>>query;
            if(query == 1){
                int index;
                double val;
                fp>>index>>val;
                updateMin(v,index,val);
                myTree.update(index, val);
            }
            else{
                int l, r;
                double naiveAns, treeAns;
                fp>>l>>r;
                naiveAns = min(v,l,r);
                treeAns = myTree.range_query(l,r);
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}


BOOST_AUTO_TEST_SUITE_END()
