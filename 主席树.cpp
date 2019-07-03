#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=200010;

int n,m,k,N=1;
int b[maxn],ys[maxn],root[maxn];
//b存离散化后的数,ys建立离散化后与原数的映射关系,root为森林的不同根节点

struct node{
    int num,id;
}a[maxn];

struct Tree{
    int l,r,size;
}tree[maxn*32];//多开 1<<5 的空间

bool cmp(node a,node b){//求第k小的数,所以从小到大排序
    return a.num<b.num;
}

void lsh(){//离散化模板
    b[a[1].id]=1;
    ys[1]=a[1].num;//注意存映射的点
    for(int i=2;i<=n;i++){
        if(a[i].num!=a[i-1].num)
            N++;
        b[a[i].id]=N;
        ys[N]=a[i].num;
    }
}

int build(int l,int r){//动态建树,防止数组越界或开不够
    int now=++k;//加点
    int mid=(l+r)/2;
    if(l<r){
        tree[now].l=build(l,mid);//更新左儿子
        tree[now].r=build(mid+1,r);//更新右儿子
    }
    return now;
}

int update(int pre,int l,int r,int x){//建权值线段树
    int now=++k;
    tree[now].size=tree[pre].size+1;//此线段树的点数为上一棵的点数+1
    //继承上一棵线段树
    tree[now].l=tree[pre].l;
    tree[now].r=tree[pre].r;
    if(l<r){//寻找需要更新的链
        int mid=(l+r)/2;
        if(x>mid)//在右儿子更新
            tree[now].r=update(tree[pre].r,mid+1,r,x);
        else//在左儿子更新
            tree[now].l=update(tree[pre].l,l,mid,x);
    }
    return now;
}

int query(int u,int v,int l,int r,int x){//查询操作
    if(l==r) return l;//找到第k小值
    //第r棵线段树左儿子-第(l-1)棵线段树左儿子的值
    int tmp=tree[tree[v].l].size-tree[tree[u].l].size;
    int mid=(l+r)/2;
    if(x<=tmp)//在左儿子上
        return query(tree[u].l,tree[v].l,l,mid,x);
    else//在右儿子上
        return query(tree[u].r,tree[v].r,mid+1,r,x-tmp);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].num);
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    lsh();
    root[0]=build(1,N);//建一颗空的线段树
    for(int i=1;i<=n;i++)//建n棵线段树,边加点边建树
        root[i]=update(root[i-1],1,N,b[i]);
    for(int i=1,l,r,kk;i<=m;i++){
        scanf("%d%d%d",&l,&r,&kk);
        //[l,r]就等价于 第r棵线段树-第(l-1)棵线段树 的k小值,返回该节点映射的值
        printf("%d\n",ys[query(root[l-1],root[r],1,N,kk)]);
    }
    return 0;
}