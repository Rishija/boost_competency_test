#ifndef naive_h
#define naive_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

int sum(vector<int>v, int l, int r){
    int sum = 0;
    for(int i = l; i <= r; ++i)
        sum += v[i];
    return sum;
}

void updateSum(vector<int>&v, size_t index, int value){
    v[index] = value;
}

double min(vector<double>v, int l, int r){
    double min = INT_MAX;
    for(int i = l; i <= r; ++i)
        if(v[i] < min)
            min = v[i];
    return min;
}

void updateMin(vector<double>&v, size_t index, double value){
    v[index] = value;
}

string maxOccurence(vector<string>v, int l, int r){
    string ans = "";
    int c = -1;
    for(int i = l; i <= r; ++i){
        int cnt = count(v[i].begin(), v[i].end(), 's');
        if(cnt > c){
            ans = v[i];
            c = cnt;
        }
        if(cnt == c && v[i].size() > ans.size()){
            ans = v[i];
            c = cnt;
        }
            
    }
    return ans;
}

void updateString(vector<string>&v, size_t index, string value){
    v[index] = value;
}

#endif
