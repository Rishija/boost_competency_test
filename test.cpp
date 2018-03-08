#define BOOST_TEST_MODULE my_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "segtree.h"
#include "naive.h"


BOOST_AUTO_TEST_SUITE (test1)

BOOST_AUTO_TEST_CASE(sum_check) {
    
    fstream fp;
    fp.open("testcase1.txt", ios::in);
    int test;
    fp >> test;
    for(int i = 0; i < test; ++i) {
        int n, q;
        fp >> n >> q;
        vector<int>v(n);
        for(int i=0; i<n; ++i)
            fp >> v[i];
        
        Segment_tree<int> myTree(v, 0, [] (const int &a, const int &b) {
            return a+b;
        });
        
        for(int i = 0; i < q; ++i) {
            int query;  fp >> query;
            if(query == 1) {
                int index, val;
                fp >> index >> val;
                updateSum(v,index,val);
                myTree.update(index, val);
            }
            else {
                int naiveAns, treeAns, l, r;
                fp >> l >> r;
                naiveAns = sum(v,l,r);
                treeAns = myTree.range_query(l,r);
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}

BOOST_AUTO_TEST_CASE(occurence_check) {
    fstream fp;
    fp.open("testcase2.txt", ios::in);
    int test;
    fp >> test;
    for(int i = 0; i<test; ++i) {
        //        cout << "hola";
        int n, q;
        fp >> n >> q;
        char temp[1000000];
        vector<string>v(n);
        for(int i = 0; i < n; ++i) {
            fp >> temp;
            v[i] = temp;
        }
        
        Segment_tree<string> myTree(v, "", [](const string &a, const string &b) {
            int cnt1 = count(a.begin(), a.end(), 's'),
            cnt2 =  count(b.begin(), b.end(), 's');
            if(cnt2 > cnt1)
                return b;
            if(cnt2 == cnt1 && b.size() > a.size())
                return b;
            return a;
        });
        
        for(int j = 0; j < q; ++j) {
            fp.ignore();
            int query;  fp >> query;
            //            cout << "query #" << j << " query val: " << query << endl;
            if(query == 1) {
                int index;  fp >> index;
                string val;
                fp >> temp;
                val = temp;
                updateString(v,index,val);
                myTree.update(index, val);
            }
            else {
                int l, r;
                fp >> l >> r;
                string naiveAns, treeAns;
                naiveAns = maxOccurence(v,l,r);
                treeAns = myTree.range_query(l,r);
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}

BOOST_AUTO_TEST_CASE(min_check) {
    
    fstream fp;
    fp.open("testcase3.txt", ios::in);
    int test;
    fp >> test;
    for(int i = 0; i < test; ++i) {
        int n, q;
        fp >> n >> q;
        vector<double>v(n);
        for(int i=0; i < n; ++i)
            fp >> v[i];
        
        Segment_tree<double> myTree(v, INT_MAX, [](const double &a, const double &b) {
            return a < b ? a : b;
        });
        
        for(int i = 0; i < q; ++i) {
            int query;  fp >> query;
            if(query == 1) {
                int index;
                double val;
                fp >> index >> val;
                updateMin(v,index,val);
                myTree.update(index, val);
            }
            else {
                int l, r;
                double naiveAns, treeAns;
                fp >> l >> r;
                naiveAns = min(v,l,r);
                treeAns = myTree.range_query(l,r);
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    fp.close();
}

BOOST_AUTO_TEST_SUITE_END()
