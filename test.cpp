#define BOOST_TEST_MODULE my_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "segtree.h"
#include "naive/naive.h"

// print pair value in case of value mismatch
namespace boost {
    namespace test_tools {
        namespace tt_detail {
            template<typename T,typename U>
            struct print_log_value<pair<T, U> > {
                void operator()(ostream& os, pair<T, U> const &pair) {
                    os << "<" << pair.first << "," << pair.second << ">";
                }
            };
        }
    }
}

BOOST_AUTO_TEST_SUITE (test1)

BOOST_AUTO_TEST_CASE(sum_check) {
    
    long long int naiveTime = 0, treeTime = 0;
    chrono::steady_clock::time_point t1, t2;
    fstream fp;
    fp.open("./generate_cases/testcase1.txt", ios::in);
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
        
        for(int j = 0; j < q; ++j) {
            int query;  fp >> query;
            if(query == 1) {
                int index, val;
                fp >> index >> val;
                
                t1 = chrono::steady_clock::now();
                updateSum(v,index,val);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                myTree.update(index, val);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
            }
            else {
                int naiveAns, treeAns, l, r;
                fp >> l >> r;
                
                t1 = chrono::steady_clock::now();
                naiveAns = sum(v,l,r);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                treeAns = myTree.range_query(l,r);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
                
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    cout << "Naive Time: " << naiveTime << endl << "Tree Time: " << treeTime << endl;
    fp.close();
}

BOOST_AUTO_TEST_CASE(occurence_check) {
    
    long long int naiveTime = 0, treeTime = 0;
    chrono::steady_clock::time_point t1, t2;
    fstream fp;
    fp.open("./generate_cases/testcase2.txt", ios::in);
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
                
                t1 = chrono::steady_clock::now();
                updateString(v,index,val);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                myTree.update(index, val);
            }
            else {
                int l, r;
                fp >> l >> r;
                string naiveAns, treeAns;
                
                t1 = chrono::steady_clock::now();
                naiveAns = maxOccurence(v,l,r);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                treeAns = myTree.range_query(l,r);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
                
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    cout << "Naive Time: " << naiveTime << endl << "Tree Time: " << treeTime << endl;
    fp.close();
}

BOOST_AUTO_TEST_CASE(min_check) {
    
    long long int naiveTime = 0, treeTime = 0;
    chrono::steady_clock::time_point t1, t2;
    fstream fp;
    fp.open("./generate_cases/testcase3.txt", ios::in);
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
        
        for(int j = 0; j < q; ++j) {
            int query;  fp >> query;
            if(query == 1) {
                int index;
                double val;
                fp >> index >> val;
                
                t1 = chrono::steady_clock::now();
                updateMin(v,index,val);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                myTree.update(index, val);
            }
            else {
                int l, r;
                double naiveAns, treeAns;
                fp >> l >> r;
                
                t1 = chrono::steady_clock::now();
                naiveAns = min(v,l,r);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                treeAns = myTree.range_query(l,r);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
                
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    cout << "Naive Time: " << naiveTime << endl << "Tree Time: " << treeTime << endl;
    fp.close();
}

BOOST_AUTO_TEST_CASE(max_dist) {
    
    long long int naiveTime = 0, treeTime = 0;
    chrono::steady_clock::time_point t1, t2;
    fstream fp;
    fp.open("./generate_cases/testcase4.txt", ios::in);
    int test;
    fp >> test;
    for(int i = 0; i < test; ++i) {
        int n, q;
        fp >> n >> q;
        vector<pair<int,int> >v(n);
        for(int i=0; i < n; ++i){
            int c1, c2;
            fp >> c1 >> c2;
            v[i] = make_pair(c1,c2);
        }
        
        Segment_tree<pair<int,int> > myTree(v, make_pair(0,0), [] (const pair<int,int> &a, const pair<int,int> &b) -> pair<int,int> {
            int dist1 = sqrt( pow(a.first,2) + pow(a.second,2) ),
            dist2 = sqrt( pow(b.first,2) + pow(b.second,2) );
            return dist2 > dist1 ? b : a;
        });
        
        for(int j = 0; j < q; ++j) {
            int query;  fp >> query;
            if(query == 1) {
                int index, fir, sec;
                pair<int,int> val;
                fp >> index >> fir >> sec;
                val = make_pair(fir,sec);
                
                t1 = chrono::steady_clock::now();
                updatePair(v,index,val);
                myTree.update(index, val);
            }
            else {
                int l, r, nAns, tAns;
                pair<int,int> naiveAns, treeAns;
                fp >> l >> r;
                
                t1 = chrono::steady_clock::now();
                naiveAns = originDist(v,l,r);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                treeAns = myTree.range_query(l,r);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
                
                BOOST_CHECK_EQUAL(naiveAns, treeAns);
            }
        }
    }
    cout << "Naive Time: " << naiveTime << endl << "Tree Time: " << treeTime << endl;
    fp.close();
}

BOOST_AUTO_TEST_CASE(total_expenditure) {
    
    long long int naiveTime = 0, treeTime = 0;
    chrono::steady_clock::time_point t1, t2;
    fstream fp;
    fp.open("./generate_cases/testcase5.txt", ios::in);
    int test;
    fp >> test;
    for(int i = 0; i < test; ++i) {
        int n, q;
        fp >> n >> q;
        vector<Expenditure>v(n);
        for(int i=0; i < n; ++i){
            int q1, r1, q2, r2;
            fp >> q1 >> r1 >> q2 >> r2;
            Expenditure temp(q1,r1,q2,r2);
            v[i] = temp;
        }
        
        Expenditure nulll(0,0,0,0);
        Segment_tree<Expenditure> myTree(v, nulll, [](const Expenditure &a, const Expenditure &b) {
            Expenditure c(a.getQuant1() + b.getQuant1(), a.getRent1() + b.getRent1(), a.getQuant2() + b.getQuant2(), a.getRent2() + b.getRent2());
            return c;
        });
        
        for(int j = 0; j < q; ++j) {
            int query;  fp >> query;
            if(query == 1) {
                int index, q1, r1, q2, r2;
                fp >> index >> q1 >> r1 >> q2 >> r2;
                Expenditure val(q1,r1,q2,r2);
                
                t1 = chrono::steady_clock::now();
                updateExpenditure(v,index,val);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                myTree.update(index, val);
            }
            else {
                int l, r;
                Expenditure naiveAns, treeAns;
                fp >> l >> r;
                
                t1 = chrono::steady_clock::now();
                naiveAns = totalExpenditure(v,l,r);
                t2 = chrono::steady_clock::now();
                naiveTime += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                
                treeAns = myTree.range_query(l,r);
                t1 = chrono::steady_clock::now();
                treeTime += chrono::duration_cast<chrono::microseconds>(t1 - t2).count();
                
                BOOST_CHECK(naiveAns == treeAns);
            }
        }
    }
    cout << "Naive Time: " << naiveTime << endl << "Tree Time: " << treeTime << endl;
    fp.close();
}

BOOST_AUTO_TEST_SUITE_END()
