//拉格朗日插值
// 读入n,k
//n个点，求k项的值
#define mod 998244353
long long power(long long x,long long y,long long p)
{
    long long r=1;
    while(y)
    {
        if(y&1)r=r*x%p;
        x=x*x%p;
        y>>=1;
    }
    return r;
}
#define N 2010
long long x[N],y[N],n,v,ans;
int main()
{
    n=read();
    v=read();
    fr(i,1,n)x[i]=read(),y[i]=read();
    fr(i,1,n)
    {
        long long k=1;
        fr(j,1,n)if(i!=j)k=k*(x[i]+mod-x[j])%mod;
        k=power(k,mod-2,mod);
        fr(j,1,n)if(i!=j)k=k*(v+mod-x[j])%mod;
        k=k*y[i]%mod;
        ans=(ans+k)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}