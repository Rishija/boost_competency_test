#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#define CASES 100

void sum_of_integers(const char* fileName, const int n, const int q, const int maxNum) {
    
    fstream fp;
    fp.open(fileName, ios::out);
    int cases = CASES;
    fp << cases << endl;
    
    while(cases--) {
        
        int size = rand() % n + 1, queries = rand() % q + 1;
        fp << size << " " << queries << endl;
        for(int i = 0; i < size; ++i)
            fp << rand() % maxNum << " ";
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q == 1) {
                int index = rand() % size, val = rand() % maxNum;
                fp << index << " " << val << endl;
            }
            else {
                int l = rand() % size, r = rand() % size;
                while(r < l)
                    r = rand() % size;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
}

void max_occurence(const char* filename, const int n, const int q, const int maxSize) {
    
    fstream fp;
    fp.open("testcase2.txt", ios::out);
    int cases = CASES;
    fp << cases << endl;
    
    while(cases--) {
        
        int totalStrings = rand() % n + 1, queries = rand() % q + 1;
        fp << totalStrings << " " << queries << endl;
        for(int i = 0; i < totalStrings; ++i) {
            int strLen = rand() % maxSize + 1;
            for(int j = 0; j < strLen; ++j)
                fp << char(rand() % 26 + 97);
            fp << " ";
        }
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q == 1) {
                int index = rand() % totalStrings, strLen = rand() % maxSize + 1;
                fp << index << " ";
                for(int j = 0; j < strLen; ++j)
                    fp << char(rand() % 26 + 97);
                fp << endl;
            }
            else {
                int l = rand() % totalStrings, r = rand() % totalStrings;
                while(r < l)
                    r = rand() % totalStrings;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
}

void minimum(const char* fileName, const int n, const int q, const int maxNum) {
    
    fstream fp;
    fp.open(fileName, ios::out);
    int cases = CASES;
    fp << cases << endl;
    
    while(cases--) {
        
        int size = rand() % n + 1, queries = rand() % q + 1;
        fp << size << " " << queries << endl;
        for(int i = 0; i < size; ++i) {
            fp << rand() %
            maxNum + static_cast <double> (rand()) / static_cast <double> (RAND_MAX)  << " ";
        }
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q == 1) {
                int index = rand() % size;
                double val = rand() %
                maxNum + static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                fp << index << " " << val << endl;
            }
            else {
                int l = rand() % size, r = rand() % size;
                while(r < l)
                    r = rand() % size;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
}

void max_coordinate_distance(const char* fileName, const int n, const int q, const int absNum) {
    
    fstream fp;
    fp.open("testcase4.txt", ios::out);
    int cases = CASES;
    fp << cases << endl;
    
    while(cases--) {
        
        int size = rand() % n + 1, queries = rand() % q + 1;
        fp << size << " " << queries << endl;
        for(int i = 0; i < size; ++i) {
            fp << (rand() % 2 * absNum) - absNum << " " << (rand() % 2 * absNum) - absNum << " ";
        }
        fp << endl;
        
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q == 1) {
                int index = rand() % size;
                fp << index << " " << (rand() % 2 * absNum) - absNum << " "
                << (rand() % 2 * absNum) - absNum << endl;
            }
            else {
                int l = rand() % size, r = rand() % size;
                while(r < l)
                    r = rand() % size;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
}


void total_expenditure
(const char* fileName, const int n, const int q, const int maxQuant, const int maxRent) {
    
    fstream fp;
    fp.open("testcase5.txt", ios::out);
    int cases = CASES;
    fp << cases << endl;
    
    while(cases--) {
        
        int size = rand() % n + 1, queries = rand() % q + 1;
        fp << size << " " << queries << endl;
        for(int i = 0; i < size; ++i) {
            fp << rand() % maxQuant << " " << rand() % maxRent << " "
            << rand() % maxQuant << " " << rand() % maxRent << " ";
        }
        fp << endl;
        while(queries--) {
            int q = rand() % 2 + 1;
            fp << q << " ";
            if(q == 1) {
                int index = rand() % size;
                fp << index << " " << rand() % maxQuant << " " << rand() % maxRent
                << " " << rand() % maxQuant << " " << rand() % maxRent << endl;
            }
            else {
                int l = rand() % size, r = rand() % size;
                while(r < l)
                    r = rand() % size;
                fp << l << " " << r << endl;
            }
        }
    }
    fp.close();
}

int main() {
    
    sum_of_integers("testcase1.txt", 10000, 5000, 20000);
    max_occurence("testcase2.txt", 200, 5000, 200);
    minimum("testcase3.txt", 2000, 5000, 100);
    max_coordinate_distance("testcase4.txt", 2000, 5000, 5000);
    total_expenditure("testcase5.txt", 1000, 5000, 10, 200);
    return 0;
}
