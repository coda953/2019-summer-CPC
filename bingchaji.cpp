#include<bits/stdc++.h>
using namespace std;
int father[1000];
int find(int x){
    if(father[x]==x)return x;
    return father[x]=find(father[x]);
}
