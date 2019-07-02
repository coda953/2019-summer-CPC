#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n,m,tree[2000010];
inline int lowbit(int k) {
    return k & -k;
}
void add(int x,int k) {
    while(x<=n) {
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int sum(int x) {
    int ans=0;
    while(x!=0) {
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
int sum(int left,int right){
    return sum(right)-sum(left-1);
}