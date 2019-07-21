#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define LL long long
#define inf 0x7f7f7f7f
#define mem(a,n) memset(a,n,sizeof(a))
int read(){
    int num=0,flag=1;char c;
    while((c=getchar())<'0'||c>'9') if(c=='-') flag=-1;
    while(c>='0'&&c<='9') { num=num*10+c-48; c=getchar();}
    return num*flag;
}
struct node{
    int v,w;
    node(int V,int W){v=V;w=W;}
    bool operator < (const node &rhs) const {
        return rhs.w>w;
    }
};
int dis[N],n,m,a[N],s,vis[N],t;
vector<node> g[N];
void dijkstra() {
    for(int i=1;i<=n;i++)
        dis[i]=inf;
    dis[s]=0;
    priority_queue<node> q;
    q.push( node(s,0) );
    while(!q.empty()) {
        node x =q.top();
        q.pop();
        for (int i = 0; i < g[x.v].size(); i++) {
            node y = g[x.v][i];
            if (dis[y.v] > x.w + y.w) {
                dis[y.v] = x.w + y.w;
                q.push(node(y.v, dis[y.v])); }
        }
    }
}
void addedge(int u,int v,int w){
    g[u].emplace_back(v,w);
    g[v].emplace_back(u,w);
}
int main() {
    n=read();m=read();
    for(int i=1,u,v,w;i<=m;i++) {
        u=read(),v=read(),w=read();
        addedge(u,v,w);
    }
    s=read();t=read();
    dijkstra();
    cout<<dis[t];
}
