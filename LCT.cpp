#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=300010;
void read(int &x){
    char c=getchar(); x=0;
    for(;c>'9'||c<'0';c=getchar());
    for(;c<='9'&&c>='0';c=getchar()) x=(x<<3)+(x<<1)+c-'0';
}
struct LCT {
    int sum[maxn],rev[maxn],ch[maxn][2],fa[maxn],stc[maxn],top;
    int isroot(int x){
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    int get(int x){
        return ch[fa[x]][1]==x;
    }
    void pushdown(int x) {
        if(!rev[x]||!x) return ;
        swap(ch[x][0],ch[x][1]);
        if(ch[x][0]) rev[ch[x][0]]^=1;
        if(ch[x][1]) rev[ch[x][1]]^=1;
        rev[x]=0;
    }
    void pushup(int x) {
        sum[x]=1;
        if(ch[x][0]) sum[x]+=sum[ch[x][0]];
        if(ch[x][1]) sum[x]+=sum[ch[x][1]];
    }
    void rotate(int x) {
        int old=fa[x],fold=fa[old],opt=get(x);
        if(!isroot(old)) ch[fold][get(old)]=x;
        fa[x]=fold;
        ch[old][opt]=ch[x][opt^1]; fa[ch[old][opt]]=old;
        ch[x][opt^1]=old; fa[old]=x;
        pushup(old); pushup(x);
    }
    void splay(int x) {
        int top=0; stc[++top]=x;
        for(int i=x;!isroot(i);i=fa[i]) stc[++top]=fa[i];
        for(int i=top;i;i--) pushdown(stc[i]);
        for(int f;!isroot(x);rotate(x)){
            if(!isroot(f=fa[x]))
                rotate(get(x)==get(f)?f:x);
        }
    }
    void access(int x) {
        int rson=0;
        for(;x;rson=x,x=fa[x]){
            splay(x);
            ch[x][1]=rson;
            pushup(x);
        }
    }
    int find(int x){ access(x); splay(x); while(ch[x][0]) x=ch[x][0]; return x;}
    int query(int x,int y) { make_root(x); access(y);  splay(y); return sum[y]-1; }//查询到根的距离
    void make_root(int x) { access(x); splay(x); rev[x]^=1; }//制定x为根
    void link(int x,int y) { make_root(x); fa[x]=y; splay(x); }//将x，y连接
    void cut(int x,int y) { make_root(x); access(y); splay(y); fa[x]=ch[y][0]=0; }//切断x,y

}S;
int a[maxn];
int n,m,opt,x,y;
int main() {

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        S.link(i,min(n+1,i+a[i]));
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d",&x);
            printf("%d\n",S.query(n+1,x+1));
        }
        else{
            scanf("%d%d",&x,&y); x++;
            S.cut(x,min(n+1,x+a[x]));
            a[x]=y;
            S.link(x,min(n+1,x+y));
        }
    }
    return 0;
}
