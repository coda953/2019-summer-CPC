#include<iostream>
#include<cstdio>
#define MAXN 1000001
typedef long long ll;
using namespace std;
ll n,m,a[MAXN],ans[MAXN<<2],tag[MAXN<<2];
inline ll ls(ll x) {
    return x<<1;
}
inline ll rs(ll x) {
    return x<<1|1;
}
void scan() {
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
        scanf("%lld",&a[i]);
}
inline void push_up(ll p) {
    ans[p]=ans[ls(p)]+ans[rs(p)];
}
void build(ll index,ll l,ll r) {
    tag[index]=0;
    if(l==r){ans[index]=a[l];return ;}
    ll mid=(l+r)>>1;
    build(ls(index),l,mid);
    build(rs(index),mid+1,r);
    push_up(index);
}
inline void f(ll p,ll l,ll r,ll k) {
    tag[p]=tag[p]+k;
    ans[p]=ans[p]+k*(r-l+1);
}
inline void push_down(ll p,ll l,ll r) {
    ll mid=(l+r)>>1;
    f(ls(p),l,mid,tag[p]);
    f(rs(p),mid+1,r,tag[p]);
    tag[p]=0;
}
inline void update(ll left,ll right,ll l,ll r,ll index,ll k) {
    if(left<=l&&r<=right) {
        ans[index]+=k*(r-l+1);
        tag[index]+=k;
        return ;
    }
    push_down(index,l,r);
    ll mid=(l+r)>>1;
    if(left<=mid)update(left,right,l,mid,ls(index),k);
    if(right>mid) update(left,right,mid+1,r,rs(index),k);
    push_up(index);
}
ll query(ll q_l,ll q_r,ll l,ll r,ll index) {
    ll res=0;
    if(q_l<=l&&r<=q_r)return ans[index];
    ll mid=(l+r)>>1;
    push_down(index,l,r);
    if(q_l<=mid)res+=query(q_l,q_r,l,mid,ls(index));
    if(q_r>mid) res+=query(q_l,q_r,mid+1,r,rs(index));
    return res;
}
int main() {
    ll a1,b,c,d,e,f;
    scan();
    build(1,1,n);
    while(m--) {
        scanf("%lld",&a1);
        if(a1==1) {
                scanf("%lld%lld%lld",&b,&c,&d);
                update(b,c,1,n,1,d);
            } else{
                scanf("%lld%lld",&e,&f);
                printf("%lld\n",query(e,f,1,n,1));
            }
        }
    }