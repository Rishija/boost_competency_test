#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int main() {
    
    // sum of integers
    fstream fp;
    fp.open("testcase1.txt", ios::out);
    int cases = 100;
    fp << cases << endl;
    while(cases--) {
        int n = rand() % 10000 + 1, queries = rand() % 5000 + 1;
        fp << n << " " << queries << endl;
        for(int i = 0; i<n; ++i) {
            fp << rand() % 20000 << " ";
        }
        fp << endl;
        
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q==1) {
                int index = rand() % n, val = rand() % 20000;
                fp << index << " " << val << endl;
            }
            else {
                int l = rand() % n, r = rand() % n;
                while(r < l)
                    r = rand() % n;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
    
    
    // string with maximum occurence of character 's'
    fp.open("testcase2.txt", ios::out);
    cases = 100;
    fp << cases << endl;
    while(cases--) {
        int strings = rand() % 200 + 1, queries = rand() % 5000 + 1;
        fp << strings << " " << queries << endl;
        for(int i = 0; i<strings; ++i) {
            int strlength = rand() % 200 + 1;
            for(int j = 0; j<strlength; ++j)
                fp << char(rand() % 26 + 97);
            fp << " ";
        }
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q==1) {
                int index = rand() % strings, strlen = rand() % 200 + 1;
                fp << index << " ";
                for(int j = 0; j<strlen; ++j)
                    fp << char(rand() % 26 + 97);
                fp << endl;
            }
            else {
                int l = rand() % strings, r = rand() % strings;
                while(r < l)
                    r = rand() % strings;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
    
    
    // minimum in the range
    fp.open("testcase3.txt", ios::out);
    cases = 100;
    fp << cases << endl;
    while(cases--) {
        int n = rand() % 2000 + 1, queries = rand() % 5000 + 1;
        fp << n << " " << queries << endl;
        for(int i = 0; i<n; ++i) {
            fp << rand() % 100 + static_cast <double> (rand()) / static_cast <double> (RAND_MAX)  << " ";
        }
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q==1) {
                int index = rand() % n;
                double val = rand() % 100 + static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                fp << index << " " << val << endl;
            }
            else {
                int l = rand() % n, r = rand() % n;
                while(r < l)
                    r = rand() % n;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
    
    return 0;
}

