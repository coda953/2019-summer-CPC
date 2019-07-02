#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long ll;
template <int n>
class vervec{
    ll tree[20*n],ls[20*n],rs[20*n],hd[n],hd1[2*n],tt,t,nh;ll*a;
    ll&ins(ll nod,ll l,ll r,ll x){
        if(l==r){return tree[nod];}
        int mid=l+(r>>1);
        if(x<=mid){tree[++tt]=tree[ls[nod]];ls[tt]=ls[ls[nod]];rs[tt]=rs[ls[nod]];
            ls[nod]=tt;return ins(tt,l,mid,x);}
        if(x>mid){tree[++tt]=tree[rs[nod]];ls[tt]=ls[rs[nod]];rs[tt]=rs[rs[nod]];
            rs[nod]=tt;return ins(tt,mid+1,r,x);}
    }
    void chit(){ll x=hd[nh];hd[++t]=++tt;tree[tt]=tree[x];
        ls[tt]=ls[x];rs[tt]=rs[x];nh=t;}
    int build(ll l,ll r){
        ll nod=++tt;if(l==r){tree[nod]=a[l];ls[nod]=rs[nod]=0;return nod;}
        ll mid=l+r>>1;
        ls[nod]=build(l,mid);
        rs[nod]=build(mid+1,r);
        return nod;
    }
    void init(){tt=0;hd[nh=0]=1;build(1,n);}
    ll query(ll nod,ll l,ll r,ll x){
        if(l==r)return tree[nod];
        ll mid=l+r>>1;
        if(x<=mid)return query(ls[nod],l,mid,x);
        else if(x>mid)return query(rs[nod],mid+1,r,x);
    }
public:
    vervec(){tt=0;t=0;nh=1;}
    void init(ll*x){a=x;init();}
    void mark(ll x){hd1[x]=nh;}
    ll&operator[](ll x){chit();return ins(hd[nh],1,n,x);}
    ll val(ll x){return query(hd[nh],1,n,x);}
    void rever(ll x){nh=hd1[x];}
};
vervec<120003>f,c;
ll getf(ll v){
    ll fa=f.val(v);
    if(fa==v)return v;
    return getf(fa);
}
void add(ll a,ll b){
    a=getf(a);
    b=getf(b);
    if(a==b)return;
    ll va=c.val(a),vb=c.val(b);
    if(va==vb){
        f[a]=b;
        c[b]++;
    }else if(va<vb){
        f[a]=b;
    }else{
        f[b]=a;
    }
}
ll sol[120003],n,m,x,y,z;
void init(ll n){
    for(ll i=1;i<=n;i++)sol[i]=i;
    f.init(sol);
    for(ll i=1;i<=n;i++)sol[i]=1;
    c.init(sol);
}
int main(){
    cin>>n>>m;
    init(n);
    f.mark(0);
    c.mark(0);
    for(ll i=1;i<=m;i++){
        cin>>x;
        if(x==1){
            cin>>x>>y;
            add(x,y);
        }else if(x==2){
            cin>>y;
            f.rever(y);
            c.rever(y);
        }else{
            cin>>x>>y;
            puts(getf(x)==getf(y)?"1":"0");
        }
        f.mark(i);
        c.mark(i);
    }
    return 0;
}