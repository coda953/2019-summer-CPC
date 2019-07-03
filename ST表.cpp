#include<cstdio>
#include<cmath>
#include<algorithm>
#include <iostream>

using namespace std;
const int MAXN=1e6+10;
int Max[MAXN][21];
int Query(int l,int r){
    int k=log2(r-l+1);
    return max(Max[l][k],Max[r-(1<<k)+1][k]);//把拆出来的区间分别取最值
}
int main()
{
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>Max[i][0];
    for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)//注意这里要控制边界
            Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);//如果看不懂边界的话建议好好看看图
    for(int i=1;i<=m;i++)
    {
        int l,r;cin>>l>>r;
        printf("%d\n",Query(l,r));
    }
    return 0;
}