#include <bits/stdc++.h>
#define N 100010
using namespace std;
void swap(int &x,int &y){int t=x;x=y,y=t;}
int ch[N][2],val[N],dis[N],f[N],n,m;
int merge(int x,int y)//合并xy
{
    if (x==0 || y==0)
        return x+y;
    if (val[x]>val[y] || (val[x]==val[y] && x>y))
        swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    f[ch[x][1]]=x;
    if (dis[ch[x][0]]<dis[ch[x][1]])
        swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}
int getf(int x)
{
    while(f[x]) x=f[x];
    return x;
}
void pop(int x)//删除x
{
    val[x]=-1;
    f[ch[x][0]]=f[ch[x][1]]=0;
    merge(ch[x][0],ch[x][1]);
}
int main()
{
    cin>>n>>m;
    dis[0]=-1;
    for (int i=1;i<=n;i++)
        cin>>val[i];
    for (int i=1;i<=m;i++)
    {
        int com;
        cin>>com;
        if (com==1)
        {
            int x,y;
            cin>>x>>y;
            if (val[x]==-1 || val[y]==-1)//已被删除
                continue;
            if (x==y)//在同一堆内
                continue;
            int fx=getf(x),fy=getf(y);
            merge(fx,fy);
        }
        else
        {
            int x;
            cin>>x;
            if (val[x]==-1)//已被删除
                puts("-1");
            else
            {
                int y=getf(x);
                printf("%d\n",val[y]);
                pop(y);//将y删除
            }
        }
    }
}